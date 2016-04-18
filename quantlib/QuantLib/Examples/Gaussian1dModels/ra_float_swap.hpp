#pragma once

#include <ql/instruments/floatfloatswap.hpp>
#include <ql/instruments/vanillaswap.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/time/schedule.hpp>
#include <boost/optional.hpp>

namespace QuantLib {

    class InterestRateIndex;

    //! float float swap

    class RAFloatSwap : public FloatFloatSwap {
      public:
        class arguments;
        class results;
        class engine;
        RAFloatSwap(
            const VanillaSwap::Type type, const Real nominal1,
            const Real nominal2, const Schedule &schedule1,
            const boost::shared_ptr<InterestRateIndex> &index1,
            const DayCounter &dayCount1, const Schedule &schedule2,
            const boost::shared_ptr<InterestRateIndex> &index2,
            const DayCounter &dayCount2,
            const bool intermediateCapitalExchange = false,
            const bool finalCapitalExchange = false, const Real gearing1 = 1.0,
            const Real spread1 = 0.0, const Real cappedRate1 = Null<Real>(),
            const Real flooredRate1 = Null<Real>(), const Real gearing2 = 1.0,
            const Real spread2 = 0.0, const Real cappedRate2 = Null<Real>(),
            const Real flooredRate2 = Null<Real>(),
            boost::optional<BusinessDayConvention> paymentConvention1 =
                boost::none,
            boost::optional<BusinessDayConvention> paymentConvention2 =
                boost::none);

        RAFloatSwap(
            const VanillaSwap::Type type, const std::vector<Real> &nominal1,
            const std::vector<Real> &nominal2, const Schedule &schedule1,
            const boost::shared_ptr<InterestRateIndex> &index1,
            const DayCounter &dayCount1, const Schedule &schedule2,
            const boost::shared_ptr<InterestRateIndex> &index2,
            const DayCounter &dayCount2,
            const bool intermediateCapitalExchange = false,
            const bool finalCapitalExchange = false,
            const std::vector<Real> &gearing1 = std::vector<Real>(),
            const std::vector<Real> &spread1 = std::vector<Real>(),
            const std::vector<Real> &cappedRate1 = std::vector<Real>(),
            const std::vector<Real> &flooredRate1 = std::vector<Real>(),
            const std::vector<Real> &gearing2 = std::vector<Real>(),
            const std::vector<Real> &spread2 = std::vector<Real>(),
            const std::vector<Real> &cappedRate2 = std::vector<Real>(),
            const std::vector<Real> &flooredRate2 = std::vector<Real>(),
            boost::optional<BusinessDayConvention> paymentConvention1 =
                boost::none,
            boost::optional<BusinessDayConvention> paymentConvention2 =
                boost::none);

		void setupArguments(PricingEngine::arguments *args) const;
		void fetchResults(const PricingEngine::results *r) const;

      private:
        void setupExpired() const;

    };

    //! %Arguments for float float swap calculation
    class RAFloatSwap::arguments : public FloatFloatSwap::arguments {
      public:
		  void validate() const;
    };

    //! %Results from float float swap calculation
    class RAFloatSwap::results : public FloatFloatSwap::results {
      public:
        void reset();
    };

    class RAFloatSwap::engine : public GenericEngine<RAFloatSwap::arguments, RAFloatSwap::results> {};
   
}
