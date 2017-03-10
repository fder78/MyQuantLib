
#include <ql/exercise.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/meshers/fdmblackscholesmesher.hpp>
#include <ql/methods/finitedifferences/utilities/fdmdividendhandler.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>

#include <eq_derivatives/autocallable_engine/mesher_mandatory.h>
#include <eq_derivatives/autocallable_engine/autocall_stepcondition.h>
#include <eq_derivatives/autocallable_engine/call_stepcondition.h>
#include <eq_derivatives/autocallable_engine/autocall_engine.h>
#include <eq_derivatives/autocallable_engine/autocall_calculator.h>
#include <eq_derivatives/autocallable_engine/autocall_solver.h>
#include <eq_derivatives/autocallable_engine/recording_stepcondition.h>


namespace QuantLib {

	FdAutocallEngine::FdAutocallEngine(
		const boost::shared_ptr<YieldTermStructure>& disc,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
		Real correlation,
		Size xGrid, Size yGrid,
		Size tGrid, Size dampingSteps,
		const FdmSchemeDesc& schemeDesc)
		: disc_(disc), p1_(p1), p2_(p2), correlation_(correlation), numGrid_(std::vector<Size>(2,0)), tGrid_(tGrid),
		dampingSteps_(dampingSteps), schemeDesc_(schemeDesc), isGeneral_(false), assetNumber_(2)
	{
		numGrid_[0] = xGrid;  numGrid_[1] = yGrid;
		//ProcessArray
		std::vector<boost::shared_ptr<StochasticProcess1D> > procs;
		procs.push_back(p1_);	procs.push_back(p2_);
		Matrix correlationMatrix(2, 2, correlation);
		correlationMatrix[0][0] = correlationMatrix[1][1] = 1.0;
		process_ = boost::shared_ptr<StochasticProcessArray>(new StochasticProcessArray(procs, correlationMatrix));
	}

	
	FdAutocallEngine::FdAutocallEngine(
		const boost::shared_ptr<YieldTermStructure>& disc,
		const boost::shared_ptr<StochasticProcessArray>& process,
		Size xGrid, 
		Size tGrid, Size dampingSteps,
		const FdmSchemeDesc& schemeDesc)
		: disc_(disc), process_(process), numGrid_(std::vector<Size>(process->size(), xGrid)), tGrid_(tGrid),
		dampingSteps_(dampingSteps), schemeDesc_(schemeDesc), isGeneral_(true), assetNumber_(process->size()) {}

