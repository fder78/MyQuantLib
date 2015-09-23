#pragma once

#include <ql/experimental/coupons/swapspreadindex.hpp>

#include <ql/termstructures/volatility/smilesection.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/cashflows/floatingratecoupon.hpp>
#include <ql/time/schedule.hpp>
#include <vector>

namespace QuantLib {

    class CmsSpreadRangeAccrualCoupon: public FloatingRateCoupon {

      public:

          CmsSpreadRangeAccrualCoupon(
                const Date& paymentDate,
                Real nominal,
				const boost::shared_ptr<SwapSpreadIndex>& index,
                const Date& startDate,
                const Date& endDate,
                Natural fixingDays,
                const DayCounter& dayCounter,
                Real gearing,
                Rate spread,
                const Date& refPeriodStart,
                const Date& refPeriodEnd,
                const boost::shared_ptr<Schedule>&  observationsSchedule,
                Real lowerTrigger,
                Real upperTrigger);

        Real startTime() const {return startTime_; }
        Real endTime() const {return endTime_; }
        Real lowerTrigger() const {return lowerTrigger_; }
        Real upperTrigger() const {return upperTrigger_; }
        Size observationsNo() const {return observationsNo_; }
        const std::vector<Date>& observationDates() const {
            return observationDates_;
        }
        const std::vector<Real>& observationTimes() const {
            return observationTimes_;
        }
        const boost::shared_ptr<Schedule> observationsSchedule() const {
            return observationsSchedule_;
        }

        Real priceWithoutOptionality(
                       const Handle<YieldTermStructure>& discountCurve) const;
        //! \name Visitability
        //@{
        virtual void accept(AcyclicVisitor&);
        //@}
      private:

        Real startTime_;                               // S
        Real endTime_;                                 // T

        const boost::shared_ptr<Schedule> observationsSchedule_;
        std::vector<Date> observationDates_;
        std::vector<Real> observationTimes_;
        Size observationsNo_;

        Real lowerTrigger_;
        Real upperTrigger_;
     };


    class CmsSpreadRangeAccrualLeg {
      public:
        CmsSpreadRangeAccrualLeg(const Schedule& schedule,
			const boost::shared_ptr<SwapSpreadIndex>& index);
        CmsSpreadRangeAccrualLeg& withNotionals(Real notional);
        CmsSpreadRangeAccrualLeg& withNotionals(const std::vector<Real>& notionals);
        CmsSpreadRangeAccrualLeg& withPaymentDayCounter(const DayCounter&);
        CmsSpreadRangeAccrualLeg& withPaymentAdjustment(BusinessDayConvention);
        CmsSpreadRangeAccrualLeg& withFixingDays(Natural fixingDays);
        CmsSpreadRangeAccrualLeg& withFixingDays(const std::vector<Natural>& fixingDays);
        CmsSpreadRangeAccrualLeg& withGearings(Real gearing);
        CmsSpreadRangeAccrualLeg& withGearings(const std::vector<Real>& gearings);
        CmsSpreadRangeAccrualLeg& withSpreads(Spread spread);
        CmsSpreadRangeAccrualLeg& withSpreads(const std::vector<Spread>& spreads);
        CmsSpreadRangeAccrualLeg& withLowerTriggers(Rate trigger);
        CmsSpreadRangeAccrualLeg& withLowerTriggers(const std::vector<Rate>& triggers);
        CmsSpreadRangeAccrualLeg& withUpperTriggers(Rate trigger);
        CmsSpreadRangeAccrualLeg& withUpperTriggers(const std::vector<Rate>& triggers);
        CmsSpreadRangeAccrualLeg& withObservationTenor(const Period&);
        CmsSpreadRangeAccrualLeg& withObservationConvention(BusinessDayConvention);
        operator Leg() const;
      private:
        Schedule schedule_;
		boost::shared_ptr<SwapSpreadIndex> index_;
        std::vector<Real> notionals_;
        DayCounter paymentDayCounter_;
        BusinessDayConvention paymentAdjustment_;
        std::vector<Natural> fixingDays_;
        std::vector<Real> gearings_;
        std::vector<Spread> spreads_;
        std::vector<Rate> lowerTriggers_, upperTriggers_;
        Period observationTenor_;
        BusinessDayConvention observationConvention_;
    };

}

