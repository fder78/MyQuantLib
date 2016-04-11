#pragma once

#include <ql/instruments/floatfloatswaption.hpp>
#include <ql/models/shortrate/onefactormodels/gaussian1dmodel.hpp>
#include <ql/rebatedexercise.hpp>

#include <ql/pricingengines/genericmodelengine.hpp>

namespace QuantLib {

	class G1d_FFSwap_Engine
		: public BasketGeneratingEngine,
		public GenericModelEngine<Gaussian1dModel,
		FloatFloatSwaption::arguments,
		FloatFloatSwaption::results> {
	public:
		enum Probabilities {
			None,
			Naive,
			Digital
		};

		G1d_FFSwap_Engine(
			const boost::shared_ptr<Gaussian1dModel> &model,
			const int integrationPoints = 64, const Real stddevs = 7.0,
			const bool extrapolatePayoff = true,
			const bool flatPayoffExtrapolation = false,
			const Handle<Quote> &oas =
			Handle<Quote>(), // continously compounded w.r.t. yts daycounter
			const Handle<YieldTermStructure> &discountCurve =
			Handle<YieldTermStructure>(),
			const bool includeTodaysExercise = false,
			const Probabilities probabilities = None)
			: BasketGeneratingEngine(model, oas, discountCurve),
			GenericModelEngine<Gaussian1dModel, FloatFloatSwaption::arguments,
			FloatFloatSwaption::results>(model),
			integrationPoints_(integrationPoints), stddevs_(stddevs),
			extrapolatePayoff_(extrapolatePayoff),
			flatPayoffExtrapolation_(flatPayoffExtrapolation), model_(model),
			oas_(oas), discountCurve_(discountCurve),
			includeTodaysExercise_(includeTodaysExercise),
			probabilities_(probabilities) {

			if (!discountCurve_.empty())
				registerWith(discountCurve_);

			if (!oas_.empty())
				registerWith(oas_);
		}

		void calculate() const;

		Handle<YieldTermStructure> discountingCurve() const {
			return discountCurve_.empty() ? model_->termStructure()
				: discountCurve_;
		}

	protected:
		const Real underlyingNpv(const Date &expiry, const Real y) const;
		const VanillaSwap::Type underlyingType() const;
		const Date underlyingLastDate() const;
		const Disposable<Array> initialGuess(const Date &expiry) const;

	private:
		const int integrationPoints_;
		const Real stddevs_;
		const bool extrapolatePayoff_, flatPayoffExtrapolation_;
		const boost::shared_ptr<Gaussian1dModel> model_;
		const Handle<Quote> oas_;
		const Handle<YieldTermStructure> discountCurve_;
		const bool includeTodaysExercise_;
		const Probabilities probabilities_;

		const std::pair<Real, Real>
			npvs(const Date &expiry, const Real y,
				const bool includeExerciseOnxpiry,
				const bool considerProbabilities = false) const;

		mutable boost::shared_ptr<RebatedExercise> rebatedExercise_;
	};
}