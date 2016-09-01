#pragma once
#include <ql\math\array.hpp>

namespace QuantLib {
	
	class AutocallCondition {
	public:
		virtual bool operator()(Array& a) = 0;
	};

	class MinUpCondition : public AutocallCondition {
	public:
		MinUpCondition(Real barrier) : barrier_(barrier) {}
		virtual bool operator()(Array& a);
	private:
		Real barrier_;
	};

}
