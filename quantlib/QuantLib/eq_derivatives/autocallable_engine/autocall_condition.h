#pragma once
#include <ql\math\array.hpp>

namespace QuantLib {
	
	class AutocallCondition {
	public:
		AutocallCondition() : barrier_(std::vector<Real>()), barrierNum_(0) {}
		AutocallCondition(Real barrier) : barrier_(std::vector<Real>(1,barrier)), barrierNum_(1) {}
		AutocallCondition(std::vector<Real> barrier) :barrier_(barrier), barrierNum_(barrier_.size()) {}
		virtual bool operator()(Array& a) = 0;
		std::vector<Real> getBarrier() {
			return barrier_;
		}
		Size getBarrierNumbers() const {
			return barrierNum_;
		}
	protected:
		std::vector<Real> barrier_;
		const Size barrierNum_;
	};
	
	class NullAutocallCondition : public AutocallCondition {
	public:
		NullAutocallCondition() : AutocallCondition() {}
		virtual bool operator()(Array& a) { return false; }
	};

	class MinUpCondition : public AutocallCondition {
	public:
		MinUpCondition(Real barrier) : AutocallCondition(barrier) {}
		MinUpCondition(std::vector<Real> barrier) : AutocallCondition(barrier) {}
		virtual bool operator()(Array& a);
	};

	class MinDownCondition : public AutocallCondition {
	public:
		MinDownCondition(Real barrier) : AutocallCondition(barrier) {}
		MinDownCondition(std::vector<Real> barrier) : AutocallCondition(barrier) {}
		virtual bool operator()(Array& a);
	};
}
