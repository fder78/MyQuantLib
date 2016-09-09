#include <eq_derivatives\autocallable_engine\autocall_condition.h>

namespace QuantLib {

	bool MinUpCondition::operator()(Array& a) {
		if (barrierNum_ == 1) {
			Real min = *std::min_element(a.begin(), a.end());
			return std::exp(min) >= barrier_[0];
		}
		else {
			std::vector<Real> r(barrierNum_);
			std::transform(a.begin(), a.end(), barrier_.begin(), r.begin(), std::divides<Real>());
			Real min = *std::min_element(a.begin(), a.end());
			return std::exp(min) >= 1.0;
		}
	}

	bool MinDownCondition::operator()(Array& a) {
		if (barrierNum_ == 1) {
			Real min = *std::min_element(a.begin(), a.end());
			return std::exp(min) <= barrier_[0];
		}
		else {
			std::vector<Real> r(barrierNum_);
			std::transform(a.begin(), a.end(), barrier_.begin(), r.begin(), std::divides<Real>());
			Real min = *std::min_element(a.begin(), a.end());
			return std::exp(min) <= 1.0;
		}
	}

}