	void FdAutocallEngine::calculate() const {

		//is redempted?
		Array prices(assetNumber_), logprices(assetNumber_);
		for (Size i = 0; i < assetNumber_; ++i) {
			prices[i] = process_->process(i)->x0();
			logprices[i] = std::log(prices[i]);
		}
		for (Size i = 0; i < arguments_.autocallDates.size(); ++i) {
			if (Settings::instance().evaluationDate() == arguments_.autocallDates[i]) {
				if (arguments_.autocallConditions[i]->operator()(logprices)) {
					results_.value = arguments_.autocallPayoffs[i]->operator()(prices) * arguments_.notionalAmt / 100.0;
					results_.theta = std::vector<Real>(1, 0);
					results_.delta = std::vector<Real>(assetNumber_, 0);
					results_.gamma = std::vector<Real>(assetNumber_, 0);
					results_.xgamma = std::vector<std::vector<Real> >(assetNumber_, std::vector<Real>(assetNumber_, 0));
					return;
				}
			}
		}
		if (Settings::instance().evaluationDate() == arguments_.autocallDates.back()) {
			results_.value = arguments_.terminalPayoff->operator()(prices) * arguments_.notionalAmt / 100.0;
			if (arguments_.isKI && arguments_.kibarrier->getBarrierNumbers() > 0)
				results_.value = arguments_.KIPayoff->operator()(prices) * arguments_.notionalAmt / 100.0;
			results_.theta = std::vector<Real>(1, 0);
			results_.delta = std::vector<Real>(assetNumber_, 0);
			results_.gamma = std::vector<Real>(assetNumber_, 0);
			results_.xgamma = std::vector<std::vector<Real> >(assetNumber_, std::vector<Real>(assetNumber_, 0));
			return;
		}

		//Calculation Start
		enum CalcType { None, firstKI, secondKI };
		CalcType type = None;
		bool repeat = true, firstRound = true;
		boost::shared_ptr<FdmStepConditionComposite> conditions;


		while (repeat) {
			// 1. Payoff
			const boost::shared_ptr<BasketPayoff> payoff;
			std::vector<boost::shared_ptr<BasketPayoff> > autocallPayoffs = arguments_.autocallPayoffs;
			std::vector<boost::shared_ptr<BasketPayoff> > KIautocallPayoffs = arguments_.KIautocallPayoffs;

			// 2. Mesher
			const Time maturity = disc_->dayCounter().yearFraction(disc_->referenceDate(), arguments_.autocallDates.back());
			Real maxMesher = 2, minMesher = 0.3;
			std::vector<std::vector<Real> > mustHave(assetNumber_, std::vector<Real>());
			std::vector<boost::shared_ptr<Fdm1dMesher> > ems;

			Size nb = arguments_.kibarrier->getBarrierNumbers();
			Size nb1 = arguments_.autocallConditions.back()->getBarrierNumbers();
			for (Size i = 0; i < assetNumber_; ++i) {
				if (nb > 0)
					mustHave[i].push_back(std::log(arguments_.kibarrier->getBarrier()[(nb>i) ? i : nb - 1]));
				else
					mustHave[i].push_back(std::log(arguments_.autocallConditions.back()->getBarrier()[(nb1>i) ? i : nb1 - 1]));
				//mustHave[i].push_back(logprices[i]);
				Real maxx = logprices[i] + std::log(maxMesher);
				Real minx = logprices[i] + std::log(minMesher);
				maxx = (maxx > std::log(200)) ? maxx : std::log(200);
				minx = (minx < std::log(30)) ? minx : std::log(30);
				std::sort(mustHave[i].begin(), mustHave[i].end());  
				mustHave[i].erase(std::unique(mustHave[i].begin(), mustHave[i].end()), mustHave[i].end());
				ems.push_back(boost::shared_ptr<Fdm1dMesher>(new MandatoryMesher(numGrid_[i], minx, maxx, mustHave[i])));
			}		
			boost::shared_ptr<FdmMesher> mesher;
			switch (assetNumber_) {
			case 1:
				mesher = boost::shared_ptr<FdmMesher>(new FdmMesherComposite(ems[0]));
				break;
			case 2:
				mesher = boost::shared_ptr<FdmMesher>(new FdmMesherComposite(ems[0], ems[1]));
				break;
			case 3:
				mesher = boost::shared_ptr<FdmMesher>(new FdmMesherComposite(ems[0], ems[1], ems[2]));
				break;
			default:
				QL_FAIL("Number of input processes is greater than 3.");
			}
			
			// 3. Calculator
			std::vector<boost::shared_ptr<FdmInnerValueCalculator> > calculators;
			boost::shared_ptr<FdmInnerValueCalculator> calculator;

			//HAVE KI Barrier?
			bool haveKIBarrier = arguments_.kibarrier->getBarrierNumbers() > 0;
			if (!haveKIBarrier) {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.terminalPayoff, mesher));
				for (Size i = 0; i < autocallPayoffs.size()-1; ++i)
					calculators.push_back(boost::shared_ptr<FdmAutocallInnerValue>(new FdmAutocallInnerValue(autocallPayoffs[i], mesher)));
				repeat = false;
			}
			else if (arguments_.isKI) {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.KIPayoff, mesher));
				for (Size i = 0; i < KIautocallPayoffs.size()-1; ++i)
					calculators.push_back(boost::shared_ptr<FdmAutocallInnerValue>(new FdmAutocallInnerValue(KIautocallPayoffs[i], mesher)));
				repeat = false;
			}
			else if (firstRound) {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.KIPayoff, mesher));
				for (Size i = 0; i < KIautocallPayoffs.size()-1; ++i)
					calculators.push_back(boost::shared_ptr<FdmAutocallInnerValue>(new FdmAutocallInnerValue(KIautocallPayoffs[i], mesher)));
				firstRound = false;
				type = firstKI;
			}
			else {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.terminalPayoff, mesher));
				for (Size i = 0; i < autocallPayoffs.size()-1; ++i)
					calculators.push_back(boost::shared_ptr<FdmAutocallInnerValue>(new FdmAutocallInnerValue(autocallPayoffs[i], mesher)));
				repeat = false;
				type = secondKI;
			}

			// 4. Step conditions
			std::list<std::vector<Time> > stoppingTimes;
			std::list<boost::shared_ptr<StepCondition<Array> > > stepConditions;
			DividendSchedule cashFlow = DividendSchedule(); //todo: Dividend
			Date refDate = disc_->referenceDate();
			DayCounter dayCounter = disc_->dayCounter();

			if (!cashFlow.empty()) {
				boost::shared_ptr<FdmDividendHandler> dividendCondition(new FdmDividendHandler(cashFlow, mesher, refDate, dayCounter, 0));
				stepConditions.push_back(dividendCondition);
				stoppingTimes.push_back(dividendCondition->dividendTimes());
			}


			for (Size i = 0; i < arguments_.autocallPayoffs.size()-1; ++i) {
				if (arguments_.autocallDates[i] > refDate) {
					boost::shared_ptr<FdmCallStepCondition> autocallCondition;
					if (type==firstKI || arguments_.isKI)
						autocallCondition = boost::shared_ptr<FdmCallStepCondition>(
							new FdmCallStepCondition(arguments_.autocallDates[i], refDate, dayCounter, mesher, calculators[i], arguments_.KIautocallConditions[i]));
					else
						autocallCondition = boost::shared_ptr<FdmCallStepCondition>(
							new FdmCallStepCondition(arguments_.autocallDates[i], refDate, dayCounter, mesher, calculators[i], arguments_.autocallConditions[i]));

					stepConditions.push_back(autocallCondition);
					stoppingTimes.push_back(autocallCondition->exerciseTimes());
				}
			}


			if (type == firstKI) {
				boost::shared_ptr<FdmRecordingStepCondition> recordingCondition(new FdmRecordingStepCondition(mesher));
				stepConditions.push_back(recordingCondition);
			}
			else if (type == secondKI) {
				std::map<Time, Array> temp = boost::dynamic_pointer_cast<FdmRecordingStepCondition>(conditions->conditions().back())->getValues();
				boost::shared_ptr<FdmWritingStepCondition> writingCondition(new FdmWritingStepCondition(mesher, temp, arguments_.kibarrier));
				stepConditions.push_back(writingCondition);
			}

			conditions = boost::shared_ptr<FdmStepConditionComposite>(new FdmStepConditionComposite(stoppingTimes, stepConditions));

			// 5. Boundary conditions
			const FdmBoundaryConditionSet boundaries;

			// 6. Solver
			const FdmSolverDesc solverDesc = { mesher, boundaries, conditions, calculator, maturity, tGrid_, dampingSteps_ };

			boost::shared_ptr<AutocallSolver> solver(
				new AutocallSolver(
					Handle<YieldTermStructure>(disc_),
					process_,
					solverDesc, schemeDesc_));

			// 7. Fetch Results
			Real mult = arguments_.notionalAmt / 100.0;
			Real x = prices[0], y=0, z=0;
			Real perturbations[3] = { 0.99, 1.0, 1.01 };
			if (assetNumber_ == 1) {
				Array values(3, 0.0);
				for (Size j = 0; j < 3; ++j)
					values[j] = mult * solver->valueAt(x*perturbations[j]);
				if (!repeat) {
					results_.value = values[1];
					results_.theta = std::vector<Real>(1, mult * solver->thetaAt(x) / 365.0);
					results_.delta.resize(0);
					results_.delta.push_back((values[2] - values[0]) / 2.0);
					results_.gamma.resize(0);
					results_.gamma.push_back(values[2] + values[0] - 2 * values[1]);
					results_.xgamma.resize(0);
				}
			} 
			else if (assetNumber_ == 2) {
				y = prices[1];
				Matrix values(3, 3, 0.0);				
				for (Size i = 0; i < 3; ++i)
					for (Size j = 0; j < 3; ++j)
						values[i][j] = mult * solver->valueAt(x*perturbations[i], y*perturbations[j]);

				if (!repeat) {
					results_.value = values[1][1];
					results_.theta = std::vector<Real>(1, mult * solver->thetaAt(x, y) / 365.0);

					results_.delta.resize(0);
					results_.delta.push_back((values[2][1] - values[0][1]) / 2.0);
					results_.delta.push_back((values[1][2] - values[1][0]) / 2.0);

					results_.gamma.resize(0);
					results_.gamma.push_back(values[2][1] + values[0][1] - 2 * values[1][1]);
					results_.gamma.push_back(values[1][2] + values[1][0] - 2 * values[1][1]);

					results_.xgamma = std::vector<std::vector<Real> >(2, std::vector<Real>(2, 0));
					results_.xgamma[1][0] = results_.xgamma[0][1] = (values[2][2] + values[0][0] - values[2][0] - values[0][2]) / 4.0;
				}
			}
			else if (assetNumber_ == 3) {
				y = prices[1];  z = prices[2];
				std::vector<Matrix> values(3, Matrix(3, 3, 0.0));
				for (Size i = 0; i < 3; ++i)
					for (Size j = 0; j < 3; ++j)
						for (Size k = 0; k < 3; ++k)
							values[i][j][k] = mult * solver->valueAt(x*perturbations[i], y*perturbations[j], z*perturbations[k]);

				if (!repeat) {
					results_.value = values[1][1][1];
					results_.theta = std::vector<Real>(1, mult * solver->thetaAt(x, y, z) / 365.0);

					results_.delta.resize(0);
					results_.delta.push_back((values[2][1][1] - values[0][1][1]) / 2.0);
					results_.delta.push_back((values[1][2][1] - values[1][0][1]) / 2.0);
					results_.delta.push_back((values[1][1][2] - values[1][1][0]) / 2.0);

					results_.gamma.resize(0);
					results_.gamma.push_back(values[2][1][1] + values[0][1][1] - 2 * values[1][1][1]);
					results_.gamma.push_back(values[1][2][1] + values[1][0][1] - 2 * values[1][1][1]);
					results_.gamma.push_back(values[1][1][2] + values[1][1][0] - 2 * values[1][1][1]);

					results_.xgamma = std::vector<std::vector<Real> >(3, std::vector<Real>(3, 0));
					results_.xgamma[1][0] = results_.xgamma[0][1] = (values[2][2][1] + values[0][0][1] - values[2][0][1] - values[0][2][1]) / 4.0;
					results_.xgamma[2][0] = results_.xgamma[0][2] = (values[2][1][2] + values[0][1][0] - values[2][1][0] - values[0][1][2]) / 4.0;
					results_.xgamma[2][1] = results_.xgamma[1][2] = (values[1][2][2] + values[1][0][0] - values[1][0][2] - values[1][2][0]) / 4.0;
				}
			}
			else
				QL_FAIL("Number of input processes is greater than 3.");

		}
	}
}
