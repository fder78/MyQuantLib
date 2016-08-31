#pragma once


#include "callable_index_rangeaccrual.hpp"

#include <ql/pricingengine.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>

namespace QuantLib {
	class Fd2dCallableIndexRAEngine : public CallableIndexRangeAccrual::engine {
	public:
		Fd2dCallableIndexRAEngine(
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
			Real correlation,
			Size xGrid = 100, Size yGrid = 100,
			Size tGrid = 50, Size dampingSteps = 0,
			const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

		void calculate() const;

	private:
		const boost::shared_ptr<GeneralizedBlackScholesProcess> p1_;
		const boost::shared_ptr<GeneralizedBlackScholesProcess> p2_;
		const Real correlation_;
		const Size xGrid_, yGrid_, tGrid_;
		const Size dampingSteps_;
		const FdmSchemeDesc schemeDesc_;
	};
}
