#pragma once

#include <eq_derivatives\autocallable_instrument\autocallable_note.h>
#include <ql/pricingengines/mcsimulation.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/processes/stochasticprocessarray.hpp>
#include <ql/exercise.hpp>

namespace QuantLib {

	class AutocallPricer : public PathPricer<MultiPath> {
	public:
		AutocallPricer(AutocallableNote::arguments& arguments,
			const boost::shared_ptr<YieldTermStructure>& discCurve);
		Real operator()(const MultiPath& multiPath) const;
	private:
		AutocallableNote::arguments arguments_;
		boost::shared_ptr<YieldTermStructure> discCurve_;
		Size nextCallIdx_;
		std::vector<Size> callIdx_;
	};







	template <class RNG = PseudoRandom, class S = Statistics>
	class MCAutocallEngine : public AutocallableNote::engine, public McSimulation<MultiVariate, RNG, S> {
	public:
		typedef typename McSimulation<MultiVariate, RNG, S>::path_generator_type	path_generator_type;
		typedef typename McSimulation<MultiVariate, RNG, S>::path_pricer_type		path_pricer_type;
		typedef typename McSimulation<MultiVariate, RNG, S>::stats_type			stats_type;

		MCAutocallEngine(const boost::shared_ptr<StochasticProcessArray>&,
			const boost::shared_ptr<YieldTermStructure>& discCurve,
			Size timeSteps,
			Size timeStepsPerYear,
			bool brownianBridge,
			bool antitheticVariate,
			Size requiredSamples,
			Real requiredTolerance,
			Size maxSamples,
			BigNatural seed);
		void calculate() const {

			McSimulation<MultiVariate, RNG, S>::calculate(requiredTolerance_,
				requiredSamples_,
				maxSamples_);
			results_.value = this->mcModel_->sampleAccumulator().mean();
			if (RNG::allowsErrorEstimate)
				results_.errorEstimate = this->mcModel_->sampleAccumulator().errorEstimate();
		}
	protected:
		virtual TimeGrid timeGrid() const;

		boost::shared_ptr<path_generator_type> pathGenerator() const {
			Size numAssets = processes_->size();
			TimeGrid grid = timeGrid();
			typename RNG::rsg_type gen = RNG::make_sequence_generator(numAssets*(grid.size() - 1), seed_);
			return boost::shared_ptr<path_generator_type>(new path_generator_type(processes_, grid, gen, brownianBridge_));
		}

		boost::shared_ptr<path_pricer_type> pathPricer() const;

