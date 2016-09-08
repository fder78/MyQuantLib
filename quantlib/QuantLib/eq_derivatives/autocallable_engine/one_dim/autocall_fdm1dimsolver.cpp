
#include <ql/math/interpolations/cubicinterpolation.hpp>
#include <ql/methods/finitedifferences/finitedifferencemodel.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmsnapshotcondition.hpp>

#include <eq_derivatives\autocallable_engine\one_dim\autocall_fdm1dimsolver.h>

namespace QuantLib {

    AutocallFdm1DimSolver::AutocallFdm1DimSolver(
                             const FdmSolverDesc& solverDesc,
                             const FdmSchemeDesc& schemeDesc,
                             const boost::shared_ptr<FdmLinearOpComposite>& op)
    : solverDesc_(solverDesc),
      schemeDesc_(schemeDesc),
      op_(op),
      thetaCondition_(new FdmSnapshotCondition(0.99*std::min(1.0/365.0, solverDesc.condition->stoppingTimes().empty() ? solverDesc.maturity : solverDesc.condition->stoppingTimes().front()))),
      conditions_(FdmStepConditionComposite::joinConditions(thetaCondition_, solverDesc.condition)),
      x_            (solverDesc.mesher->layout()->size()),
      initialValues_(solverDesc.mesher->layout()->size()),
      resultValues_ (solverDesc.mesher->layout()->size()) {

        const boost::shared_ptr<FdmMesher> mesher = solverDesc.mesher;
        const boost::shared_ptr<FdmLinearOpLayout> layout = mesher->layout();

        const FdmLinearOpIterator endIter = layout->end();
        for (FdmLinearOpIterator iter = layout->begin(); iter != endIter;
             ++iter) {
            initialValues_[iter.index()]
                 = solverDesc_.calculator->avgInnerValue(iter,
                                                         solverDesc.maturity);
            x_[iter.index()] = mesher->location(iter, 0);
        }
    }


    void AutocallFdm1DimSolver::performCalculations() const {
        Array rhs(initialValues_.size());
        std::copy(initialValues_.begin(), initialValues_.end(), rhs.begin());

        FdmBackwardSolver(op_, solverDesc_.bcSet, conditions_, schemeDesc_)
            .rollback(rhs, solverDesc_.maturity, 0.0,
                      solverDesc_.timeSteps, solverDesc_.dampingSteps);

        std::copy(rhs.begin(), rhs.end(), resultValues_.begin());
        interpolation_ = boost::shared_ptr<CubicInterpolation>(new
            MonotonicCubicNaturalSpline(x_.begin(), x_.end(),
                                        resultValues_.begin()));
    }

    Real AutocallFdm1DimSolver::interpolateAt(Real x) const {
        calculate();
        return interpolation_->operator()(x);
    }

    Real AutocallFdm1DimSolver::thetaAt(Real x) const {
        QL_REQUIRE(conditions_->stoppingTimes().front() > 0.0,
                   "stopping time at zero-> can't calculate theta");

        calculate();
        Array thetaValues(resultValues_.size());

        const Array& rhs = thetaCondition_->getValues();
        std::copy(rhs.begin(), rhs.end(), thetaValues.begin());

        Real temp = MonotonicCubicNaturalSpline(x_.begin(), x_.end(), thetaValues.begin())(x);
        return ( temp - interpolateAt(x) ) / thetaCondition_->getTime();
    }


    Real AutocallFdm1DimSolver::derivativeX(Real x) const {
        calculate();
        return interpolation_->derivative(x);
    }

    Real AutocallFdm1DimSolver::derivativeXX(Real x) const {
        calculate();
        return interpolation_->secondDerivative(x);
    }
}
