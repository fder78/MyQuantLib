
#include <ql/math/functional.hpp>
#include <ql/instruments/payoffs.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/operators/secondderivativeop.hpp>

#include <eq_derivatives\autocallable_engine\one_dim\autocall_fdm1dblackscholesop.h>

namespace QuantLib {

    AutocallFdm1dBlackScholesOp::AutocallFdm1dBlackScholesOp(
        const boost::shared_ptr<FdmMesher>& mesher,
		const boost::shared_ptr<YieldTermStructure>& disc,
        const boost::shared_ptr<GeneralizedBlackScholesProcess> & bsProcess,
        Real strike,
        bool localVol,
        Real illegalLocalVolOverwrite,
        Size direction)
    : mesher_(mesher),
		disc_(disc),
      rTS_   (bsProcess->riskFreeRate().currentLink()),
      qTS_   (bsProcess->dividendYield().currentLink()),
      volTS_ (bsProcess->blackVolatility().currentLink()),
      localVol_((localVol) ? bsProcess->localVolatility().currentLink()
                           : boost::shared_ptr<LocalVolTermStructure>()),
      x_     ((localVol) ? Array(Exp(mesher->locations(direction))) : Array()),
      dxMap_ (FirstDerivativeOp(direction, mesher)),
      dxxMap_(SecondDerivativeOp(direction, mesher)),
      mapT_  (direction, mesher),
      strike_(strike),
      illegalLocalVolOverwrite_(illegalLocalVolOverwrite),
      direction_(direction) {
    }

    void AutocallFdm1dBlackScholesOp::setTime(Time t1, Time t2) {
        const Rate r = rTS_->forwardRate(t1, t2, Continuous).rate();
        const Rate q = qTS_->forwardRate(t1, t2, Continuous).rate();
		const Rate currentForwardRate = disc_->forwardRate(t1, t2, Continuous).rate();

        if (localVol_) {
            const boost::shared_ptr<FdmLinearOpLayout> layout=mesher_->layout();
            const FdmLinearOpIterator endIter = layout->end();

            Array v(layout->size());
            for (FdmLinearOpIterator iter = layout->begin();
                 iter!=endIter; ++iter) {
                const Size i = iter.index();

                if (illegalLocalVolOverwrite_ < 0.0) {
                    v[i] = square<Real>()(
                                localVol_->localVol(0.5*(t1+t2), x_[i], true));
                }
                else {
                    try {
                        v[i] = square<Real>()(
                                localVol_->localVol(0.5*(t1+t2), x_[i], true));
                    } catch (Error&) {
                        v[i] = square<Real>()(illegalLocalVolOverwrite_);
                    }

                }
            }
            mapT_.axpyb(r - q - 0.5*v, dxMap_,
                        dxxMap_.mult(0.5*v), Array(1, -currentForwardRate));
        }
        else {
            const Real v
                = volTS_->blackForwardVariance(t1, t2, strike_)/(t2-t1);
            mapT_.axpyb(Array(1, r - q - 0.5*v), dxMap_,
                        dxxMap_.mult(0.5*Array(mesher_->layout()->size(), v)),
                        Array(1, -currentForwardRate));
        }
    }

    Size AutocallFdm1dBlackScholesOp::size() const {
        return 1u;
    }

    Disposable<Array> AutocallFdm1dBlackScholesOp::apply(const Array& u) const {
        return mapT_.apply(u);
    }

    Disposable<Array> AutocallFdm1dBlackScholesOp::apply_direction(Size direction,
                                                    const Array& r) const {
        if (direction == direction_)
            return mapT_.apply(r);
        else {
            Array retVal(r.size(), 0.0);
            return retVal;
        }
    }

    Disposable<Array> AutocallFdm1dBlackScholesOp::apply_mixed(const Array& r) const {
        Array retVal(r.size(), 0.0);
        return retVal;
    }

    Disposable<Array> AutocallFdm1dBlackScholesOp::solve_splitting(Size direction,
                                                const Array& r, Real dt) const {
        if (direction == direction_)
            return mapT_.solve_splitting(r, dt, 1.0);
        else {
            Array retVal(r);
            return retVal;
        }
    }

    Disposable<Array> AutocallFdm1dBlackScholesOp::preconditioner(const Array& r,
                                                        Real dt) const {
        return solve_splitting(direction_, r, dt);
    }

#if !defined(QL_NO_UBLAS_SUPPORT)
    Disposable<std::vector<SparseMatrix> >
    AutocallFdm1dBlackScholesOp::toMatrixDecomp() const {
        std::vector<SparseMatrix> retVal(1, mapT_.toMatrix());
        return retVal;
    }
#endif
}
