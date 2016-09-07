
#include <ql/exercise.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/meshers/fdmblackscholesmesher.hpp>
#include <ql/methods/finitedifferences/utilities/fdmdividendhandler.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>

#include <eq_derivatives/autocallable_engine/mesher_mandatory.h>
#include <eq_derivatives/autocallable_engine/autocall_stepcondition.h>
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
		: disc_(disc), p1_(p1), p2_(p2), correlation_(correlation), xGrid_(xGrid), yGrid_(yGrid), tGrid_(tGrid), dampingSteps_(dampingSteps), schemeDesc_(schemeDesc) {
	}

	void FdAutocallEngine::calculate() const {

		Array prices(2), logprices(2);
		prices[0] = p1_->x0(); prices[1] = p2_->x0();
		logprices[0] = std::log(prices[0]); logprices[1] = std::log(prices[1]);
		for (Size i = 0; i < arguments_.autocallDates.size(); ++i) {
			if (Settings::instance().evaluationDate() == arguments_.autocallDates[i]) {
				if (arguments_.autocallConditions[i]->operator()(logprices)) {
					results_.value = arguments_.autocallPayoffs[i]->operator()(prices) * arguments_.notionalAmt / 100.0;
					results_.theta = std::vector<Real>(1, 0);
					results_.delta = std::vector<Real>(2, 0);
					results_.gamma = std::vector<Real>(2, 0);
					results_.xgamma = std::vector<Real>(1, 0);
					return;
				}
			}
		}
		if (Settings::instance().evaluationDate() == arguments_.autocallDates.back()) {
			results_.value = arguments_.terminalPayoff->operator()(prices) * arguments_.notionalAmt / 100.0;
			if (arguments_.isKI && arguments_.kibarrier->getBarrier() != Null<Real>())
				results_.value = arguments_.KIPayoff->operator()(prices) * arguments_.notionalAmt / 100.0;
			results_.theta = std::vector<Real>(1, 0);
			results_.delta = std::vector<Real>(2, 0);
			results_.gamma = std::vector<Real>(2, 0);
			results_.xgamma = std::vector<Real>(1, 0);
			return;
		}

		enum CalcType { None, firstKI, secondKI };
		CalcType type = None;
		bool repeat = true, firstRound = true;
		boost::shared_ptr<FdmStepConditionComposite> conditions;


		while (repeat) {
			// 1. Payoff
			const boost::shared_ptr<BasketPayoff> payoff;
			// 1.1 AutoCall Condition
			const boost::shared_ptr<AutocallCondition> condition;
			// 1.2 AutoCall Payoff
			std::vector<boost::shared_ptr<BasketPayoff> > autocallPayoffs = arguments_.autocallPayoffs;

			// 2. Mesher
			const Time maturity = disc_->dayCounter().yearFraction(disc_->referenceDate(), arguments_.autocallDates.back());
			Real maxMesher = 5, minMesher = 0.2;
			std::vector<Real> mustHavex, mustHavey;
			if (arguments_.kibarrier->getBarrier() != Null<Real>()) {
				mustHavex.push_back(std::log(arguments_.kibarrier->getBarrier()));
				mustHavey.push_back(std::log(arguments_.kibarrier->getBarrier()));
			}
			else {
				mustHavex.push_back(std::log(arguments_.autocallConditions.back()->getBarrier()));
				mustHavey.push_back(std::log(arguments_.autocallConditions.back()->getBarrier()));
			}
			Real logx = std::log(p1_->x0()); Real logy = std::log(p2_->x0());
			mustHavex.push_back(logx); mustHavey.push_back(logy);

			Real maxx = logx + std::log(maxMesher), maxy = logy + std::log(maxMesher);
			Real minx = logx + std::log(minMesher), miny = logy + std::log(minMesher);
			std::sort(mustHavex.begin(), mustHavex.end());  mustHavex.erase(std::unique(mustHavex.begin(), mustHavex.end()), mustHavex.end());
			std::sort(mustHavey.begin(), mustHavey.end());  mustHavey.erase(std::unique(mustHavey.begin(), mustHavey.end()), mustHavey.end());
			const boost::shared_ptr<Fdm1dMesher> em1(new MandatoryMesher(xGrid_, minx, maxx, mustHavex));
			const boost::shared_ptr<Fdm1dMesher> em2(new MandatoryMesher(yGrid_, miny, maxy, mustHavey));
			const boost::shared_ptr<FdmMesher> mesher(new FdmMesherComposite(em1, em2));

			// 3. Calculator
			std::vector<boost::shared_ptr<FdmInnerValueCalculator> > calculators;
			for (Size i = 0; i < arguments_.autocallPayoffs.size(); ++i)
				calculators.push_back(boost::shared_ptr<FdmAutocallInnerValue>(new FdmAutocallInnerValue(autocallPayoffs[i], mesher)));

			boost::shared_ptr<FdmInnerValueCalculator> calculator;

			//HAVE KI Barrier?
			bool haveKIBarrier = arguments_.kibarrier->getBarrier() != Null<Real>();
			if (!haveKIBarrier) {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.terminalPayoff, mesher));
				repeat = false;
			}
			else if (arguments_.isKI) {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.KIPayoff, mesher));
				repeat = false;
			}
			else if (firstRound) {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.KIPayoff, mesher));
				firstRound = false;
				type = firstKI;
			}
			else {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.terminalPayoff, mesher));
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
			for (Size i = 0; i < arguments_.autocallPayoffs.size(); ++i) {
				if (arguments_.autocallDates[i] > refDate) {
					boost::shared_ptr<FdmAutocallStepCondition> autocallCondition(
						new FdmAutocallStepCondition(arguments_.autocallDates[i], refDate, dayCounter, mesher, calculators[i], arguments_.autocallConditions[i]));
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
					Handle<GeneralizedBlackScholesProcess>(p1_),
					Handle<GeneralizedBlackScholesProcess>(p2_),
					correlation_, solverDesc, schemeDesc_));

			const Real x = p1_->x0();
			const Real y = p2_->x0();
			Real mult = arguments_.notionalAmt / 100.0;

			Matrix values(3, 3, 0.0);
			Real perturbations[3] = { 0.99, 1.0, 1.01 };
			for (Size i = 0; i < 3; ++i) {
				for (Size j = 0; j < 3; ++j) {
					values[i][j] = mult * solver->valueAt(x*perturbations[i], y*perturbations[j]);
				}
			}

			if (!repeat) {
				results_.value = values[1][1];
				results_.theta = std::vector<Real>(1, mult * solver->thetaAt(x, y) / 365.0);

				results_.delta.resize(0);
				results_.delta.push_back((values[2][1] - values[0][1]) / 2.0);
				results_.delta.push_back((values[1][2] - values[1][0]) / 2.0);

				results_.gamma.resize(0);
				results_.gamma.push_back(values[2][1] + values[0][1] - 2 * values[1][1]);
				results_.gamma.push_back(values[1][2] + values[1][0] - 2 * values[1][1]);

				results_.xgamma.resize(0);
				results_.xgamma.push_back((values[2][2] + values[0][0] - values[2][0] - values[0][2]) / 4.0);
			}
		}
	}
}
