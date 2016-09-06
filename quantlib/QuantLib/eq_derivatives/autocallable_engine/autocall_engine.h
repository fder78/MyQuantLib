#pragma once
#include <ql/pricingengine.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>

#include <eq_derivatives\autocallable_instrument\autocallable_note.h>

namespace QuantLib {

	class FdAutocallEngine : public AutocallableNote::engine {
	public:
		FdAutocallEngine(
			const boost::shared_ptr<YieldTermStructure>& disc,
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
			Real correlation,
			Size xGrid = 100, Size yGrid = 100,
			Size tGrid = 50, Size dampingSteps = 0,
			const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

		void calculate() const;

	private:
		const boost::shared_ptr<YieldTermStructure>& disc_;
		const boost::shared_ptr<GeneralizedBlackScholesProcess> p1_;
		const boost::shared_ptr<GeneralizedBlackScholesProcess> p2_;
		const Real correlation_;
		const Size xGrid_, yGrid_, tGrid_;
		const Size dampingSteps_;
		const FdmSchemeDesc schemeDesc_;
	};
}