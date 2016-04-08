#include "participation_payoff.hpp"

namespace QuantLib {

	ParticipationPayoff::ParticipationPayoff(Real participation, Real strike, Period p) :
		participation_(participation), strike_(strike), p_(p) 
	{
		Frequency f = p_.frequency();
		strike_ /= f;
	}

    std::string ParticipationPayoff::name() const { return "Index Rangeaccrual Payoff"; }
    std::string ParticipationPayoff::description() const { return name(); }
    void ParticipationPayoff::accept(AcyclicVisitor& v) {
        Visitor<ParticipationPayoff>* v1 = dynamic_cast<Visitor<ParticipationPayoff>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            Payoff::accept(v);
    }
    Real ParticipationPayoff::operator()(Real s) const {
		return participation_ * s - strike_;
    }
}
