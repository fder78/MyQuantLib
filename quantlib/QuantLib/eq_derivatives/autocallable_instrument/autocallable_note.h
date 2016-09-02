#pragma once

#include <ql/instruments/basketoption.hpp>
#include <eq_derivatives\autocallable_engine\autocall_condition.h>
#include <ql/pricingengine.hpp>

namespace QuantLib {

	class AutocallableNote : public Instrument {
	public:
		class arguments;
		class engine;
		class results;

		AutocallableNote(
			const Real notionalAmt,
			const std::vector<Date>& autocallDates,
			const std::vector<Date>& paymentDates,
			const std::vector<boost::shared_ptr<AutocallCondition> >& autocallConditions,
			const std::vector<boost::shared_ptr<BasketPayoff> >& autocallPayoffs,
			const boost::shared_ptr<BasketPayoff> terminalPayoff);

		void withKI(const Real kibarrier, boost::shared_ptr<BasketPayoff> KIPayoff) {
			kibarrier_ = kibarrier;
			KIPayoff_ = KIPayoff;
			isKI_ = true;
		}

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
		const Real notionalAmt_;
		const std::vector<Date>& autocallDates_;
		const std::vector<Date>& paymentDates_;
		const std::vector<boost::shared_ptr<AutocallCondition> >& autocallConditions_;
		const std::vector<boost::shared_ptr<BasketPayoff> >& autocallPayoffs_;
		const boost::shared_ptr<BasketPayoff> terminalPayoff_;
		boost::shared_ptr<BasketPayoff> KIPayoff_;
		void setupExpired() const;
		bool isKI_;
		Real kibarrier_;


		// results
		mutable std::vector<Real> delta_, gamma_, theta_, vega_, rho_, dividendRho_;
	};

	class AutocallableNote::arguments : public virtual PricingEngine::arguments {
	public:
		arguments() {}
		void validate() const {}
		Real notionalAmt;
		std::vector<Date> autocallDates;
		std::vector<Date> paymentDates;
		std::vector<boost::shared_ptr<AutocallCondition> > autocallConditions;
		std::vector<boost::shared_ptr<BasketPayoff> > autocallPayoffs;
		boost::shared_ptr<BasketPayoff> terminalPayoff;
		bool isKI;
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
