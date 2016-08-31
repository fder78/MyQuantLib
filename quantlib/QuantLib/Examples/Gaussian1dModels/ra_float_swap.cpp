
#include"ra_float_swap.hpp"
#include <ql/cashflows/iborcoupon.hpp>
#include <ql/cashflows/cmscoupon.hpp>
#include <ql/cashflows/capflooredcoupon.hpp>
#include <ql/cashflows/cashflowvectors.hpp>
#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <ql/experimental/coupons/cmsspreadcoupon.hpp> // internal
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

namespace QuantLib {

	RAFloatSwap::RAFloatSwap(
		const VanillaSwap::Type type,
		const Real nominal1,
		const Real nominal2,
		const Schedule &schedule1,
		const Real& fixedRate1,
		const boost::shared_ptr<InterestRateIndex> &index1,
		const std::pair<Real, Real>& indexRange,
		const DayCounter &dayCount1,
		const Schedule &schedule2,
		const boost::shared_ptr<InterestRateIndex> &index2,
		const DayCounter &dayCount2,

		const bool intermediateCapitalExchange,
		const bool finalCapitalExchange,
		const Real gearing1,
		const Real spread1,
		const Real cappedRate1,
		const Real flooredRate1,
		const Real gearing2,
		const Real spread2,
		const Real cappedRate2,
		const Real flooredRate2,
		boost::optional<BusinessDayConvention> paymentConvention1,
		boost::optional<BusinessDayConvention> paymentConvention2)
		: FloatFloatSwap(type, nominal1, nominal2, schedule1, index1, dayCount1,
			schedule2, index2, dayCount2, intermediateCapitalExchange, finalCapitalExchange,
			gearing1, spread1, cappedRate1, flooredRate1, gearing2, spread2, cappedRate2, flooredRate2,
			paymentConvention1, paymentConvention2),
		indexRange_(std::vector<std::pair<Real,Real> >(schedule1.size() - 1, indexRange)),
		fixedRate_(std::vector<Rate>(schedule1.size() - 1, fixedRate1)) { }

	RAFloatSwap::RAFloatSwap(
		const VanillaSwap::Type type,
		const std::vector<Real> &nominal1,
		const std::vector<Real> &nominal2,
		const Schedule &schedule1,
		const std::vector<Real>& fixedRate1,
		const boost::shared_ptr<InterestRateIndex> &index1,
		const std::vector<std::pair<Real, Real> >& indexRange,
		const DayCounter &dayCount1,
		const Schedule &schedule2,
		const boost::shared_ptr<InterestRateIndex> &index2,
		const DayCounter &dayCount2,

		const bool intermediateCapitalExchange,
		const bool finalCapitalExchange,
		const std::vector<Real> &gearing1,
		const std::vector<Real> &spread1,
		const std::vector<Real> &cappedRate1,
		const std::vector<Real> &flooredRate1,
		const std::vector<Real> &gearing2,
		const std::vector<Real> &spread2,
		const std::vector<Real> &cappedRate2,
		const std::vector<Real> &flooredRate2,
		boost::optional<BusinessDayConvention> paymentConvention1,
		boost::optional<BusinessDayConvention> paymentConvention2)
		: FloatFloatSwap(type, nominal1, nominal2, schedule1, index1, dayCount1,
			schedule2, index2, dayCount2, intermediateCapitalExchange, finalCapitalExchange,
			gearing1, spread1, cappedRate1, flooredRate1, gearing2, spread2, cappedRate2, flooredRate2,
			paymentConvention1, paymentConvention2),
			indexRange_(indexRange), fixedRate_(fixedRate1) { }

    void RAFloatSwap::setupArguments(PricingEngine::arguments *args) const {

        FloatFloatSwap::setupArguments(args);

        RAFloatSwap::arguments *arguments = dynamic_cast<RAFloatSwap::arguments *>(args);

        if(!arguments)
            return; // swap engine ... // QL_REQUIRE(arguments != 0, "argument type does not match");

		arguments->indexRange = indexRange_;
		arguments->fixedRate = fixedRate_;
    }

    void RAFloatSwap::setupExpired() const { FloatFloatSwap::setupExpired(); }

    void RAFloatSwap::fetchResults(const PricingEngine::results *r) const {
        FloatFloatSwap::fetchResults(r);
    }

    void RAFloatSwap::arguments::validate() const {
        FloatFloatSwap::arguments::validate();
    }

    void RAFloatSwap::results::reset() { FloatFloatSwap::results::reset(); }
}
