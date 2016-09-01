#pragma once

#include <ql/instruments/basketoption.hpp>
#include <ql/pricingengine.hpp>

namespace QuantLib {

	class AutocallableNote : public Instrument {
	public:
		class arguments;
		class engine;
		class results;

		AutocallableNote(const boost::shared_ptr<BasketPayoff>&, const boost::shared_ptr<Exercise>&);

		bool isExpired() const;
		std::vector<Real> delta() const;
		std::vector<Real> gamma() const;
		std::vector<Real> theta() const;
		std::vector<Real> vega() const;
		std::vector<Real> rho() const;
		std::vector<Real> dividendRho() const;
		
		void setupArguments(PricingEngine::arguments*) const;
		void fetchResults(const PricingEngine::results*) const;

	protected:
		boost::shared_ptr<BasketPayoff> payoff_;
		boost::shared_ptr<Exercise> exercise_;
		void setupExpired() const;
		// results
		mutable std::vector<Real> delta_, gamma_, theta_, vega_, rho_, dividendRho_;
	};

	class AutocallableNote::arguments : public virtual PricingEngine::arguments {
	public:
		arguments() {}
		void validate() const {}
		boost::shared_ptr<BasketPayoff> payoff;
		boost::shared_ptr<Exercise> exercise;
	};

	class AutocallableNote::results : public virtual Instrument::results {
	public:
		void reset() {
			Instrument::results::reset();
			delta = gamma = theta = vega = rho = dividendRho = std::vector<Real>();
		}
		std::vector<Real> delta, gamma, theta, vega, rho, dividendRho;
	};

	class AutocallableNote::engine
		: public GenericEngine<AutocallableNote::arguments, AutocallableNote::results> {};
}
