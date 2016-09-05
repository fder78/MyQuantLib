
#include <ql/payoff.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <eq_derivatives\autocallable_engine\autocall_calculator.h>

namespace QuantLib {

	FdmAutocallInnerValue::FdmAutocallInnerValue(
		const boost::shared_ptr<BasketPayoff>& payoff,
		const boost::shared_ptr<FdmMesher>& mesher)
		: payoff_(payoff), mesher_(mesher) { }

	Real FdmAutocallInnerValue::innerValue(
		const FdmLinearOpIterator& iter, Time) {
		Array x(mesher_->layout()->dim().size());
		for (Size i = 0; i < x.size(); ++i) {
			x[i] = std::exp(mesher_->location(iter, i));
		}
		return payoff_->operator()(x);
	}

	Real
		FdmAutocallInnerValue::avgInnerValue(const FdmLinearOpIterator& iter, Time t) {
		return innerValue(iter, t);
	}
}