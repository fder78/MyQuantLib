#pragma once
#include <vector>
#include <ql/instruments/payoffs.hpp>

namespace QuantLib {
	class GeneralPayoff :public Payoff {
	public:
		GeneralPayoff(const std::vector<Real> startPoints, const std::vector<Real> startPayoffs, const std::vector<Real> slopes);
		std::string name() const { return std::string("General Payoff"); }
		std::string description() const { return std::string("General Payoff"); }
		Real operator()(Real price) const;
	private:
		const std::vector<Real> startPoints_;
		const std::vector<Real> slopes_, startPayoffs_;
		virtual void accept(AcyclicVisitor&);
	};

}