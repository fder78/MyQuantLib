
#include <ql/exercise.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/meshers/fdmblackscholesmesher.hpp>
#include <ql/methods/finitedifferences/utilities/fdmdividendhandler.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>

#include <ql/methods/finitedifferences/meshers/predefined1dmesher.hpp>
#include <eq_derivatives\autocallable_engine\autocall_stepcondition.h>
#include <eq_derivatives\autocallable_engine\autocall_engine.h>
#include <eq_derivatives\autocallable_engine\autocall_calculator.h>
#include <eq_derivatives/autocallable_engine/autocall_solver.h>

namespace QuantLib {

	FdAutocallEngine::FdAutocallEngine(
		const boost::shared_ptr<YieldTermStructure>& disc,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
		Real correlation,
		Size xGrid, Size yGrid,
		Size tGrid, Size dampingSteps,
		const FdmSchemeDesc& schemeDesc)
		: disc_(disc), p1_(p1), p2_(p2), correlation_(correlation), xGrid_(xGrid), yGrid_(yGrid), tGrid_(tGrid),	dampingSteps_(dampingSteps), schemeDesc_(schemeDesc) {
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
			if (arguments_.isKI && arguments_.kibarrier->getBarrier()!=Null<Real>())
				results_.value = arguments_.KIPayoff->operator()(prices) * arguments_.notionalAmt / 100.0;
			results_.theta = std::vector<Real>(1, 0);
			results_.delta = std::vector<Real>(2, 0);
			results_.gamma = std::vector<Real>(2, 0);
			results_.xgamma = std::vector<Real>(1, 0);
			return;
		}

		bool repeat = true, firstRound = true;
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
			Real mustHave;
			if (arguments_.kibarrier->getBarrier() != Null<Real>())
				mustHave = std::log(arguments_.kibarrier->getBarrier());
			else
				mustHave = std::log(arguments_.autocallConditions.back()->getBarrier());
			std::vector<Real> xs(xGrid_ + 1, 0.0), ys(yGrid_ + 1, 0.0);
			Real logx = std::log(p1_->x0()); Real logy = std::log(p2_->x0());
			Real maxx = logx + std::log(maxMesher), maxy = logy + std::log(maxMesher);
			Real minx = logx + std::log(minMesher), miny = logy + std::log(minMesher);
			Real margin = std::log(2);
			maxx = (maxx < mustHave + margin) ? mustHave + margin : maxx; maxy = (maxy < mustHave + margin) ? mustHave + margin : maxy;
			minx = (minx > mustHave - margin) ? mustHave - margin : minx; miny = (miny > mustHave - margin) ? mustHave - margin : miny;
			Size xg2 = (Size)((maxx - mustHave) / (maxx - minx) * xGrid_), xg1 = xGrid_ - xg2;
			Size yg2 = (Size)((maxy - mustHave) / (maxy - miny) * yGrid_), yg1 = yGrid_ - yg2;
			Real dx1 = (mustHave - minx) / xg1, dx2 = (maxx - mustHave) / xg2;
			Real dy1 = (mustHave - miny) / yg1, dy2 = (maxy - mustHave) / yg2;
			for (Size i = 0; i <= xGrid_; ++i) {
				if (i < xg1)
					xs[i] = minx + dx1 * i;
				else
					xs[i] = mustHave + dx2 * (i - xg1);
			}
			for (Size i = 0; i <= yGrid_; ++i) {
				if (i < yg1)
					ys[i] = miny + dy1 * i;
				else
					ys[i] = mustHave + dy2 * (i - yg1);
			}
			const boost::shared_ptr<Fdm1dMesher> em1(new Predefined1dMesher(xs));
			const boost::shared_ptr<Fdm1dMesher> em2(new Predefined1dMesher(ys));
			const boost::shared_ptr<FdmMesher> mesher(new FdmMesherComposite(em1, em2));
			//const boost::shared_ptr<Fdm1dMesher> em1(new MandatoryMesher(xGrid_, minx, maxx, mustHave);

			// 3. Calculator
			std::vector<boost::shared_ptr<FdmInnerValueCalculator> > calculators;
			for (Size i = 0; i < arguments_.autocallPayoffs.size(); ++i)
				calculators.push_back(boost::shared_ptr<FdmAutocallInnerValue>(new FdmAutocallInnerValue(autocallPayoffs[i], mesher)));

			boost::shared_ptr<FdmInnerValueCalculator> calculator;

			if (arguments_.kibarrier->getBarrier() != Null<Real>() && firstRound) {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.KIPayoff, mesher));
				firstRound = false;
				if (arguments_.isKI) 
					repeat = false;
			}
			else {
				calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.terminalPayoff, mesher));
				repeat = false;
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

			const boost::shared_ptr<FdmStepConditionComposite> conditions(new FdmStepConditionComposite(stoppingTimes, stepConditions));

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
