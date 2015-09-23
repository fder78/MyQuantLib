
#include "cms_spread_ra_coupon.hpp"
#include <ql/cashflows/cashflowvectors.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/math/distributions/normaldistribution.hpp>
#include <ql/time/schedule.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

#include <cmath>

namespace QuantLib {

    //===========================================================================//
    //                         CmsSpreadRangeAccrualCoupon                        //
    //===========================================================================//

    CmsSpreadRangeAccrualCoupon::CmsSpreadRangeAccrualCoupon(
                const Date& paymentDate,
                Real nominal,
				const boost::shared_ptr<SwapSpreadIndex>& index,
                const Date& startDate,                                  // S
                const Date& endDate,                                    // T
                Natural fixingDays,
                const DayCounter& dayCounter,
                Real gearing,
                Rate spread,
                const Date& refPeriodStart,
                const Date& refPeriodEnd,
                const boost::shared_ptr<Schedule>&  observationsSchedule,
                Real lowerTrigger,                                    // l
                Real upperTrigger                                     // u
        )
    : FloatingRateCoupon(paymentDate, nominal, startDate, endDate,
                         fixingDays, index, gearing, spread,
                         refPeriodStart, refPeriodEnd, dayCounter),
    observationsSchedule_(observationsSchedule),
    lowerTrigger_(lowerTrigger),
    upperTrigger_(upperTrigger){

        QL_REQUIRE(lowerTrigger_<upperTrigger,
                   "lowerTrigger_>=upperTrigger");
        QL_REQUIRE(observationsSchedule_->startDate()==startDate,
                   "incompatible start date");
        QL_REQUIRE(observationsSchedule_->endDate()==endDate,
                   "incompatible end date");

        observationDates_ = observationsSchedule_->dates();
        observationDates_.pop_back();                       //remove end date
        observationDates_.erase(observationDates_.begin()); //remove start date
        observationsNo_ = observationDates_.size();

        const Handle<YieldTermStructure>& rateCurve = index->swapIndex1()->forwardingTermStructure();
        Date referenceDate = rateCurve->referenceDate();

        startTime_ = dayCounter.yearFraction(referenceDate, startDate);
        endTime_ = dayCounter.yearFraction(referenceDate, endDate);
        for(Size i=0;i<observationsNo_;i++) {
            observationTimes_.push_back(
                dayCounter.yearFraction(referenceDate, observationDates_[i]));
        }

     }

    void CmsSpreadRangeAccrualCoupon::accept(AcyclicVisitor& v) {
        Visitor<CmsSpreadRangeAccrualCoupon>* v1 =
            dynamic_cast<Visitor<CmsSpreadRangeAccrualCoupon>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            FloatingRateCoupon::accept(v);
    }

    Real CmsSpreadRangeAccrualCoupon::priceWithoutOptionality(
           const Handle<YieldTermStructure>& discountingCurve) const {
        return accrualPeriod() * (gearing_*indexFixing()+spread_) *
               nominal() * discountingCurve->discount(date());
    }


