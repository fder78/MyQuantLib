
#pragma once

#include <ql/methods/finitedifferences/operators/ninepointlinearop.hpp>
#include <eq_derivatives/autocallable_engine/autocall_fdmblackscholesop.h>
#include <ql/methods/finitedifferences/operators/fdmlinearopcomposite.hpp>

namespace QuantLib {

	class FdmMesher;
	class GeneralizedBlackScholesProcess;

	class AutocallFdm3dBlackScholesOp : public FdmLinearOpComposite {
	public:
		AutocallFdm3dBlackScholesOp(
			const boost::shared_ptr<FdmMesher>& mesher,
			const boost::shared_ptr<YieldTermStructure>& disc,
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& p3,
			const Matrix correlation,
			Time maturity,
			bool localVol = false,
			Real illegalLocalVolOverwrite = -Null<Real>());

		Size size() const;
		void setTime(Time t1, Time t2);
		Disposable<Array> apply(const Array& x) const;
		Disposable<Array> apply_mixed(const Array& x) const;

		Disposable<Array> apply_direction(Size direction, const Array& x) const;

		Disposable<Array> solve_splitting(Size direction,
			const Array& x, Real s) const;
		Disposable<Array> preconditioner(const Array& r, Real s) const;

#if !defined(QL_NO_UBLAS_SUPPORT)
		Disposable<std::vector<SparseMatrix> > toMatrixDecomp() const;
#endif
	private:
		const boost::shared_ptr<FdmMesher> mesher_;
		const boost::shared_ptr<GeneralizedBlackScholesProcess> p1_, p2_, p3_;
		const boost::shared_ptr<YieldTermStructure> disc_;
		const boost::shared_ptr<LocalVolTermStructure> localVol1_, localVol2_, localVol3_;
		const Array x_, y_, z_;

		Real currentForwardRate_;
		Autocall_FdmBlackScholesOp opX_, opY_, opZ_;
		NinePointLinearOp corrMapT12_, corrMapT13_, corrMapT23_;
		const NinePointLinearOp corrMapTemplate12_, corrMapTemplate13_, corrMapTemplate23_;
		const Real illegalLocalVolOverwrite_;
	};
}
