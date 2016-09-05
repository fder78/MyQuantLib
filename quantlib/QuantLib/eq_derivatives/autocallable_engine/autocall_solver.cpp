
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/solvers/fdm2dimsolver.hpp>
#include <ql/methods/finitedifferences/operators/fdm2dblackscholesop.hpp>
#include <eq_derivatives/autocallable_engine/autocall_solver.h>


namespace QuantLib {

	AutocallSolver::AutocallSolver(
		const Handle<GeneralizedBlackScholesProcess>& p1,
		const Handle<GeneralizedBlackScholesProcess>& p2,
		const Real correlation,
		const FdmSolverDesc& solverDesc,
		const FdmSchemeDesc& schemeDesc)
		: p1_(p1),
		p2_(p2),
		correlation_(correlation),
		solverDesc_(solverDesc),
		schemeDesc_(schemeDesc) {
		registerWith(p1_);
		registerWith(p2_);
	}


	void AutocallSolver::performCalculations() const {

		boost::shared_ptr<Fdm2dBlackScholesOp> op(
			new Fdm2dBlackScholesOp(solverDesc_.mesher,
				p1_.currentLink(),
				p2_.currentLink(),
				correlation_,
				solverDesc_.maturity));

		solver_ = boost::shared_ptr<Fdm2DimSolver>(
			new Fdm2DimSolver(solverDesc_, schemeDesc_, op));
	}

	Real AutocallSolver::valueAt(Real u, Real v) const {
		calculate();
		const Real x = std::log(u);
		const Real y = std::log(v);

		return solver_->interpolateAt(x, y);
	}

	Real AutocallSolver::thetaAt(Real u, Real v) const {
		calculate();
		const Real x = std::log(u);
		const Real y = std::log(v);
		return solver_->thetaAt(x, y);
	}


	Real AutocallSolver::deltaXat(Real u, Real v) const {
		calculate();

		const Real x = std::log(u);
		const Real y = std::log(v);

		return solver_->derivativeX(x, y) / u;
	}

	Real AutocallSolver::deltaYat(Real u, Real v) const {
		calculate();

		const Real x = std::log(u);
		const Real y = std::log(v);

		return solver_->derivativeY(x, y) / v;
	}

	Real AutocallSolver::gammaXat(Real u, Real v) const {
		calculate();

		const Real x = std::log(u);
		const Real y = std::log(v);

		return (solver_->derivativeXX(x, y)
			- solver_->derivativeX(x, y)) / (u*u);
	}

	Real AutocallSolver::gammaYat(Real u, Real v) const {
		calculate();

		const Real x = std::log(u);
		const Real y = std::log(v);

		return (solver_->derivativeYY(x, y)
			- solver_->derivativeY(x, y)) / (v*v);
	}
}
