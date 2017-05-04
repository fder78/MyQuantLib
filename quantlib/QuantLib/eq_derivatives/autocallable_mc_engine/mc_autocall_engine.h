#pragma once

#include <eq_derivatives\autocallable_instrument\autocallable_note.h>
#include <ql/pricingengines/mcsimulation.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/processes/stochasticprocessarray.hpp>
#include <ql/exercise.hpp>

namespace QuantLib {

	template <class GSG>
	class MultiPathGeneratorPathReuse {
	public:
		typedef Sample<MultiPath> sample_type;
		MultiPathGeneratorPathReuse(
			const std::vector<std::string> names,
			const boost::shared_ptr<StochasticProcess>& p,
			const TimeGrid&,
			GSG generator,
			bool brownianBridge = false);
		const sample_type& next() const;
		const sample_type& antithetic() const;
		void generatePaths(Size n);
		void reset() { idx_ = 0; }
		bool isFirst() { return isFirstPhase_; }

	private:
		static bool isFirstPhase_;
		static Size idx_;
		static std::vector<MultiPath> paths_;
		static std::map<std::string, Size> indexID_;
		std::vector<std::string> names_;

		const sample_type& next(bool antithetic) const;
		bool brownianBridge_;
		boost::shared_ptr<StochasticProcess> process_;
		GSG generator_;
		mutable sample_type next_;

	};

	template <class GSG>
	bool MultiPathGeneratorPathReuse<GSG>::isFirstPhase_;
	template <class GSG>
	Size MultiPathGeneratorPathReuse<GSG>::idx_;
	template <class GSG>
	std::vector<MultiPath> MultiPathGeneratorPathReuse<GSG>::paths_;
	template <class GSG>
	std::map<std::string, Size> MultiPathGeneratorPathReuse<GSG>::indexID_;

	template <class GSG>
	MultiPathGeneratorPathReuse<GSG>::MultiPathGeneratorPathReuse(
		const std::vector<std::string> names,
		const boost::shared_ptr<StochasticProcess>& process,
		const TimeGrid& times,
		GSG generator,
		bool brownianBridge)
		: brownianBridge_(brownianBridge), process_(process),
		names_(names), generator_(generator), next_(MultiPath(process->size(), times), 1.0) {

		QL_REQUIRE(generator_.dimension() == process->factors()*(times.size() - 1),
			"dimension (" << generator_.dimension() << ") is not equal to (" << process->factors() << " * " << times.size() - 1 << ") the number of factors " << "times the number of time steps");
		QL_REQUIRE(times.size() > 1, "no times given");
		QL_REQUIRE(process->size() >= names.size(), "Number of processes should not be less than the number of names");
		if (paths_.size() == 0) {
			isFirstPhase_ = true;
			for (Size i = 0; i < names_.size(); ++i)
				indexID_[names_[i]] = i;
		}
		else {
			isFirstPhase_ = false;
			for (Size i = 0; i < names.size(); ++i)
				QL_REQUIRE(indexID_.find(names[i]) != indexID_.end(), names[i] << " is not in ID list");
		}

	}

	template <class GSG>
	void MultiPathGeneratorPathReuse<GSG>::generatePaths(Size n) {
		for (Size i = 0; i < n; ++i) {
			next();
		}
		isFirstPhase_ = false;
	}

	template <class GSG>
	inline const typename MultiPathGeneratorPathReuse<GSG>::sample_type&
		MultiPathGeneratorPathReuse<GSG>::next() const {
		return next(false);
	}

	template <class GSG>
	inline const typename MultiPathGeneratorPathReuse<GSG>::sample_type&
		MultiPathGeneratorPathReuse<GSG>::antithetic() const {
		return next(true);
	}

