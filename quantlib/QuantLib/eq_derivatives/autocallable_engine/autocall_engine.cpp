
#include <ql/exercise.hpp>
#include <ql/methods/finitedifferences/solvers/fdm2dblackscholessolver.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/meshers/fdmblackscholesmesher.hpp>
#include <ql/methods/finitedifferences/utilities/fdmdividendhandler.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>

#include <eq_derivatives\autocallable_engine\autocall_stepcondition.h>
#include <eq_derivatives\autocallable_engine\autocall_engine.h>
#include <eq_derivatives\autocallable_engine\autocall_calculator.h>

namespace QuantLib {

	FdAutocallEngine::FdAutocallEngine(
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
		Real correlation,
		Size xGrid, Size yGrid,
		Size tGrid, Size dampingSteps,
		const FdmSchemeDesc& schemeDesc)
		: p1_(p1), p2_(p2), correlation_(correlation), xGrid_(xGrid), yGrid_(yGrid), tGrid_(tGrid),	dampingSteps_(dampingSteps), schemeDesc_(schemeDesc) {}

	void FdAutocallEngine::calculate() const {
		// 1. Payoff
		const boost::shared_ptr<BasketPayoff> payoff = boost::dynamic_pointer_cast<BasketPayoff>(arguments_.payoff);
		// 1.1 AutoCall Condition
		const boost::shared_ptr<AutocallCondition> condition(new MinUpCondition(100));
		// 1.2 AutoCall Payoff
		const boost::shared_ptr<BasketPayoff> autocallPayoff = boost::dynamic_pointer_cast<BasketPayoff>(arguments_.payoff);

		// 2. Mesher
		const Time maturity = p1_->time(arguments_.exercise->lastDate());
		const boost::shared_ptr<Fdm1dMesher> em1(
			new FdmBlackScholesMesher(
				xGrid_, p1_, maturity, p1_->x0(),
				Null<Real>(), Null<Real>(), 0.0001, 1.5,
				std::pair<Real, Real>(p1_->x0(), 0.1)));

		const boost::shared_ptr<Fdm1dMesher> em2(
			new FdmBlackScholesMesher(
				yGrid_, p2_, maturity, p2_->x0(),
				Null<Real>(), Null<Real>(), 0.0001, 1.5,
				std::pair<Real, Real>(p2_->x0(), 0.1)));

		const boost::shared_ptr<FdmMesher> mesher(new FdmMesherComposite(em1, em2));

		// 3. Calculator
		const boost::shared_ptr<FdmInnerValueCalculator> calculator(new FdmAutocallInnerValue(autocallPayoff, mesher));

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
		boost::shared_ptr<FdmAutocallStepCondition> autocallCondition(
				new FdmAutocallStepCondition(arguments_.exercise->dates(), refDate, dayCounter, mesher, calculator, condition));
		stepConditions.push_back(autocallCondition);
		stoppingTimes.push_back(autocallCondition->exerciseTimes());

		const boost::shared_ptr<FdmStepConditionComposite> conditions(new FdmStepConditionComposite(stoppingTimes, stepConditions));

		// 5. Boundary conditions
		const FdmBoundaryConditionSet boundaries;

		// 6. Solver
		const FdmSolverDesc solverDesc = { mesher, boundaries, conditions, calculator, maturity, tGrid_, dampingSteps_ };

		boost::shared_ptr<Fdm2dBlackScholesSolver> solver(
			new Fdm2dBlackScholesSolver(
				Handle<GeneralizedBlackScholesProcess>(p1_),
				Handle<GeneralizedBlackScholesProcess>(p2_),
				correlation_, solverDesc, schemeDesc_));

		const Real x = p1_->x0();
		const Real y = p2_->x0();

		results_.value = solver->valueAt(x, y);
		results_.theta = std::vector<Real>(1, solver->thetaAt(x, y));

		results_.delta.resize(0);
		results_.delta.push_back(solver->deltaXat(x, y));
		results_.delta.push_back(solver->deltaYat(x, y));

		results_.gamma.resize(0);
		results_.gamma.push_back(solver->gammaXat(x, y));
		results_.gamma.push_back(solver->gammaYat(x, y));
	}
}
