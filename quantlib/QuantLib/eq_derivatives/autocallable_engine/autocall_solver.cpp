
#include <ql/processes/blackscholesprocess.hpp>
#include <eq_derivatives/autocallable_engine/one_dim/autocall_fdm1dimsolver.h>
#include <eq_derivatives/autocallable_engine/one_dim/autocall_fdm1dblackscholesop.h>
#include <eq_derivatives/autocallable_engine/two_dim/autocall_fdm2dimsolver.h>
#include <eq_derivatives/autocallable_engine/two_dim/autocall_fdm2dblackscholesop.h>
#include <eq_derivatives/autocallable_engine/three_dim/autocall_fdm3dimsolver.h>
#include <eq_derivatives/autocallable_engine/three_dim/autocall_fdm3dblackscholesop.h>
#include <eq_derivatives/autocallable_engine/autocall_solver.h>


namespace QuantLib {

	AutocallSolver::AutocallSolver(
		const Handle<YieldTermStructure>& disc,
		const boost::shared_ptr<StochasticProcessArray>& process,
		const FdmSolverDesc& solverDesc,
		const FdmSchemeDesc& schemeDesc)
		: disc_(disc), process_(process),
		solverDesc_(solverDesc),
		schemeDesc_(schemeDesc) {
		for (Size i = 0; i < process_->size(); ++i)
			registerWith(process_->process(i));
	}


	void AutocallSolver::performCalculations() const {
		boost::shared_ptr<FdmLinearOpComposite> op;
		switch (process_->size()) {
		case 1:
			op = boost::shared_ptr<FdmLinearOpComposite>(
				new AutocallFdm1dBlackScholesOp(solverDesc_.mesher,
					disc_.currentLink(),
					boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process_->process(0)),
					solverDesc_.maturity));
			solver1d_ = boost::shared_ptr<AutocallFdm1DimSolver>(new AutocallFdm1DimSolver(solverDesc_, schemeDesc_, op));
			break;
		case 2:
			op = boost::shared_ptr<FdmLinearOpComposite>(
				new AutocallFdm2dBlackScholesOp(solverDesc_.mesher,
					disc_.currentLink(),
					boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process_->process(0)),
					boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process_->process(1)),
					process_->correlation()[0][1],
					solverDesc_.maturity));
			solver2d_ = boost::shared_ptr<AutocallFdm2DimSolver>(new AutocallFdm2DimSolver(solverDesc_, schemeDesc_, op));
			break;
		case 3:			
			op = boost::shared_ptr<FdmLinearOpComposite>(
			new AutocallFdm3dBlackScholesOp(solverDesc_.mesher,
				disc_.currentLink(),
				boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process_->process(0)),
				boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process_->process(1)),
				boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process_->process(2)),
				process_->correlation(),
				solverDesc_.maturity));
			solver3d_ = boost::shared_ptr<AutocallFdm3DimSolver>(new AutocallFdm3DimSolver(solverDesc_, schemeDesc_, op));
			break;
		default:
			QL_FAIL("Autocall solver cannot handle more than 3 assets.");
			break;
		}
	}
	Real AutocallSolver::valueAt(Real u) const {
		calculate();
		const Real x = std::log(u);
		return solver1d_->interpolateAt(x);
	}
	Real AutocallSolver::thetaAt(Real u) const {
		calculate();
		const Real x = std::log(u);
		return solver1d_->thetaAt(x);
	}
	Real AutocallSolver::valueAt(Real u, Real v) const {
		calculate();
		const Real x = std::log(u);
		const Real y = std::log(v);
		return solver2d_->interpolateAt(x, y);
	}
	Real AutocallSolver::thetaAt(Real u, Real v) const {
		calculate();
		const Real x = std::log(u);
		const Real y = std::log(v);
		return solver2d_->thetaAt(x, y);
	}	
	Real AutocallSolver::valueAt(Real u, Real v, Real w) const {
		calculate();
		const Real x = std::log(u);
		const Real y = std::log(v);
		const Real z = std::log(w);
		return solver3d_->interpolateAt(x, y, z);		
	}
	Real AutocallSolver::thetaAt(Real u, Real v, Real w) const {
		calculate();
		const Real x = std::log(u);
		const Real y = std::log(v);
		const Real z = std::log(w);
		return solver3d_->thetaAt(x, y, z);
	}
}
