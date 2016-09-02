
#include <eq_derivatives\autocallable_instrument\general_payoff.h>

namespace QuantLib {

	GeneralPayoff::GeneralPayoff(const std::vector<Real> startPoints, const std::vector<Real> startPayoffs, const std::vector<Real> slopes)
	: startPoints_(startPoints), startPayoffs_(startPayoffs), slopes_(slopes) {
		QL_REQUIRE(startPoints_[0] == 0.0, "Start point of a general payoff should be 0");
		QL_REQUIRE(startPoints_.size() == startPayoffs_.size() && startPoints_.size() == slopes.size(), 
			"input args of general payoff should have the same number of elements");
		for (Size i = 1; i < startPoints_.size(); ++i) {
			QL_REQUIRE(startPoints_[i] > startPoints_[i - 1], "start points should increase");
		}
	}

	Real GeneralPayoff::operator()(Real p) const {
		QL_REQUIRE(p >= 0.0, "price should be positive");
		Size idx = std::upper_bound(startPoints_.begin(), startPoints_.end(), p) - startPoints_.begin() - 1;
		return startPayoffs_[idx] + slopes_[idx] * (p - startPoints_[idx]);
	}

	void GeneralPayoff::accept(AcyclicVisitor& v) {
		Visitor<GeneralPayoff>* v1 =
			dynamic_cast<Visitor<GeneralPayoff>*>(&v);
		if (v1 != 0)
			v1->visit(*this);
		else
			Payoff::accept(v);
	}

}