    CmsSpreadRangeAccrualLeg::CmsSpreadRangeAccrualLeg(
                            const Schedule& schedule,
							const boost::shared_ptr<SwapSpreadIndex>& index)
    : schedule_(schedule), index_(index),
      paymentAdjustment_(Following),
      observationConvention_(ModifiedFollowing) {}

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withNotionals(Real notional) {
        notionals_ = std::vector<Real>(1,notional);
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withNotionals(
                                         const std::vector<Real>& notionals) {
        notionals_ = notionals;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withPaymentDayCounter(
                                               const DayCounter& dayCounter) {
        paymentDayCounter_ = dayCounter;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withPaymentAdjustment(
                                           BusinessDayConvention convention) {
        paymentAdjustment_ = convention;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withFixingDays(Natural fixingDays) {
        fixingDays_ = std::vector<Natural>(1,fixingDays);
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withFixingDays(
                                     const std::vector<Natural>& fixingDays) {
        fixingDays_ = fixingDays;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withGearings(Real gearing) {
        gearings_ = std::vector<Real>(1,gearing);
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withGearings(
                                          const std::vector<Real>& gearings) {
        gearings_ = gearings;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withSpreads(Spread spread) {
        spreads_ = std::vector<Spread>(1,spread);
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withSpreads(
                                         const std::vector<Spread>& spreads) {
        spreads_ = spreads;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withLowerTriggers(Rate trigger) {
        lowerTriggers_ = std::vector<Rate>(1,trigger);
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withLowerTriggers(
                                          const std::vector<Rate>& triggers) {
        lowerTriggers_ = triggers;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withUpperTriggers(Rate trigger) {
        upperTriggers_ = std::vector<Rate>(1,trigger);
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withUpperTriggers(
                                          const std::vector<Rate>& triggers) {
        upperTriggers_ = triggers;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withObservationTenor(
                                                        const Period& tenor) {
        observationTenor_ = tenor;
        return *this;
    }

    CmsSpreadRangeAccrualLeg& CmsSpreadRangeAccrualLeg::withObservationConvention(
                                           BusinessDayConvention convention) {
        observationConvention_ = convention;
        return *this;
    }

    CmsSpreadRangeAccrualLeg::operator Leg() const {

        QL_REQUIRE(!notionals_.empty(), "no notional given");

        Size n = schedule_.size()-1;
        QL_REQUIRE(notionals_.size() <= n,
                   "too many nominals (" << notionals_.size() <<
                   "), only " << n << " required");
        QL_REQUIRE(fixingDays_.size() <= n,
                   "too many fixingDays (" << fixingDays_.size() <<
                   "), only " << n << " required");
        QL_REQUIRE(gearings_.size()<=n,
                   "too many gearings (" << gearings_.size() <<
                   "), only " << n << " required");
        QL_REQUIRE(spreads_.size()<=n,
                   "too many spreads (" << spreads_.size() <<
                   "), only " << n << " required");
        QL_REQUIRE(lowerTriggers_.size()<=n,
                   "too many lowerTriggers (" << lowerTriggers_.size() <<
                   "), only " << n << " required");
        QL_REQUIRE(upperTriggers_.size()<=n,
                   "too many upperTriggers (" << upperTriggers_.size() <<
                   "), only " << n << " required");

        Leg leg(n);

        // the following is not always correct
        Calendar calendar = schedule_.calendar();

        Date refStart, start, refEnd, end;
        Date paymentDate;
        std::vector<boost::shared_ptr<Schedule> > observationsSchedules;

        for (Size i=0; i<n; ++i) {
            refStart = start = schedule_.date(i);
            refEnd   =   end = schedule_.date(i+1);
            paymentDate = calendar.adjust(end, paymentAdjustment_);
            if (i==0   && !schedule_.isRegular(i+1)) {
                BusinessDayConvention bdc = schedule_.businessDayConvention();
                refStart = calendar.adjust(end - schedule_.tenor(), bdc);
            }
            if (i==n-1 && !schedule_.isRegular(i+1)) {
                BusinessDayConvention bdc = schedule_.businessDayConvention();
                refEnd = calendar.adjust(start + schedule_.tenor(), bdc);
            }
            if (detail::get(gearings_, i, 1.0) == 0.0) { // fixed coupon
                leg.push_back(boost::shared_ptr<CashFlow>(new
                    FixedRateCoupon(paymentDate,
                                    detail::get(notionals_, i, Null<Real>()),
                                    detail::get(spreads_, i, 0.0),
                                    paymentDayCounter_,
                                    start, end, refStart, refEnd)));
            } else { // floating coupon
                observationsSchedules.push_back(
                    boost::shared_ptr<Schedule>(new
                        Schedule(start, end,
                                 observationTenor_, calendar,
                                 observationConvention_,
                                 observationConvention_,
                                 DateGeneration::Forward, false)));

                    leg.push_back(boost::shared_ptr<CashFlow>(new
                       CmsSpreadRangeAccrualCoupon(
                            paymentDate,
                            detail::get(notionals_, i, Null<Real>()),
                            index_,
                            start, end,
                            detail::get(fixingDays_, i, 2),
                            paymentDayCounter_,
                            detail::get(gearings_, i, 1.0),
                            detail::get(spreads_, i, 0.0),
                            refStart, refEnd,
                            observationsSchedules.back(),
                            detail::get(lowerTriggers_, i, Null<Rate>()),
                            detail::get(upperTriggers_, i, Null<Rate>()))));
            }
        }
        return leg;
    }

}
