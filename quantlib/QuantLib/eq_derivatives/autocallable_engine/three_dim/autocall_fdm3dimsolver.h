#pragma once

#include <ql/math/matrix.hpp>
#include <ql/patterns/lazyobject.hpp>
#include <ql/methods/finitedifferences/solvers/fdmsolverdesc.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>

namespace QuantLib {

	class BicubicSpline;
	class FdmSnapshotCondition;

	class AutocallFdm3DimSolver : public LazyObject {
	public:
		AutocallFdm3DimSolver(const FdmSolverDesc& solverDesc,
			const FdmSchemeDesc& schemeDesc,
			const boost::shared_ptr<FdmLinearOpComposite>& op);

		void performCalculations() const;

		Real interpolateAt(Real x, Real y, Rate z) const;
		Real thetaAt(Real x, Real y, Rate z) const;

	private:
		const FdmSolverDesc solverDesc_;
		const FdmSchemeDesc schemeDesc_;
		const boost::shared_ptr<FdmLinearOpComposite> op_;

		const boost::shared_ptr<FdmSnapshotCondition> thetaCondition_;
		const boost::shared_ptr<FdmStepConditionComposite> conditions_;

		std::vector<Real> x_, y_, z_, initialValues_;
		mutable std::vector<Matrix> resultValues_;
		mutable std::vector<boost::shared_ptr<BicubicSpline> > interpolation_;
	};
}