		boost::shared_ptr<StochasticProcessArray> processes_;
		boost::shared_ptr<YieldTermStructure> discCurve_;
		Size timeSteps_, timeStepsPerYear_;
		Size requiredSamples_;
		Size maxSamples_;
		Real requiredTolerance_;
		bool brownianBridge_;
		BigNatural seed_;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	//TIMEGRID
	template <class RNG, class S>
	inline TimeGrid MCAutocallEngine<RNG, S>::timeGrid() const {
		Date evalDate = Settings::instance().evaluationDate();
		if (arguments_.isKI) {
			std::vector<Time> t;
			for (Size i = 0; i < arguments_.autocallDates.size(); ++i) {
				Time temp = discCurve_->dayCounter().yearFraction(evalDate, arguments_.autocallDates[i]);
				if (temp > 0)
					t.push_back(temp);
			}
			return TimeGrid(t.begin(), t.end());
		}
		else {
			Size days = arguments_.autocallDates.back() - evalDate;
			Time residualTime = discCurve_->dayCounter().yearFraction(evalDate, arguments_.autocallDates.back());
			return TimeGrid(residualTime, days);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//pathPricer
	template <class RNG, class S>
	inline
		boost::shared_ptr<typename MCAutocallEngine<RNG, S>::path_pricer_type>
		MCAutocallEngine<RNG, S>::pathPricer() const {
		return boost::shared_ptr<typename MCAutocallEngine<RNG, S>::path_pricer_type>(
			new AutocallPricer(arguments_, discCurve_));
	}




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class RNG, class S>
	inline MCAutocallEngine<RNG, S>::MCAutocallEngine(
		const boost::shared_ptr<StochasticProcessArray>& processes,
		const boost::shared_ptr<YieldTermStructure>& discCurve,
		Size timeSteps,
		Size timeStepsPerYear,
		bool brownianBridge,
		bool antitheticVariate,
		Size requiredSamples,
		Real requiredTolerance,
		Size maxSamples,
		BigNatural seed)
		: McSimulation<MultiVariate, RNG, S>(antitheticVariate, false),
		processes_(processes), timeSteps_(timeSteps), discCurve_(discCurve),
		timeStepsPerYear_(timeStepsPerYear), requiredSamples_(requiredSamples), maxSamples_(maxSamples), requiredTolerance_(requiredTolerance),
		brownianBridge_(brownianBridge), seed_(seed) {

		QL_REQUIRE(timeSteps != Null<Size>() || timeStepsPerYear != Null<Size>(), "no time steps provided");
		QL_REQUIRE(timeSteps == Null<Size>() || timeStepsPerYear == Null<Size>(), "both time steps and time steps per year were provided");
		QL_REQUIRE(timeSteps != 0, "timeSteps must be positive, " << timeSteps << " not allowed");
		QL_REQUIRE(timeStepsPerYear != 0, "timeStepsPerYear must be positive, " << timeStepsPerYear << " not allowed");

		registerWith(processes_);
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class RNG = PseudoRandom, class S = Statistics>
	class MakeMCAutocallEngine {
	public:
		MakeMCAutocallEngine(const boost::shared_ptr<StochasticProcessArray>&, const boost::shared_ptr<YieldTermStructure>& discCurve);
		// named parameters
		MakeMCAutocallEngine& withSteps(Size steps);
		MakeMCAutocallEngine& withStepsPerYear(Size steps);
		MakeMCAutocallEngine& withBrownianBridge(bool b = true);
		MakeMCAutocallEngine& withAntitheticVariate(bool b = true);
		MakeMCAutocallEngine& withSamples(Size samples);
		MakeMCAutocallEngine& withAbsoluteTolerance(Real tolerance);
		MakeMCAutocallEngine& withMaxSamples(Size samples);
		MakeMCAutocallEngine& withSeed(BigNatural seed);
		// conversion to pricing engine
		operator boost::shared_ptr<PricingEngine>() const;
	private:
		boost::shared_ptr<StochasticProcessArray> process_;
		boost::shared_ptr<YieldTermStructure> disc_;
		bool brownianBridge_, antithetic_;
		Size steps_, stepsPerYear_, samples_, maxSamples_;
		Real tolerance_;
		BigNatural seed_;
	};

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>::MakeMCAutocallEngine(
		const boost::shared_ptr<StochasticProcessArray>& process,
		const boost::shared_ptr<YieldTermStructure>& discCurve)
		: process_(process), disc_(discCurve), brownianBridge_(false), antithetic_(false),
		steps_(Null<Size>()), stepsPerYear_(Null<Size>()),
		samples_(Null<Size>()), maxSamples_(Null<Size>()),
		tolerance_(Null<Real>()), seed_(0) {}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withSteps(Size steps) {
		steps_ = steps;
		return *this;
	}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withStepsPerYear(Size steps) {
		stepsPerYear_ = steps;
		return *this;
	}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withBrownianBridge(bool brownianBridge) {
		brownianBridge_ = brownianBridge;
		return *this;
	}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withAntitheticVariate(bool b) {
		antithetic_ = b;
		return *this;
	}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withSamples(Size samples) {
		QL_REQUIRE(tolerance_ == Null<Real>(),
			"tolerance already set");
		samples_ = samples;
		return *this;
	}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withAbsoluteTolerance(Real tolerance) {
		QL_REQUIRE(samples_ == Null<Size>(),
			"number of samples already set");
		QL_REQUIRE(RNG::allowsErrorEstimate,
			"chosen random generator policy "
			"does not allow an error estimate");
		tolerance_ = tolerance;
		return *this;
	}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withMaxSamples(Size samples) {
		maxSamples_ = samples;
		return *this;
	}

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>&
		MakeMCAutocallEngine<RNG, S>::withSeed(BigNatural seed) {
		seed_ = seed;
		return *this;
	}

	template <class RNG, class S>
	inline
		MakeMCAutocallEngine<RNG, S>::operator
		boost::shared_ptr<PricingEngine>() const {
			QL_REQUIRE(steps_ != Null<Size>() || stepsPerYear_ != Null<Size>(),
				"number of steps not given");
			QL_REQUIRE(steps_ == Null<Size>() || stepsPerYear_ == Null<Size>(),
				"number of steps overspecified");
			return boost::shared_ptr<PricingEngine>(new
				MCAutocallEngine<RNG, S>(process_,
					disc_,
					steps_,
					stepsPerYear_,
					brownianBridge_,
					antithetic_,
					samples_, tolerance_,
					maxSamples_,
					seed_));
	}

}
