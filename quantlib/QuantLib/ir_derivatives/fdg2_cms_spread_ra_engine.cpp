
#include "fdg2_cms_spread_ra_engine.hpp"
#include "fdg2_cms_spread_swap_innervalue.hpp"
#include "fdg2_cms_spread_ra_stepcondition.h"

#include "exercise_call_innervalue.hpp"
#include <ql/experimental/coupons/swapspreadindex.hpp>
#include <ql/experimental/coupons/cmsspreadcoupon.hpp>
#include <ql/experimental/coupons/lognormalcmsspreadpricer.hpp>
#include <ql/cashflows/lineartsrpricer.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/handle.hpp>

#include <ql/exercise.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/processes/ornsteinuhlenbeckprocess.hpp>
#include <ql/methods/finitedifferences/solvers/fdmsolverdesc.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmsimpleprocess1dmesher.hpp>
#include <ql/methods/finitedifferences/solvers/fdmg2solver.hpp>

#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>

#include <boost/scoped_ptr.hpp>

namespace QuantLib {

    FdG2CmsSpreadRAEngine::FdG2CmsSpreadRAEngine(
        const boost::shared_ptr<G2>& model,
		const Real pastAccrual,
		const Real pastFixing,
        Size tGrid, Size xGrid, Size yGrid,
        Size dampingSteps, Real invEps,
        const FdmSchemeDesc& schemeDesc)
		: GenericModelEngine<G2, FloatFloatSwaption::arguments, FloatFloatSwaption::results>(model), 
      tGrid_(tGrid),
      xGrid_(xGrid),
      yGrid_(yGrid),
      dampingSteps_(dampingSteps),
      invEps_(invEps),
      schemeDesc_(schemeDesc),
	  pastAccrual_(pastAccrual), pastFixing_(pastFixing) {}

