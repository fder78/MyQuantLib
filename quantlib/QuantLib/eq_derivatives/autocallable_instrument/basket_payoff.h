#pragma once
#include <ql/instruments/basketoption.hpp>
#include <ql/instruments/forward.hpp>

namespace QuantLib {
	
	class ArrayPayoff {
	public:
		virtual Real operator()(Array a) = 0;
	};

	class GeneralBasketPayoff : public BasketPayoff {
	public:
		GeneralBasketPayoff(const boost::shared_ptr<ArrayPayoff>& payoff) : 
			BasketPayoff(boost::shared_ptr<Payoff>(new ForwardTypePayoff(Position::Long, 0.0))),
			payoff_(payoff) {}
		Real accumulate(const Array &a) const {
			return (*payoff_)(a);
		}
	protected:
		const boost::shared_ptr<ArrayPayoff>& payoff_;
	};

	class TestPayoff : public ArrayPayoff {
	public:
		TestPayoff(std::vector<Real> params) : params_(params) {}
		Real operator()(Array a);

	private:
		std::vector<Real> params_;
	};

}