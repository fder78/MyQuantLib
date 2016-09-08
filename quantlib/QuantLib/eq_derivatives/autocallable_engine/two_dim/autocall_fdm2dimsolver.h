#pragma once

#include <ql/handle.hpp>
#include <ql/math/matrix.hpp>
#include <ql/patterns/lazyobject.hpp>
#include <ql/methods/finitedifferences/solvers/fdmsolverdesc.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>


namespace QuantLib {

    class BicubicSpline;
    class FdmSnapshotCondition;

    class AutocallFdm2DimSolver : public LazyObject {
      public:
        AutocallFdm2DimSolver(const FdmSolverDesc& solverDesc,
                      const FdmSchemeDesc& schemeDesc,
                      const boost::shared_ptr<FdmLinearOpComposite>& op);

        Real interpolateAt(Real x, Real y) const;
        Real thetaAt(Real x, Real y) const;

        Real derivativeX(Real x, Real y) const;
        Real derivativeY(Real x, Real y) const;
        Real derivativeXX(Real x, Real y) const;
        Real derivativeYY(Real x, Real y) const;
        Real derivativeXY(Real x, Real y) const;

      protected:
        void performCalculations() const;

      private:
        const FdmSolverDesc solverDesc_;
        const FdmSchemeDesc schemeDesc_;
        const boost::shared_ptr<FdmLinearOpComposite> op_;

        const boost::shared_ptr<FdmSnapshotCondition> thetaCondition_;
        const boost::shared_ptr<FdmStepConditionComposite> conditions_;

        std::vector<Real> x_, y_, initialValues_;
        mutable Matrix resultValues_;
        mutable boost::shared_ptr<BicubicSpline> interpolation_;
    };
}