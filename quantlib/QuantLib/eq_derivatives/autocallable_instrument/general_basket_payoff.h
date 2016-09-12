#pragma once
#include <ql/instruments/basketoption.hpp>
#include <ql/instruments/forward.hpp>
#include <eq_derivatives/autocallable_instrument/general_payoff.h>

namespace QuantLib {
	
	class ArrayPayoff {
	public:
		virtual Real operator()(const Array& a) = 0;
	};

	class GeneralBasketPayoff : public BasketPayoff {
	public:
		GeneralBasketPayoff(const boost::shared_ptr<ArrayPayoff>& payoff);
		Real accumulate(const Array &a) const {
			return (*payoff_)(a);
		}
	protected:
		const boost::shared_ptr<ArrayPayoff>& payoff_;
	};

	class MinOfPayoffs : public ArrayPayoff {
	public:
		MinOfPayoffs(std::vector<boost::shared_ptr<Payoff> > payoffs);
		Real operator()(const Array& a);

	private:
		std::vector<boost::shared_ptr<Payoff> > payoffs_;
	};

}