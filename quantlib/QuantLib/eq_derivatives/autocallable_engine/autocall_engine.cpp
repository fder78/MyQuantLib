
#include <ql/exercise.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/meshers/fdmblackscholesmesher.hpp>
#include <ql/methods/finitedifferences/utilities/fdmdividendhandler.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>

#include <eq_derivatives\autocallable_engine\autocall_stepcondition.h>
#include <eq_derivatives\autocallable_engine\autocall_engine.h>
#include <eq_derivatives\autocallable_engine\autocall_calculator.h>
#include <eq_derivatives/autocallable_engine/autocall_solver.h>

namespace QuantLib {

	FdAutocallEngine::FdAutocallEngine(
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
		Real correlation,
		Size xGrid, Size yGrid,
		Size tGrid, Size dampingSteps,
		const FdmSchemeDesc& schemeDesc)
		: p1_(p1), p2_(p2), correlation_(correlation), xGrid_(xGrid), yGrid_(yGrid), tGrid_(tGrid),	dampingSteps_(dampingSteps), schemeDesc_(schemeDesc) {
	}

	void FdAutocallEngine::calculate() const {

		// 1. Payoff
		const boost::shared_ptr<BasketPayoff> payoff;
		// 1.1 AutoCall Condition
		const boost::shared_ptr<AutocallCondition> condition;
		// 1.2 AutoCall Payoff
		std::vector<boost::shared_ptr<BasketPayoff> > autocallPayoffs = arguments_.autocallPayoffs;

		// 2. Mesher
		const Time maturity = p1_->time(arguments_.autocallDates.back());
		const boost::shared_ptr<Fdm1dMesher> em1(new FdmBlackScholesMesher(
			xGrid_, p1_, maturity, p1_->x0(), Null<Real>(), Null<Real>(), 0.0001, 1.5, std::pair<Real, Real>(p1_->x0(), 0.1)));
		const boost::shared_ptr<Fdm1dMesher> em2(new FdmBlackScholesMesher(
			yGrid_, p2_, maturity, p2_->x0(), Null<Real>(), Null<Real>(), 0.0001, 1.5, std::pair<Real, Real>(p2_->x0(), 0.1)));
		const boost::shared_ptr<FdmMesher> mesher(new FdmMesherComposite(em1, em2));

		// 3. Calculator
		std::vector<boost::shared_ptr<FdmInnerValueCalculator> > calculators;
		for (Size i = 0; i < arguments_.autocallPayoffs.size(); ++i)
			calculators.push_back(boost::shared_ptr<FdmAutocallInnerValue>(new FdmAutocallInnerValue(autocallPayoffs[i], mesher)));

		boost::shared_ptr<FdmInnerValueCalculator> calculator;
		if (arguments_.kibarrier->getBarrier()>0 && arguments_.isKI)
			calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.KIPayoff, mesher));
		else if (arguments_.kibarrier->getBarrier()==Null<Real>())
			calculator = boost::shared_ptr<FdmInnerValueCalculator>(new FdmAutocallInnerValue(arguments_.terminalPayoff, mesher));

		// 4. Step conditions
		std::list<std::vector<Time> > stoppingTimes;
		std::list<boost::shared_ptr<StepCondition<Array> > > stepConditions;
		DividendSchedule cashFlow = DividendSchedule(); //todo: Dividend
		Date refDate = p1_->riskFreeRate()->referenceDate();
		DayCounter dayCounter = p1_->riskFreeRate()->dayCounter();

		if (!cashFlow.empty()) {
			boost::shared_ptr<FdmDividendHandler> dividendCondition(new FdmDividendHandler(cashFlow, mesher, refDate, dayCounter, 0));
			stepConditions.push_back(dividendCondition);
			stoppingTimes.push_back(dividendCondition->dividendTimes());
		}
		for (Size i = 0; i < arguments_.autocallPayoffs.size(); ++i) {
			boost::shared_ptr<FdmAutocallStepCondition> autocallCondition(
				new FdmAutocallStepCondition(arguments_.autocallDates[i], refDate, dayCounter, mesher, calculators[i], arguments_.autocallConditions[i]));
			stepConditions.push_back(autocallCondition);
			stoppingTimes.push_back(autocallCondition->exerciseTimes());
		}

		const boost::shared_ptr<FdmStepConditionComposite> conditions(new FdmStepConditionComposite(stoppingTimes, stepConditions));

		// 5. Boundary conditions
		const FdmBoundaryConditionSet boundaries;

		// 6. Solver
		const FdmSolverDesc solverDesc = { mesher, boundaries, conditions, calculator, maturity, tGrid_, dampingSteps_ };

		boost::shared_ptr<AutocallSolver> solver(
			new AutocallSolver(
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
