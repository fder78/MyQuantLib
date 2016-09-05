#include <eq_derivatives\autocallable_engine\autocall_condition.h>

namespace QuantLib {

	bool MinUpCondition::operator()(Array& a) {
		Real min = *std::min_element(a.begin(), a.end());
		return std::exp(min) >= barrier_;
	}

	bool MinDownCondition::operator()(Array& a) {
		Real min = *std::min_element(a.begin(), a.end());
		return std::exp(min) <= barrier_;
	}

}