    void FdG2CmsSpreadRAEngine::calculate() const {

        // 1. Term structure
        const Handle<YieldTermStructure> ts = model_->termStructure();

        // 2. Mesher
        const DayCounter dc = ts->dayCounter();
        const Date referenceDate = ts->referenceDate();
		const Time maturity = dc.yearFraction(referenceDate, arguments_.leg1PayDates.back());

        const boost::shared_ptr<OrnsteinUhlenbeckProcess> process1(
            new OrnsteinUhlenbeckProcess(model_->a(), model_->sigma()));

        const boost::shared_ptr<OrnsteinUhlenbeckProcess> process2(
            new OrnsteinUhlenbeckProcess(model_->b(), model_->eta()));

        const boost::shared_ptr<Fdm1dMesher> xMesher(
            new FdmSimpleProcess1dMesher(xGrid_,process1,maturity,1,invEps_));

        const boost::shared_ptr<Fdm1dMesher> yMesher(
            new FdmSimpleProcess1dMesher(yGrid_,process2,maturity,1,invEps_));

        const boost::shared_ptr<FdmMesher> mesher(
            new FdmMesherComposite(xMesher, yMesher));

        // 3. Inner Value Calculator
		// 4. Step conditions
		
		//call stepcondition
		const boost::shared_ptr<FdmInnerValueCalculator> callCalculator(
			new FdmExerciseCallInnerValue(0.0));
		const boost::shared_ptr<FdmStepConditionComposite> c2 =
			FdmStepConditionComposite::vanillaComposite(DividendSchedule(), arguments_.exercise, mesher, callCalculator, referenceDate, dc);

		//accrual stepcondition		
		std::vector<Time> payTimes;
		std::vector<Time> floatingTimes;
		for (Size i = 0; i < arguments_.leg1PayDates.size(); ++i) {
			payTimes.push_back(dc.yearFraction(referenceDate, arguments_.leg1PayDates[i]));
		}
		for (Size i = 0; i < arguments_.leg2PayDates.size(); ++i) {
			floatingTimes.push_back(dc.yearFraction(referenceDate, arguments_.leg2PayDates[i]));
		}
		std::vector<Time> accrualTimes;
		std::map<Time, Time> timeInterval;		
		std::map<Time, std::pair<Size, Time> > cfIndex;
		dc.yearFraction(referenceDate, arguments_.leg1PayDates.back());
		for (Size i = 0; i < payTimes.size(); ++i) {
			if (payTimes[i] > 0.0) {
				Time t = (i == 0) ? 0.0 : (payTimes[i - 1] <= 0.0) ? 0.0 : payTimes[i - 1];
				Size n = unsigned int(tGrid_ * (payTimes[i] - t));
				Real dt = (payTimes[i] - t) / n;
				for (Size k = 0; k < n; ++k) {
					accrualTimes.push_back(t + k*dt);
					timeInterval[accrualTimes.back()] = dt;
					std::pair<Size, Time> idxPair(i, payTimes[i]);
					cfIndex[accrualTimes.back()] = idxPair;
				}
			}
		}

        const Handle<YieldTermStructure> disTs = model_->termStructure();
		boost::shared_ptr<SwapSpreadIndex> swapIndex = boost::dynamic_pointer_cast<SwapSpreadIndex>(arguments_.swap->index1());
        const Handle<YieldTermStructure> fwdTs = swapIndex->swapIndex1()->forwardingTermStructure();

        QL_REQUIRE(fwdTs->dayCounter() == disTs->dayCounter(),
                "day counter of forward and discount curve must match");
        QL_REQUIRE(fwdTs->referenceDate() == disTs->referenceDate(),
                "reference date of forward and discount curve must match");

        const boost::shared_ptr<G2> fwdModel(
            new G2(fwdTs, model_->a(), model_->sigma(), model_->b(), model_->eta(), model_->rho()));

        const boost::shared_ptr<FdmInnerValueCalculator> calculator(
             new FdmCmsSpreadSwapInnerValue<G2>(model_.currentLink(), fwdModel, arguments_.swap, floatingTimes, accrualTimes, timeInterval, cfIndex, mesher, 0));
        			
		boost::shared_ptr<FdmRAStepCondition> stepcondition(new FdmRAStepCondition(accrualTimes, mesher, calculator));
		
		//StepCondition Composite
		const std::list<std::vector<Time> > dateslist(1, stepcondition->accrualTimes());
		const std::list<boost::shared_ptr<StepCondition<Array> > > condlist(1, stepcondition);
		const boost::shared_ptr<FdmStepConditionComposite> c1(new FdmStepConditionComposite(dateslist, condlist));		
		
		std::list<std::vector<Time> > stoppingTimes;
		stoppingTimes.push_back(c1->stoppingTimes());
		stoppingTimes.push_back(c2->stoppingTimes());
		FdmStepConditionComposite::Conditions cs;
		cs.push_back(c1);
		cs.push_back(c2);
		const boost::shared_ptr<FdmStepConditionComposite> conditions(new FdmStepConditionComposite(stoppingTimes, cs));
		
        // 5. Boundary conditions
        const FdmBoundaryConditionSet boundaries;

        // 6. Solver
        FdmSolverDesc solverDesc = { mesher, boundaries, conditions,
			callCalculator, maturity,
			1, dampingSteps_ };

        const boost::scoped_ptr<FdmG2Solver> solver(
            new FdmG2Solver(model_, solverDesc, schemeDesc_));

        results_.value = solver->valueAt(0.0, 0.0);
		
		// ±â´©ÀûÄíÆù
		std::vector<Real> df(2,0);
		std::vector<Time> tau(2,0);
		std::vector<Leg> leg(1, arguments_.swap->leg1());
		leg.push_back(arguments_.swap->leg2());

		for (Size k = 0; k < 2; ++k) {
			for (Size i = 0; i < leg[k].size(); ++i) {
				if (!leg[k][i]->hasOccurred(referenceDate)) {
					df[k] = disTs->discount(leg[k][i]->date());
					tau[k] = boost::dynamic_pointer_cast<Coupon>(leg[k][i])->accrualPeriod();
					break;
				}
			}
		}
		Real initialAdjust = pastAccrual_ * tau[0] * df[0]
			- (pastFixing_ + arguments_.swap->spread2()[0]) * tau[1] * df[1];
		
		results_.value += initialAdjust * ((arguments_.swap->type() == VanillaSwap::Payer) ? -1 : +1);
		results_.value *= arguments_.nominal1[0];
    }
}
