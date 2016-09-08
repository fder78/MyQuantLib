
#include <ql/math/interpolations/bicubicsplineinterpolation.hpp>
#include <ql/methods/finitedifferences/finitedifferencemodel.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmsnapshotcondition.hpp>
#include <eq_derivatives/autocallable_engine/two_dim/autocall_fdm2dimsolver.h>

namespace QuantLib {

    AutocallFdm2DimSolver::AutocallFdm2DimSolver(
                             const FdmSolverDesc& solverDesc,
                             const FdmSchemeDesc& schemeDesc,
                             const boost::shared_ptr<FdmLinearOpComposite>& op)
    : solverDesc_(solverDesc),
      schemeDesc_(schemeDesc),
      op_(op),
      thetaCondition_(new FdmSnapshotCondition(0.99*std::min(1.0/365.0, solverDesc.condition->stoppingTimes().empty() ? solverDesc.maturity : solverDesc.condition->stoppingTimes().front()))),
      conditions_(FdmStepConditionComposite::joinConditions(thetaCondition_, solverDesc.condition)),
      initialValues_(solverDesc.mesher->layout()->size()),
      resultValues_ (solverDesc.mesher->layout()->dim()[1], solverDesc.mesher->layout()->dim()[0]) {

        const boost::shared_ptr<FdmMesher> mesher = solverDesc.mesher;
        const boost::shared_ptr<FdmLinearOpLayout> layout = mesher->layout();

        x_.reserve(layout->dim()[0]);
        y_.reserve(layout->dim()[1]);

        const FdmLinearOpIterator endIter = layout->end();
        for (FdmLinearOpIterator iter = layout->begin(); iter != endIter; ++iter) {
            initialValues_[iter.index()] = solverDesc_.calculator->avgInnerValue(iter, solverDesc.maturity);
            if (!iter.coordinates()[1]) {
                x_.push_back(mesher->location(iter, 0));
            }
            if (!iter.coordinates()[0]) {
                y_.push_back(mesher->location(iter, 1));
            }
        }
    }


    void AutocallFdm2DimSolver::performCalculations() const {
        Array rhs(initialValues_.size());
        std::copy(initialValues_.begin(), initialValues_.end(), rhs.begin());

        FdmBackwardSolver(op_, solverDesc_.bcSet, conditions_, schemeDesc_)
            .rollback(rhs, solverDesc_.maturity, 0.0, solverDesc_.timeSteps, solverDesc_.dampingSteps);

        std::copy(rhs.begin(), rhs.end(), resultValues_.begin());
        interpolation_ = boost::shared_ptr<BicubicSpline> (
            new BicubicSpline(x_.begin(), x_.end(),
                              y_.begin(), y_.end(),
                              resultValues_));
    }

    Real AutocallFdm2DimSolver::interpolateAt(Real x, Real y) const {
        calculate();
        return interpolation_->operator()(x, y);
    }

    Real AutocallFdm2DimSolver::thetaAt(Real x, Real y) const {
        QL_REQUIRE(conditions_->stoppingTimes().front() > 0.0,
                   "stopping time at zero-> can't calculate theta");

        calculate();
        Matrix thetaValues(resultValues_.rows(), resultValues_.columns());

        const Array& rhs = thetaCondition_->getValues();
        std::copy(rhs.begin(), rhs.end(), thetaValues.begin());

        return (BicubicSpline(x_.begin(), x_.end(), y_.begin(), y_.end(), thetaValues)(x, y) - interpolateAt(x, y)) / thetaCondition_->getTime();
    }


    Real AutocallFdm2DimSolver::derivativeX(Real x, Real y) const {
        calculate();
        return interpolation_->derivativeX(x, y);
    }

    Real AutocallFdm2DimSolver::derivativeY(Real x, Real y) const {
        calculate();
        return interpolation_->derivativeY(x, y);
    }

    Real AutocallFdm2DimSolver::derivativeXX(Real x, Real y) const {
        calculate();
        return interpolation_->secondDerivativeX(x, y);
    }

    Real AutocallFdm2DimSolver::derivativeYY(Real x, Real y) const {
        calculate();
        return interpolation_->secondDerivativeY(x, y);
    }

    Real AutocallFdm2DimSolver::derivativeXY(Real x, Real y) const {
        calculate();
        return interpolation_->derivativeXY(x, y);
    }

}
