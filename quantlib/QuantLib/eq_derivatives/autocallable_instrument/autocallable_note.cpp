
#include <eq_derivatives\autocallable_instrument\autocallable_note.h>
#include <ql/event.hpp>
#include <ql/exercise.hpp>
#include <ql/settings.hpp>

namespace QuantLib {

	AutocallableNote::AutocallableNote(const Real notionalAmt,
		const Schedule&autocallDates,
		const Schedule& paymentDates,
		const std::vector<boost::shared_ptr<AutocallCondition> >& autocallConditions,
		const std::vector<boost::shared_ptr<BasketPayoff> >& autocallPayoffs,
		const boost::shared_ptr<BasketPayoff> terminalPayoff) 
		: notionalAmt_(notionalAmt),
		autocallConditions_(autocallConditions), autocallPayoffs_(autocallPayoffs), terminalPayoff_(terminalPayoff), 
		isKI_(false), kibarrier_(boost::shared_ptr<AutocallCondition>(new NullAutocallCondition())) {

		for (Size i = 1; i < autocallDates.size(); ++i) {
			autocallDates_.push_back(autocallDates[i]);
			paymentDates_.push_back(paymentDates[i]);
		}
	}

	bool AutocallableNote::isExpired() const {
		return detail::simple_event(autocallDates_.back()).hasOccurred(Date(), true);
	}

	std::vector<Real> AutocallableNote::delta() const {
		calculate();
		QL_REQUIRE(delta_.size()>0, "delta not provided");
		return delta_;
	}

	std::vector<Real> AutocallableNote::gamma() const {
		calculate();
		QL_REQUIRE(gamma_.size()>0, "gamma not provided");
		return gamma_;
	}

	std::vector<std::vector<Real> > AutocallableNote::xgamma() const {
		calculate();
		QL_REQUIRE(gamma_.size()>0, "gamma not provided");
		return xgamma_;
	}

	std::vector<Real> AutocallableNote::theta() const {
		calculate();
		QL_REQUIRE(theta_.size()>0, "theta not provided");
		return theta_;
	}

	std::vector<Real> AutocallableNote::vega() const {
		calculate();
		QL_REQUIRE(vega_.size()>0, "vega not provided");
		return vega_;
	}

	std::vector<Real> AutocallableNote::rho() const {
		calculate();
		QL_REQUIRE(rho_.size()>0, "rho not provided");
		return rho_;
	}

	std::vector<Real> AutocallableNote::dividendRho() const {
		calculate();
		QL_REQUIRE(dividendRho_.size()>0, "dividend rho not provided");
		return dividendRho_;
	}

	void AutocallableNote::setupExpired() const {
		NPV_ = 0.0;
		delta_ = gamma_ = theta_ = vega_ = rho_ = dividendRho_ = std::vector<Real>();
		xgamma_ = std::vector<std::vector<Real> >();
	}


	inline void AutocallableNote::setupArguments(PricingEngine::arguments* args) const {
		AutocallableNote::arguments* arguments = dynamic_cast<AutocallableNote::arguments*>(args);
		QL_REQUIRE(arguments != 0, "wrong argument type");
		arguments->notionalAmt = notionalAmt_;
		arguments->autocallDates = autocallDates_;
		arguments->paymentDates = paymentDates_;
		arguments->autocallConditions = autocallConditions_;
		arguments->autocallPayoffs = autocallPayoffs_;
		arguments->terminalPayoff = terminalPayoff_;
		arguments->isKI = isKI_;
		arguments->kibarrier = kibarrier_;
		arguments->KIPayoff = KIPayoff_;
	}

	void AutocallableNote::fetchResults(const PricingEngine::results* r) const {
		Instrument::fetchResults(r);
		const AutocallableNote::results* results = dynamic_cast<const AutocallableNote::results*>(r);
		QL_ENSURE(results != 0, "no greeks returned from pricing engine");
		delta_ = results->delta;
		gamma_ = results->gamma;
		xgamma_ = results->xgamma;
		theta_ = results->theta;
		vega_ = results->vega;
		rho_ = results->rho;
		dividendRho_ = results->dividendRho;
		
	}
}