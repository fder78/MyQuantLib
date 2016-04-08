#pragma once

#include <ql/option.hpp>
#include <ql/payoff.hpp>
#include <ql/time/period.hpp>

namespace QuantLib {

	class ParticipationPayoff : public Payoff {
	public:
		ParticipationPayoff(Real participation, Real strike, Period tenor=Period(Annual));
		std::string name() const;
		std::string description() const;
		Real operator()(Real price) const;
		virtual void accept(AcyclicVisitor&);
	private:
		Real participation_, strike_;
		Period p_;
	};

}

