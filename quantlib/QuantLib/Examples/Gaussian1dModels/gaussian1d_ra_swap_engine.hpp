#pragma once

#include <ql/instruments/nonstandardswaption.hpp>
#include <ql/models/shortrate/onefactormodels/gsr.hpp>
#include <ql/pricingengines/genericmodelengine.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolstructure.hpp>

namespace QuantLib {

    class G1d_RA_Swap_Engine
        : public BasketGeneratingEngine,
          public GenericModelEngine<Gaussian1dModel,
                                    NonstandardSwaption::arguments,
                                    NonstandardSwaption::results> {
      public:
        enum Probabilities {
            None,
            Naive,
            Digital
        };

        G1d_RA_Swap_Engine(
            const boost::shared_ptr<Gaussian1dModel> &model,
            const int integrationPoints = 64, const Real stddevs = 7.0,
            const bool extrapolatePayoff = true,
            const bool flatPayoffExtrapolation = false,
            const Handle<Quote> &oas = Handle<Quote>(), // continuously
                                                        // compounded w.r.t. yts
                                                        // daycounter
            const Handle<YieldTermStructure> &discountCurve =
                Handle<YieldTermStructure>(),
            const Probabilities probabilities = None)
            : BasketGeneratingEngine(model, oas, discountCurve),
              GenericModelEngine<Gaussian1dModel,
                                 NonstandardSwaption::arguments,
                                 NonstandardSwaption::results>(model),
              integrationPoints_(integrationPoints), stddevs_(stddevs),
              extrapolatePayoff_(extrapolatePayoff),
              flatPayoffExtrapolation_(flatPayoffExtrapolation),
              discountCurve_(discountCurve), oas_(oas),
              probabilities_(probabilities) {

            if (!oas_.empty())
                registerWith(oas_);

            if (!discountCurve_.empty())
                registerWith(discountCurve_);
        }

        void calculate() const;

      protected:
        const Real underlyingNpv(const Date &expiry, const Real y) const;
        const VanillaSwap::Type underlyingType() const;
        const Date underlyingLastDate() const;
        const Disposable<Array> initialGuess(const Date &expiry) const;

      private:
        const int integrationPoints_;
        const Real stddevs_;
        const bool extrapolatePayoff_, flatPayoffExtrapolation_;
        const Handle<YieldTermStructure> discountCurve_;
        const Handle<Quote> oas_;
        const Probabilities probabilities_;
    };
}
