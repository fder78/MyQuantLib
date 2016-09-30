#pragma once

#include <ql/payoff.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/operators/firstderivativeop.hpp>
#include <ql/methods/finitedifferences/operators/triplebandlinearop.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearopcomposite.hpp>

namespace QuantLib {

	class Autocall_FdmBlackScholesOp : public FdmLinearOpComposite {
	public:
		Autocall_FdmBlackScholesOp(
			const boost::shared_ptr<FdmMesher>& mesher,
			const boost::shared_ptr<GeneralizedBlackScholesProcess>& process,
			const boost::shared_ptr<YieldTermStructure>& disc,
			Real strike,
			bool localVol = false,
			Real illegalLocalVolOverwrite = -Null<Real>(),
			Size direction = 0);

		Size size() const;
		void setTime(Time t1, Time t2);

		Disposable<Array> apply(const Array& r) const;
		Disposable<Array> apply_mixed(const Array& r) const;
		Disposable<Array> apply_direction(Size direction,
			const Array& r) const;
		Disposable<Array> solve_splitting(Size direction,
			const Array& r, Real s) const;
		Disposable<Array> preconditioner(const Array& r, Real s) const;

#if !defined(QL_NO_UBLAS_SUPPORT)
		Disposable<std::vector<SparseMatrix> > toMatrixDecomp() const;
#endif
	private:
		const boost::shared_ptr<FdmMesher> mesher_;
		const boost::shared_ptr<YieldTermStructure> rTS_, qTS_, disc_;
		const boost::shared_ptr<BlackVolTermStructure> volTS_;
		const boost::shared_ptr<LocalVolTermStructure> localVol_;
		const Array x_;
		const FirstDerivativeOp  dxMap_;
		const TripleBandLinearOp dxxMap_;
		TripleBandLinearOp mapT_;
		const Real strike_;
		const Real illegalLocalVolOverwrite_;
		const Size direction_, ndim_;
	};
}
