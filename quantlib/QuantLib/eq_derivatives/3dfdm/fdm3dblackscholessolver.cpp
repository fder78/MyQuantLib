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

#include <ql/methods/finitedifferences/solvers/fdm3dimsolver.hpp>
#include <ql/methods/finitedifferences/utilities/fdmquantohelper.hpp>
#include "fdm3dblackscholesop.hpp"
#include "fdm3dblackscholessolver.hpp"

namespace QuantLib {

	Fdm3dBlackScholesSolver::Fdm3dBlackScholesSolver(
		const Handle<GeneralizedBlackScholesProcess>& p1,
		const Handle<GeneralizedBlackScholesProcess>& p2,
		const Handle<GeneralizedBlackScholesProcess>& p3,
		const Matrix corr,
		const FdmSolverDesc& solverDesc,
		const FdmSchemeDesc& schemeDesc)
		: p1_(p1), p2_(p2), p3_(p3),
		corr_(corr),
		solverDesc_(solverDesc),
		schemeDesc_(schemeDesc) {

		registerWith(p1);
		registerWith(p2);
		registerWith(p3);
	}

	void Fdm3dBlackScholesSolver::performCalculations() const {
		const boost::shared_ptr<FdmLinearOpComposite> op(
			new Fdm3dBlackScholesOp(solverDesc_.mesher,
				p1_.currentLink(),
				p2_.currentLink(),
				p3_.currentLink(),
				corr_,
				solverDesc_.maturity));

		solver_ = boost::shared_ptr<Fdm3DimSolver>(
			new Fdm3DimSolver(solverDesc_, schemeDesc_, op));
	}

	Real Fdm3dBlackScholesSolver::valueAt(Real s1, Real s2, Real s3) const {
		calculate();

		const Real x = std::log(s1);
		const Real y = std::log(s2);
		const Real z = std::log(s3);
		return solver_->interpolateAt(x, y, z);
	}

	Real Fdm3dBlackScholesSolver::deltaAt(Real s1, Real s2, Real s3, Real eps)
		const {
		return (valueAt(s1 + eps, s2, s3) - valueAt(s1 - eps, s2, s3)) / (2 * eps);
	}

	Real Fdm3dBlackScholesSolver::gammaAt(Real s1, Real s2, Real s3, Real eps) const {
		return (valueAt(s1 + eps, s2, s3) + valueAt(s1 - eps, s2, s3) - 2 * valueAt(s1, s2, s3)) / (eps*eps);
	}

	Real Fdm3dBlackScholesSolver::thetaAt(Real s1, Real s2, Real s3) const {
		calculate();
		const Real x = std::log(s1);
		const Real y = std::log(s2);
		const Real z = std::log(s3);
		return solver_->thetaAt(x, y, z);
	}
}
