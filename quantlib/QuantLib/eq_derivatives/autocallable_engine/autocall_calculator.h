#pragma once

#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>

namespace QuantLib {

	class Payoff;
	class BasketPayoff;
	class FdmMesher;
	class FdmLinearOpIterator;

	class FdmAutocallInnerValue : public FdmInnerValueCalculator {
	public:
		FdmAutocallInnerValue(const boost::shared_ptr<BasketPayoff>& payoff,
			const boost::shared_ptr<FdmMesher>& mesher);

		Real innerValue(const FdmLinearOpIterator& iter, Time);
		Real avgInnerValue(const FdmLinearOpIterator& iter, Time);

	private:
		const boost::shared_ptr<BasketPayoff> payoff_;
		const boost::shared_ptr<FdmMesher> mesher_;
	};

}
