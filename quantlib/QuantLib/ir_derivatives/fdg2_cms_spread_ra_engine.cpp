
#include "fdg2_cms_spread_ra_engine.hpp"
#include "fdmcmsspreadswapinnervalue.hpp"
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
        Size tGrid, Size xGrid, Size yGrid,
        Size dampingSteps, Real invEps,
        const FdmSchemeDesc& schemeDesc)
		: GenericModelEngine<G2, FloatFloatSwaption::arguments, FloatFloatSwaption::results>(model), 
      tGrid_(tGrid),
      xGrid_(xGrid),
      yGrid_(yGrid),
      dampingSteps_(dampingSteps),
      invEps_(invEps),
      schemeDesc_(schemeDesc) {
    }

    void FdG2CmsSpreadRAEngine::calculate() const {

        // 1. Term structure
        const Handle<YieldTermStructure> ts = model_->termStructure();

        // 2. Mesher
        const DayCounter dc = ts->dayCounter();
        const Date referenceDate = ts->referenceDate();
        const Time maturity = dc.yearFraction(referenceDate,
                                              arguments_.exercise->lastDate());

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
        const std::vector<Date>& exerciseDates = arguments_.exercise->dates();
        std::map<Time, Date> t2d;

        for (Size i=0; i < exerciseDates.size(); ++i) {
            const Time t = dc.yearFraction(referenceDate, exerciseDates[i]);
            QL_REQUIRE(t >= 0, "exercise dates must not contain past date");
            t2d[t] = exerciseDates[i];
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

		//set coupon pricer///////////////////////////////////////TEST
		//boost::shared_ptr<CmsCouponPricer> cmsPricer(new LinearTsrPricer(Handle<SwaptionVolatilityStructure>(swaptionVol_), Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(0.0)))));
		//boost::shared_ptr<FloatingRateCouponPricer> pricer(new LognormalCmsSpreadPricer(cmsPricer, Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(0.0)))));
		//setCouponPricer(arguments_.swap->leg1(), pricer);

        const boost::shared_ptr<FdmInnerValueCalculator> calculator(
             new FdmCmsSpreadSwapInnerValue<G2>(model_.currentLink(), fwdModel, arguments_.swap, t2d, mesher, 0));

        // 4. Step conditions
		const boost::shared_ptr<FdmStepConditionComposite> c1 =
			FdmStepConditionComposite::vanillaComposite(
				DividendSchedule(), arguments_.exercise,
				mesher, calculator, referenceDate, dc);
        const boost::shared_ptr<FdmStepConditionComposite> c2 =
             FdmStepConditionComposite::vanillaComposite(
                 DividendSchedule(), arguments_.exercise,
                 mesher, calculator, referenceDate, dc);

		std::list<std::vector<Time> > stoppingTimes;
		stoppingTimes.push_back(c2->stoppingTimes());
		stoppingTimes.push_back(c1->stoppingTimes());
		FdmStepConditionComposite::Conditions cs;
		cs.push_back(c2);
		cs.push_back(c1);
		const boost::shared_ptr<FdmStepConditionComposite> conditions(new FdmStepConditionComposite(stoppingTimes, cs));



        // 5. Boundary conditions
        const FdmBoundaryConditionSet boundaries;

        // 6. Solver
        FdmSolverDesc solverDesc = { mesher, boundaries, conditions,
                                     calculator, maturity,
                                     tGrid_, dampingSteps_ };

        const boost::scoped_ptr<FdmG2Solver> solver(
            new FdmG2Solver(model_, solverDesc, schemeDesc_));

        results_.value = solver->valueAt(0.0, 0.0);
    }
}
