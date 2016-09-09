#pragma once
#include <eq_derivatives\autocallable_instrument\basket_payoff.h>

namespace QuantLib {
	Real TestPayoff::operator()(Array a) {
		QL_REQUIRE(a.size() == params_.size(), "Number of asset mismatch");
		return 0;
	}
}