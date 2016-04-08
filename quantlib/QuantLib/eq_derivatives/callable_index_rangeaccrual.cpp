
#include "callable_index_rangeaccrual.hpp"

namespace QuantLib {

    CallableIndexRangeAccrual::CallableIndexRangeAccrual(
		const Real& notional,
		const std::vector<Real>& basePrices,
		const std::vector<std::pair<Real, Real> >& rabounds,
		const Schedule& couponDates,
		const Schedule& paymentDates,
		const boost::shared_ptr<Payoff>& payoff,
		const boost::shared_ptr<Exercise>& exercise,
		const Size inRangeCount)
    : MultiAssetOption(payoff, exercise), notional_(notional), basePrices_(basePrices), rabounds_(rabounds), 
		couponDates_(couponDates), paymentDates_(paymentDates), inRangeCount_(inRangeCount) {}


	void CallableIndexRangeAccrual::setupArguments(PricingEngine::arguments* args) const {

		MultiAssetOption::setupArguments(args);
		CallableIndexRangeAccrual::arguments* moreArgs = dynamic_cast<CallableIndexRangeAccrual::arguments*>(args);
		QL_REQUIRE(moreArgs != 0, "wrong argument type");
		moreArgs->notional = notional_;
		moreArgs->basePrices = basePrices_;
		moreArgs->rabounds = rabounds_;
		moreArgs->basePrices = basePrices_;
		moreArgs->couponDates = couponDates_;
		moreArgs->paymentDates = paymentDates_;
		moreArgs->inRangeCount = inRangeCount_;
	}


}

