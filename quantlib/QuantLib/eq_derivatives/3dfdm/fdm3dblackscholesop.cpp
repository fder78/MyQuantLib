/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
Copyright (C) 2016 K.Hwang

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file Fdm3dBlackScholesOp.cpp
*/


#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include "fdm3dblackscholesop.hpp"
#include <ql/methods/finitedifferences/operators/secondordermixedderivativeop.hpp>

#if !defined(QL_NO_UBLAS_SUPPORT)
#include <boost/numeric/ublas/matrix.hpp>
#endif

namespace QuantLib {

	Fdm3dBlackScholesOp::Fdm3dBlackScholesOp(
		const boost::shared_ptr<FdmMesher>& mesher,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p3,
		const Matrix correlation,
		Time maturity,
		bool localVol,
		Real illegalLocalVolOverwrite)
		: mesher_(mesher),
		p1_(p1),
		p2_(p2),
		p3_(p3),
		localVol1_((localVol) ? p1->localVolatility().currentLink()
			: boost::shared_ptr<LocalVolTermStructure>()),
		localVol2_((localVol) ? p2->localVolatility().currentLink()
			: boost::shared_ptr<LocalVolTermStructure>()),
		localVol3_((localVol) ? p3->localVolatility().currentLink()
			: boost::shared_ptr<LocalVolTermStructure>()),
		x_((localVol) ? Array(Exp(mesher->locations(0))) : Array()),
		y_((localVol) ? Array(Exp(mesher->locations(1))) : Array()),
		z_((localVol) ? Array(Exp(mesher->locations(2))) : Array()),

		opX_(mesher, p1, p1->x0(), localVol, illegalLocalVolOverwrite, 0),
		opY_(mesher, p2, p2->x0(), localVol, illegalLocalVolOverwrite, 1),
		opZ_(mesher, p3, p3->x0(), localVol, illegalLocalVolOverwrite, 2),
		corrMapT12_(0, 1, mesher),
		corrMapTemplate12_(SecondOrderMixedDerivativeOp(0, 1, mesher)
			.mult(Array(mesher->layout()->size(), correlation[0][1]))),
		corrMapT13_(0, 2, mesher),
		corrMapTemplate13_(SecondOrderMixedDerivativeOp(0, 2, mesher)
			.mult(Array(mesher->layout()->size(), correlation[0][2]))),
		corrMapT23_(1, 2, mesher),
		corrMapTemplate23_(SecondOrderMixedDerivativeOp(1, 2, mesher)
			.mult(Array(mesher->layout()->size(), correlation[1][2]))),
		illegalLocalVolOverwrite_(illegalLocalVolOverwrite) {
	}

	Size Fdm3dBlackScholesOp::size() const {
		return 3;
	}

	void Fdm3dBlackScholesOp::setTime(Time t1, Time t2) {
		opX_.setTime(t1, t2);
		opY_.setTime(t1, t2);
		opZ_.setTime(t1, t2);

		if (localVol1_) {
			const boost::shared_ptr<FdmLinearOpLayout> layout = mesher_->layout();
			const FdmLinearOpIterator endIter = layout->end();

			Array vol1(layout->size()), vol2(layout->size()), vol3(layout->size());
			for (FdmLinearOpIterator iter = layout->begin(); iter != endIter; ++iter) {
				const Size i = iter.index();

				if (illegalLocalVolOverwrite_ < 0.0) {
					vol1[i] = localVol1_->localVol(0.5*(t1 + t2), x_[i], true);
					vol2[i] = localVol2_->localVol(0.5*(t1 + t2), y_[i], true);
					vol3[i] = localVol3_->localVol(0.5*(t1 + t2), z_[i], true);
				}
				else {
					try {
						vol1[i] = localVol1_->localVol(0.5*(t1 + t2), x_[i], true);
					}
					catch (Error&) {
						vol1[i] = illegalLocalVolOverwrite_;
					}
					try {
						vol2[i] = localVol2_->localVol(0.5*(t1 + t2), y_[i], true);
					}
					catch (Error&) {
						vol2[i] = illegalLocalVolOverwrite_;
					}
					try {
						vol3[i] = localVol3_->localVol(0.5*(t1 + t2), z_[i], true);
					}
					catch (Error&) {
						vol3[i] = illegalLocalVolOverwrite_;
					}
				}
			}
			corrMapT12_ = corrMapTemplate12_.mult(vol1*vol2);
			corrMapT13_ = corrMapTemplate12_.mult(vol1*vol3);
			corrMapT23_ = corrMapTemplate12_.mult(vol2*vol3);
		}
		else {
			const Real vol1 = p1_->blackVolatility()->blackForwardVol(t1, t2, p1_->x0());
			const Real vol2 = p2_->blackVolatility()->blackForwardVol(t1, t2, p2_->x0());
			const Real vol3 = p3_->blackVolatility()->blackForwardVol(t1, t2, p3_->x0());
			corrMapT12_ = corrMapTemplate12_.mult(Array(mesher_->layout()->size(), vol1*vol2));
			corrMapT13_ = corrMapTemplate13_.mult(Array(mesher_->layout()->size(), vol1*vol3));
			corrMapT23_ = corrMapTemplate23_.mult(Array(mesher_->layout()->size(), vol2*vol3));
		}

		currentForwardRate_ = p1_->riskFreeRate()->forwardRate(t1, t2, Continuous).rate();  //todo
	}

	Disposable<Array> Fdm3dBlackScholesOp::apply(const Array& x) const {
		return opX_.apply(x) + opY_.apply(x) + opZ_.apply(x) + apply_mixed(x);
	}

	Disposable<Array> Fdm3dBlackScholesOp::apply_mixed(const Array& x) const {
		return corrMapT12_.apply(x) + corrMapT13_.apply(x) + corrMapT23_.apply(x) + currentForwardRate_*x;
	}

	Disposable<Array> Fdm3dBlackScholesOp::apply_direction(Size direction, const Array& x) const {
		if (direction == 0) {
			return opX_.apply(x);
		}
		else if (direction == 1) {
			return opY_.apply(x);
		}
		else if (direction == 2) {
			return opZ_.apply(x);
		}
		else {
			QL_FAIL("direction is too large");
		}
	}

	Disposable<Array> Fdm3dBlackScholesOp::solve_splitting(Size direction, const Array& x, Real s) const {
		if (direction == 0) {
			return opX_.solve_splitting(direction, x, s);
		}
		else if (direction == 1) {
			return opY_.solve_splitting(direction, x, s);
		}
		else if (direction == 2) {
			return opZ_.solve_splitting(direction, x, s);
		}
		else
			QL_FAIL("direction is too large");
	}

	Disposable<Array> Fdm3dBlackScholesOp::preconditioner(const Array& r, Real dt) const {
		return solve_splitting(0, r, dt);
	}

#if !defined(QL_NO_UBLAS_SUPPORT)
	Disposable<std::vector<SparseMatrix> >
		Fdm3dBlackScholesOp::toMatrixDecomp() const {
		std::vector<SparseMatrix> retVal(4);
		retVal[0] = opX_.toMatrix();
		retVal[1] = opY_.toMatrix();
		retVal[2] = opZ_.toMatrix();
		retVal[3] = corrMapT12_.toMatrix() + corrMapT23_.toMatrix() + corrMapT13_.toMatrix()
			+ currentForwardRate_*boost::numeric::ublas::identity_matrix<Real>(mesher_->layout()->size());

		return retVal;
	}
#endif
}
