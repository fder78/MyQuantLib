#pragma once

#include <ql/qldefines.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/processes/stochasticprocessarray.hpp>
#include <ql/methods/montecarlo/lsmbasissystem.hpp>
#include <ql/pricingengines/mclongstaffschwartzengine.hpp>
#include <ql/exercise.hpp>
#include <boost/function.hpp>

#include "callable_index_rangeaccrual.hpp"


namespace QuantLib {

	////////////////////////////////////////////////////////////////////////////////////
	// ENGINE
	////////////////////////////////////////////////////////////////////////////////////

	template <class RNG = PseudoRandom>
	class MCCallableIndexRAEngine
		: public MCLongstaffSchwartzEngine<CallableIndexRangeAccrual::engine, MultiVariate, RNG> {
	public:
		MCCallableIndexRAEngine(const boost::shared_ptr<StochasticProcessArray>&,
			const boost::shared_ptr<YieldTermStructure>& discTS,
			Size timeSteps,
			Size timeStepsPerYear,
			bool brownianBridge,
			bool antitheticVariate,
			Size requiredSamples,
			Real requiredTolerance,
			Size maxSamples,
			BigNatural seed,
			Size nCalibrationSamples = Null<Size>());
		void calculate() const;
	protected:
		boost::shared_ptr<YieldTermStructure> discTS_;
		boost::shared_ptr<LongstaffSchwartzPathPricer<MultiPath> > lsmPathPricer() const;
		TimeGrid timeGrid() const;
		TimeGrid exerciseTimeGrid() const;
		std::vector<Size> exerciseIndex() const;
	};

	template <class RNG> inline
		MCCallableIndexRAEngine<RNG>::MCCallableIndexRAEngine(
			const boost::shared_ptr<StochasticProcessArray>& processes,
			const boost::shared_ptr<YieldTermStructure>& discTS,
			Size timeSteps,
			Size timeStepsPerYear,
			bool brownianBridge,
			bool antitheticVariate,
			Size requiredSamples,
			Real requiredTolerance,
			Size maxSamples,
			BigNatural seed,
			Size nCalibrationSamples)
		: discTS_(discTS), MCLongstaffSchwartzEngine<CallableIndexRangeAccrual::engine, MultiVariate, RNG>(
			processes,
			timeSteps,
			timeStepsPerYear,
			brownianBridge,
			antitheticVariate,
			false,
			requiredSamples,
			requiredTolerance,
			maxSamples,
			seed,
			nCalibrationSamples) {}

	template <class RNG>
	inline void MCCallableIndexRAEngine<RNG>::calculate() const {
		MCLongstaffSchwartzEngine::calculate();
		this->results_.value *= (-1.0);
	}


	template <class RNG>
	inline boost::shared_ptr<LongstaffSchwartzPathPricer<MultiPath> >
		MCCallableIndexRAEngine<RNG>::lsmPathPricer() const {

		boost::shared_ptr<StochasticProcessArray> processArray = boost::dynamic_pointer_cast<StochasticProcessArray>(this->process_);
		QL_REQUIRE(processArray && processArray->size() > 0, "Stochastic process array required");

		boost::shared_ptr<GeneralizedBlackScholesProcess> process =	boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(processArray->process(0));
		QL_REQUIRE(process, "generalized Black-Scholes process required");

		boost::shared_ptr<EarlyExercise> exercise = boost::dynamic_pointer_cast<EarlyExercise>(this->arguments_.exercise);
		QL_REQUIRE(exercise, "wrong exercise given");
		QL_REQUIRE(!exercise->payoffAtExpiry(), "payoff at expiry not handled");

		std::vector<DiscountFactor> df;
		for (Size i = 0; i < this->arguments_.paymentDates.size()-1; ++i) {
			Time t1 = discTS_->timeFromReference(this->arguments_.paymentDates[i + 1]);
			Time t0 = discTS_->timeFromReference(this->arguments_.paymentDates[i]);
			if (t1 > 0) {
				if (t0 <= 0)
					df.push_back(discTS_->discount(t1));
				else
					df.push_back(discTS_->discount(t1) / discTS_->discount(t0));
			}
		}

		boost::shared_ptr<CallableIndexRAPathPricer> earlyExercisePathPricer(
			new CallableIndexRAPathPricer(processArray->size(),
				this->arguments_.payoff,
				this->arguments_.notional,
				this->arguments_.basePrices,
				this->arguments_.rabounds,
				this->arguments_.couponDates,
				this->arguments_.paymentDates,
				this->arguments_.inRangeCount,
				this->timeStepsPerYear_,
				this->exerciseIndex(),
				df));

		return boost::shared_ptr<LongstaffSchwartzPathPricer<MultiPath> >(
			new LongstaffSchwartzPathPricer<MultiPath>(
				this->exerciseTimeGrid(),
				earlyExercisePathPricer, 
				discTS_
				));
	}

