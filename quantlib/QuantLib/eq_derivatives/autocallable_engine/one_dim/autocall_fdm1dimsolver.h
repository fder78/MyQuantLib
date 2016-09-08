#pragma once

#include <ql/handle.hpp>
#include <ql/math/matrix.hpp>
#include <ql/patterns/lazyobject.hpp>
#include <ql/methods/finitedifferences/solvers/fdmsolverdesc.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>


namespace QuantLib {

    class CubicInterpolation;
    class FdmSnapshotCondition;
	
    class AutocallFdm1DimSolver : public LazyObject {
      public:
        AutocallFdm1DimSolver(const FdmSolverDesc& solverDesc,
                      const FdmSchemeDesc& schemeDesc,
                      const boost::shared_ptr<FdmLinearOpComposite>& op);

        Real interpolateAt(Real x) const;
        Real thetaAt(Real x) const;

        Real derivativeX(Real x) const;
        Real derivativeXX(Real x) const;

      protected:
        void performCalculations() const;

      private:
        const FdmSolverDesc solverDesc_;
        const FdmSchemeDesc schemeDesc_;
        const boost::shared_ptr<FdmLinearOpComposite> op_;

        const boost::shared_ptr<FdmSnapshotCondition> thetaCondition_;
        const boost::shared_ptr<FdmStepConditionComposite> conditions_;

        std::vector<Real> x_, initialValues_;
        mutable Array resultValues_;
        mutable boost::shared_ptr<CubicInterpolation> interpolation_;
    };
}
