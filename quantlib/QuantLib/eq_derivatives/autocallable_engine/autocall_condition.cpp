#include <eq_derivatives\autocallable_engine\autocall_condition.h>

namespace QuantLib {

	MinUpCondition::MinUpCondition(std::vector<Real> barrier)
		: AutocallCondition(barrier) {
	}

	bool MinUpCondition::operator()(Array& a) {
		if (barrierNum_ == 1) {
			Real min = *std::min_element(a.begin(), a.end());
			return min >= barrier_[0];
		}
		else {
			std::vector<Real> r(barrierNum_);
			std::transform(a.begin(), a.end(), barrier_.begin(), r.begin(), std::divides<Real>());
			Real min = *std::min_element(r.begin(), r.end());
			return min >= 1.0;
		}
	}


	MinDownCondition::MinDownCondition(std::vector<Real> barrier) 
		: AutocallCondition(barrier) {
	}

	bool MinDownCondition::operator()(Array& a) {
		if (barrierNum_ == 1) {
			Real min = *std::min_element(a.begin(), a.end());
			return min <= barrier_[0];
		}
		else {
			std::vector<Real> r(barrierNum_);
			std::transform(a.begin(), a.end(), barrier_.begin(), r.begin(), std::divides<Real>());
			Real min = *std::min_element(r.begin(), r.end());
			return min <= 1.0;
		}
	}

}