	template <class RNG>
	inline TimeGrid MCCallableIndexRAEngine<RNG>::exerciseTimeGrid() const {
		std::vector<Time> requiredTimes;
		for (Size i = 0; i < this->arguments_.couponDates.size(); ++i) {
			Time t = discTS_->timeFromReference(this->arguments_.couponDates[i]);
			if (t > 0.0)
				requiredTimes.push_back(t);
		}
		return TimeGrid(requiredTimes.begin(), requiredTimes.end());
	}

	template <class RNG>
	inline TimeGrid MCCallableIndexRAEngine<RNG>::timeGrid() const {
		TimeGrid tg = this->exerciseTimeGrid();
		if (this->timeSteps_ != Null<Size>()) {
			return TimeGrid(tg.begin(), tg.end(), this->timeSteps_);
		}
		else if (this->timeStepsPerYear_ != Null<Size>()) {
			Size steps = static_cast<Size>(this->timeStepsPerYear_ * tg.back());
			return TimeGrid(tg.begin(), tg.end(), std::max<Size>(steps, 1));
		}
		else {
			QL_FAIL("time steps not specified");
		}
	}

	template <class RNG>
	inline std::vector<Size> MCCallableIndexRAEngine<RNG>::exerciseIndex() const {
		std::vector<Size> exerciseIndex(1, 0);
		TimeGrid tg = timeGrid();
		Size m = 0;
		Time t = discTS_->timeFromReference(this->arguments_.couponDates[m]);
		while (t <= 0.0)
			t = discTS_->timeFromReference(this->arguments_.couponDates[++m]);

		for (Size i = 0; i < tg.size(); ++i) {
			if (t == tg[i]) {
				exerciseIndex.push_back(i);
				if (t < tg.back())
					t = discTS_->timeFromReference(this->arguments_.couponDates[++m]);
			}
		}
		return exerciseIndex;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// PATH PRICER
	////////////////////////////////////////////////////////////////////////////////////

	class CallableIndexRAPathPricer
		: public EarlyExercisePathPricer<MultiPath> {
	public:
		CallableIndexRAPathPricer(Size assetNumber,
			const boost::shared_ptr<Payoff>& payoff,
			const Real& notional,
			const std::vector<Real>& basePrices,
			const std::vector<std::pair<Real, Real> >& rabounds,
			const Schedule& couponDates,
			const Schedule& paymentDates,
			const Size& inRangeCount,
			const Size& timeStepPerYear,
			const std::vector<Size>& exerciseIndex,
			const std::vector<DiscountFactor>& df,
			Size polynomOrder = 2,
			LsmBasisSystem::PolynomType
			polynomType = LsmBasisSystem::Monomial);

		Array state(const MultiPath& path, Size t) const;

		//EXERCISE VALUE
		Real operator()(const MultiPath& path, Size t) const;

		std::vector<boost::function1<Real, Array> > basisSystem() const;

	protected:
		std::vector<Size> exerciseIndex_;
		Real notional_;
		std::vector<Real> basePrices_, df_;
		std::vector<std::pair<Real, Real> > rabounds_;
		std::vector<std::pair<Real, Real> > boundValues_;
		Schedule couponDates_;
		Schedule paymentDates_;
		const Size assetNumber_, inRangeCount_, timeStepPerYear_;
		const boost::shared_ptr<Payoff> payoff_;
		std::vector<boost::function1<Real, Array> > v_;

		bool isInRange(Array&) const;
	};



	////////////////////////////////////////////////////////////////////////////////////
	// MAKE CLASS
	////////////////////////////////////////////////////////////////////////////////////

	//! Monte Carlo American basket-option engine factory
	template <class RNG = PseudoRandom>
	class MakeMCCallableIndexRAEngine {
	public:
		MakeMCCallableIndexRAEngine(
			const boost::shared_ptr<StochasticProcessArray>&,
			const boost::shared_ptr<YieldTermStructure>& discTS
			);
		// named parameters
		MakeMCCallableIndexRAEngine& withSteps(Size steps);
		MakeMCCallableIndexRAEngine& withStepsPerYear(Size steps);
		MakeMCCallableIndexRAEngine& withBrownianBridge(bool b = true);
		MakeMCCallableIndexRAEngine& withAntitheticVariate(bool b = true);
		MakeMCCallableIndexRAEngine& withSamples(Size samples);
		MakeMCCallableIndexRAEngine& withAbsoluteTolerance(Real tolerance);
		MakeMCCallableIndexRAEngine& withMaxSamples(Size samples);
		MakeMCCallableIndexRAEngine& withSeed(BigNatural seed);
		MakeMCCallableIndexRAEngine& withCalibrationSamples(Size samples);
		// conversion to pricing engine
		operator boost::shared_ptr<PricingEngine>() const;
	private:
		boost::shared_ptr<StochasticProcessArray> process_;
		boost::shared_ptr<YieldTermStructure> discTS_;
		bool brownianBridge_, antithetic_;
		Size steps_, stepsPerYear_, samples_, maxSamples_, calibrationSamples_;
		Real tolerance_;
		BigNatural seed_;
	};

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>::MakeMCCallableIndexRAEngine(
		const boost::shared_ptr<StochasticProcessArray>& process,
		const boost::shared_ptr<YieldTermStructure>& discTS)
		: discTS_(discTS), process_(process), brownianBridge_(false), antithetic_(false),
		steps_(Null<Size>()), stepsPerYear_(Null<Size>()),
		samples_(Null<Size>()), maxSamples_(Null<Size>()),
		calibrationSamples_(Null<Size>()),
		tolerance_(Null<Real>()), seed_(0) {}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withSteps(Size steps) {
		steps_ = steps;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withStepsPerYear(Size steps) {
		stepsPerYear_ = steps;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withBrownianBridge(bool brownianBridge) {
		brownianBridge_ = brownianBridge;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withAntitheticVariate(bool b) {
		antithetic_ = b;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withSamples(Size samples) {
		QL_REQUIRE(tolerance_ == Null<Real>(),
			"tolerance already set");
		samples_ = samples;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withAbsoluteTolerance(Real tolerance) {
		QL_REQUIRE(samples_ == Null<Size>(),
			"number of samples already set");
		QL_REQUIRE(RNG::allowsErrorEstimate,
			"chosen random generator policy "
			"does not allow an error estimate");
		tolerance_ = tolerance;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withMaxSamples(Size samples) {
		maxSamples_ = samples;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withSeed(BigNatural seed) {
		seed_ = seed;
		return *this;
	}

	template <class RNG>
	inline MakeMCCallableIndexRAEngine<RNG>&
		MakeMCCallableIndexRAEngine<RNG>::withCalibrationSamples(Size samples) {
		calibrationSamples_ = samples;
		return *this;
	}

	template <class RNG>
	inline
		MakeMCCallableIndexRAEngine<RNG>::operator
		boost::shared_ptr<PricingEngine>() const {
		QL_REQUIRE(steps_ != Null<Size>() || stepsPerYear_ != Null<Size>(),
			"number of steps not given");
		QL_REQUIRE(steps_ == Null<Size>() || stepsPerYear_ == Null<Size>(),
			"number of steps overspecified");
		return boost::shared_ptr<PricingEngine>(new
			MCCallableIndexRAEngine<RNG>(process_,
				discTS_,
				steps_,
				stepsPerYear_,
				brownianBridge_,
				antithetic_,
				samples_,
				tolerance_,
				maxSamples_,
				seed_,
				calibrationSamples_));
	}

}
