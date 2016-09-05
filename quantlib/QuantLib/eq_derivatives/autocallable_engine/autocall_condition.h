#pragma once
#include <ql\math\array.hpp>

namespace QuantLib {
	
	class AutocallCondition {
	public:
		AutocallCondition(Real barrier) : barrier_(barrier) {}
		virtual bool operator()(Array& a) = 0;
		Real getBarrier() {
			return barrier_;
		}
	protected:
		Real barrier_;
	};
	
	class NullAutocallCondition : public AutocallCondition {
	public:
		NullAutocallCondition() : AutocallCondition(Null<Real>()) {}
		virtual bool operator()(Array& a) { return false; }
	};

	class MinUpCondition : public AutocallCondition {
	public:
		MinUpCondition(Real barrier) : AutocallCondition(barrier) {}
		virtual bool operator()(Array& a);
	};

	class MinDownCondition : public AutocallCondition {
	public:
		MinDownCondition(Real barrier) : AutocallCondition(barrier) {}
		virtual bool operator()(Array& a);
	};
}
