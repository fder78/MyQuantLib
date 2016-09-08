#pragma once
#include <ql/pricingengine.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>
#include <ql/processes/stochasticprocessarray.hpp>
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

		FdAutocallEngine(
			const boost::shared_ptr<YieldTermStructure>& disc,
			const boost::shared_ptr<StochasticProcessArray>& process,
			Size xGrid = 100,
			Size tGrid = 50, Size dampingSteps = 0,
			const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

		void calculate() const;

	private:
		const boost::shared_ptr<YieldTermStructure>& disc_;
		boost::shared_ptr<GeneralizedBlackScholesProcess> p1_;
		boost::shared_ptr<GeneralizedBlackScholesProcess> p2_;
		Real correlation_;
		boost::shared_ptr<StochasticProcessArray> process_;
		std::vector<Size> numGrid_;
		const Size tGrid_;
		const Size dampingSteps_;
		const FdmSchemeDesc schemeDesc_;
		const bool isGeneral_;
		Size assetNumber_;
	};
}