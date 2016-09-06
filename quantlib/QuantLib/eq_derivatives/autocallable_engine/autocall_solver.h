#pragma once

#include <ql/handle.hpp>
#include <ql/patterns/lazyobject.hpp>
#include <ql/methods/finitedifferences/solvers/fdmsolverdesc.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>

namespace QuantLib {

	class AutocallFdm2DimSolver;
	class GeneralizedBlackScholesProcess;

	class AutocallSolver : public LazyObject {
	public:
		AutocallSolver(
			const Handle<YieldTermStructure>& disc,
			const Handle<GeneralizedBlackScholesProcess>& p1,
			const Handle<GeneralizedBlackScholesProcess>& p2,
			const Real correlation,
			const FdmSolverDesc& solverDesc,
			const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

		Real valueAt(Real x, Real y) const;
		Real thetaAt(Real x, Real y) const;

		Real deltaXat(Real x, Real y) const;
		Real deltaYat(Real x, Real y) const;
		Real gammaXat(Real x, Real y) const;
		Real gammaYat(Real x, Real y) const;

	protected:
		void performCalculations() const;

	private:
		const Handle<YieldTermStructure> disc_;
		const Handle<GeneralizedBlackScholesProcess> p1_;
		const Handle<GeneralizedBlackScholesProcess> p2_;
		const Real correlation_;
		const FdmSolverDesc solverDesc_;
		const FdmSchemeDesc schemeDesc_;

		mutable boost::shared_ptr<AutocallFdm2DimSolver> solver_;
	};
}
