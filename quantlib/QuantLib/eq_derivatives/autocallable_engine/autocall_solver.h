#pragma once

#include <ql/handle.hpp>
#include <ql/patterns/lazyobject.hpp>
#include <ql/methods/finitedifferences/solvers/fdmsolverdesc.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>
#include <ql/processes/stochasticprocessarray.hpp>

namespace QuantLib {

	class AutocallFdm1DimSolver;
	class AutocallFdm2DimSolver;
	class AutocallFdm3DimSolver;
	class GeneralizedBlackScholesProcess;

	class AutocallSolver : public LazyObject {
	public:
		AutocallSolver(
			const Handle<YieldTermStructure>& disc,
			const boost::shared_ptr<StochasticProcessArray>& process,
			const FdmSolverDesc& solverDesc,
			const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

		Real valueAt(Real x) const;
		Real thetaAt(Real x) const;
		Real valueAt(Real x, Real y) const;
		Real thetaAt(Real x, Real y) const;
		Real valueAt(Real x, Real y, Real z) const;
		Real thetaAt(Real x, Real y, Real z) const;

	protected:
		void performCalculations() const;

	private:
		const Handle<YieldTermStructure> disc_;
		const boost::shared_ptr<StochasticProcessArray>& process_;
		const FdmSolverDesc solverDesc_;
		const FdmSchemeDesc schemeDesc_;

		mutable boost::shared_ptr<AutocallFdm1DimSolver> solver1d_;
		mutable boost::shared_ptr<AutocallFdm2DimSolver> solver2d_;
		mutable boost::shared_ptr<AutocallFdm3DimSolver> solver3d_;
	};
}
