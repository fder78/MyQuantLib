#pragma once
#include <eq_derivatives\autocallable_instrument\general_basket_payoff.h>

namespace QuantLib {

	GeneralBasketPayoff::GeneralBasketPayoff(const boost::shared_ptr<ArrayPayoff>& payoff) :
		BasketPayoff(boost::shared_ptr<Payoff>(new ForwardTypePayoff(Position::Long, 0.0))),
		payoff_(payoff) {
	}

	MinOfPayoffs::MinOfPayoffs(std::vector<boost::shared_ptr<Payoff> > payoffs) 
		: payoffs_(payoffs) {
	}

	Real MinOfPayoffs::operator()(const Array& a) {
		QL_REQUIRE(a.size() == payoffs_.size(), "Number of asset mismatch");
		Real p = QL_MAX_REAL;
		for (Size i = 0; i < a.size(); ++i) {
			Real temp = payoffs_[i]->operator()(a[i]);
			p = (temp < p) ? temp : p;
		}
		return p;
	}
}