	template <class GSG>
	const typename MultiPathGeneratorPathReuse<GSG>::sample_type&
		MultiPathGeneratorPathReuse<GSG>::next(bool antithetic) const {

		if (brownianBridge_) {

			QL_FAIL("Brownian bridge not supported");

		}
		else {
			if (isFirstPhase_) {
				typedef typename GSG::sample_type sequence_type;
				const sequence_type& sequence_ =
					antithetic ? generator_.lastSequence()
					: generator_.nextSequence();

				Size m = process_->size();
				Size n = process_->factors();

				MultiPath& path = next_.value;

				Array asset = process_->initialValues();
				for (Size j = 0; j < m; j++)
					path[j].front() = asset[j];

				Array temp(n);
				next_.weight = sequence_.weight;

				const TimeGrid& timeGrid = path[0].timeGrid();
				Time t, dt;
				for (Size i = 1; i < path.pathSize(); i++) {
					Size offset = (i - 1)*n;
					t = timeGrid[i - 1];
					dt = timeGrid.dt(i - 1);
					if (antithetic)
						std::transform(sequence_.value.begin() + offset,
							sequence_.value.begin() + offset + n,
							temp.begin(),
							std::negate<Real>());
					else
						std::copy(sequence_.value.begin() + offset,
							sequence_.value.begin() + offset + n,
							temp.begin());

					asset = process_->evolve(t, asset, dt, temp);
					for (Size j = 0; j < m; j++)
						path[j][i] = asset[j];
				}
				paths_.push_back(path);
				return next_;
			}
			else {
				std::vector<Path> path;
				for (Size i = 0; i < names_.size(); ++i)
					path.push_back(paths_[idx_][indexID_[names_[i]]]);
				MultiPath mp(path);
				next_.value = mp;
				next_.weight = 1.0;
				idx_++;
				return next_;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class RNG = PseudoRandom>
	struct MultiVariatePathReuse
	{
		typedef RNG rng_traits;
		typedef MultiPath path_type;
		typedef PathPricer<path_type> path_pricer_type;
		typedef typename RNG::rsg_type rsg_type;
		typedef MultiPathGeneratorPathReuse<rsg_type> path_generator_type;
		enum { allowsErrorEstimate = RNG::allowsErrorEstimate };
	};


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	class MCAutocallEngine : public AutocallableNote::engine, public McSimulation<MultiVariatePathReuse, RNG, S> {
	public:
		typedef typename McSimulation<MultiVariatePathReuse, RNG, S>::path_generator_type	path_generator_type;
		typedef typename McSimulation<MultiVariatePathReuse, RNG, S>::path_pricer_type		path_pricer_type;
		typedef typename McSimulation<MultiVariatePathReuse, RNG, S>::stats_type			stats_type;

		MCAutocallEngine(
			const std::vector<std::string> names,
			const boost::shared_ptr<StochasticProcessArray>& process,
			const boost::shared_ptr<YieldTermStructure>& discCurve,
			const Date maxDate,
			Size timeSteps,
			Size timeStepsPerYear,
			bool brownianBridge,
			bool antitheticVariate,
			Size requiredSamples,
			Real requiredTolerance,
			Size maxSamples,
			BigNatural seed);
		void calculate() const {

			McSimulation<MultiVariatePathReuse, RNG, S>::calculate(requiredTolerance_,
				requiredSamples_,
				maxSamples_);
			Size assetNumber_ = processes_->size();
			results_.value = this->mcModel_->sampleAccumulator().mean();
			results_.theta = std::vector<Real>(1, 0);
			results_.delta = std::vector<Real>(assetNumber_, 0);
			results_.gamma = std::vector<Real>(assetNumber_, 0);
			results_.xgamma = std::vector<std::vector<Real> >(assetNumber_, std::vector<Real>(assetNumber_, 0));
			if (RNG::allowsErrorEstimate)
				results_.errorEstimate = this->mcModel_->sampleAccumulator().errorEstimate();
		}
		void init() const {
			this->pathGenerator();
		}
	protected:
		virtual TimeGrid timeGrid() const;

		boost::shared_ptr<path_generator_type> pathGenerator() const {
			Size numAssets = processes_->size();
			TimeGrid grid = timeGrid();
			typename RNG::rsg_type gen = RNG::make_sequence_generator(numAssets*(grid.size() - 1), seed_);
			boost::shared_ptr<path_generator_type> pathGen = boost::shared_ptr<path_generator_type>(new path_generator_type(
				names_,
				processes_,
				grid,
				gen,
				brownianBridge_));
			if (pathGen->isFirst())
				pathGen->generatePaths(requiredSamples_);
			pathGen->reset();
			return pathGen;
		}

		boost::shared_ptr<path_pricer_type> pathPricer() const;

		std::vector<std::string> names_;
		Date maxDate_;
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
		Size days = maxDate_ - evalDate;
		Time residualTime = discCurve_->dayCounter().yearFraction(evalDate, maxDate_);
		return TimeGrid(residualTime, days);
		//if (arguments_.isKI) {
		//	std::vector<Time> t;
		//	for (Size i = 0; i < arguments_.autocallDates.size(); ++i) {
		//		Time temp = discCurve_->dayCounter().yearFraction(evalDate, arguments_.autocallDates[i]);
		//		if (temp > 0)
		//			t.push_back(temp);
		//	}
		//	return TimeGrid(t.begin(), t.end());
		//}
		//else {
		//	Size days = arguments_.autocallDates.back() - evalDate;
		//	Time residualTime = discCurve_->dayCounter().yearFraction(evalDate, arguments_.autocallDates.back());
		//	return TimeGrid(residualTime, days);
		//}
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
		const std::vector<std::string> names,
		const boost::shared_ptr<StochasticProcessArray>& processes,
		const boost::shared_ptr<YieldTermStructure>& discCurve,
		const Date maxDate,
		Size timeSteps,
		Size timeStepsPerYear,
		bool brownianBridge,
		bool antitheticVariate,
		Size requiredSamples,
		Real requiredTolerance,
		Size maxSamples,
		BigNatural seed)
		: McSimulation<MultiVariatePathReuse, RNG, S>(antitheticVariate, false),
		processes_(processes), timeSteps_(timeSteps), discCurve_(discCurve),
		timeStepsPerYear_(timeStepsPerYear), requiredSamples_(requiredSamples), maxSamples_(maxSamples), requiredTolerance_(requiredTolerance),
		brownianBridge_(brownianBridge), seed_(seed), names_(names), maxDate_(maxDate) {

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
		MakeMCAutocallEngine(
			const std::vector<std::string> names,
			const boost::shared_ptr<StochasticProcessArray>&,
			const boost::shared_ptr<YieldTermStructure>& discCurve,
			const Date maxDate);
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
		operator boost::shared_ptr<MCAutocallEngine<RNG, S> >() const;
	private:
		std::vector<std::string> names_;
		Date maxDate_;
		boost::shared_ptr<StochasticProcessArray> process_;
		boost::shared_ptr<YieldTermStructure> disc_;
		bool brownianBridge_, antithetic_;
		Size steps_, stepsPerYear_, samples_, maxSamples_;
		Real tolerance_;
		BigNatural seed_;
	};

	template <class RNG, class S>
	inline MakeMCAutocallEngine<RNG, S>::MakeMCAutocallEngine(
		const std::vector<std::string> names,
		const boost::shared_ptr<StochasticProcessArray>& process,
		const boost::shared_ptr<YieldTermStructure>& discCurve,
		const Date maxDate)
		: process_(process), disc_(discCurve), brownianBridge_(false), antithetic_(false),
		steps_(Null<Size>()), stepsPerYear_(Null<Size>()),
		samples_(Null<Size>()), maxSamples_(Null<Size>()),
		tolerance_(Null<Real>()), seed_(0), names_(names), maxDate_(maxDate) {}

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
		boost::shared_ptr<MCAutocallEngine<RNG, S> >() const {
		QL_REQUIRE(steps_ != Null<Size>() || stepsPerYear_ != Null<Size>(),
			"number of steps not given");
		QL_REQUIRE(steps_ == Null<Size>() || stepsPerYear_ == Null<Size>(),
			"number of steps overspecified");
		boost::shared_ptr<MCAutocallEngine<RNG, S> > engine = boost::shared_ptr<MCAutocallEngine<RNG, S> >(new
			MCAutocallEngine<RNG, S>(
				names_,
				process_,
				disc_,
				maxDate_,
				steps_,
				stepsPerYear_,
				brownianBridge_,
				antithetic_,
				samples_, tolerance_,
				maxSamples_,
				seed_));
		engine->init();
		return engine;
	}

}
