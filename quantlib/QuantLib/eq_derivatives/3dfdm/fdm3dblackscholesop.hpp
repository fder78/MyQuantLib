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


/*! \file Fdm3dBlackScholesOp.hpp
*/

#pragma once

#include <ql/methods/finitedifferences/operators/ninepointlinearop.hpp>
#include <ql/methods/finitedifferences/operators/fdmblackscholesop.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearopcomposite.hpp>

namespace QuantLib {

    class FdmMesher;
    class GeneralizedBlackScholesProcess;

    class Fdm3dBlackScholesOp : public FdmLinearOpComposite {
      public:
        Fdm3dBlackScholesOp(
            const boost::shared_ptr<FdmMesher>& mesher,
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
    
        Disposable<Array> apply_direction(Size direction,const Array& x) const;
        
        Disposable<Array> solve_splitting(Size direction,
                                          const Array& x, Real s) const;
        Disposable<Array> preconditioner(const Array& r, Real s) const;
    
#if !defined(QL_NO_UBLAS_SUPPORT)
        Disposable<std::vector<SparseMatrix> > toMatrixDecomp() const;
#endif
      private:
        const boost::shared_ptr<FdmMesher> mesher_;
        const boost::shared_ptr<GeneralizedBlackScholesProcess> p1_, p2_, p3_;
        const boost::shared_ptr<LocalVolTermStructure> localVol1_, localVol2_, localVol3_;
        const Array x_, y_, z_;
        
        Real currentForwardRate_;
        FdmBlackScholesOp opX_, opY_, opZ_;
        NinePointLinearOp corrMapT12_, corrMapT13_, corrMapT23_;
        const NinePointLinearOp corrMapTemplate12_, corrMapTemplate13_, corrMapTemplate23_;
        const Real illegalLocalVolOverwrite_;
    };
}
