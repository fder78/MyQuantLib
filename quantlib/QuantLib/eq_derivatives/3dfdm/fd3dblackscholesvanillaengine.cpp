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

#include <ql/exercise.hpp>
#include "fdm3dblackscholessolver.hpp"
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmeshercomposite.hpp>
#include <ql/methods/finitedifferences/stepconditions/fdmstepconditioncomposite.hpp>
#include <ql/methods/finitedifferences/meshers/fdmblackscholesmesher.hpp>
#include "fd3dBlackScholesVanillaEngine.hpp"

namespace QuantLib {

	Fd3dBlackScholesVanillaEngine::Fd3dBlackScholesVanillaEngine(
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
		const boost::shared_ptr<GeneralizedBlackScholesProcess>& p3,
		Matrix correlation,
		std::vector<Size> grid, Size tGrid, Size dampingSteps,
		const FdmSchemeDesc& schemeDesc)
		: p1_(p1), p2_(p2), p3_(p3),
		correlation_(correlation),
		xGrid_(grid[0]), yGrid_(grid[1]), zGrid_(grid[2]), tGrid_(tGrid),
		dampingSteps_(dampingSteps),
		schemeDesc_(schemeDesc) {
	}

	void Fd3dBlackScholesVanillaEngine::calculate() const {
		// 1. Payoff
		const boost::shared_ptr<BasketPayoff> payoff = boost::dynamic_pointer_cast<BasketPayoff>(arguments_.payoff);

		// 2. Mesher
		const Time maturity = p1_->time(arguments_.exercise->lastDate());
		const boost::shared_ptr<Fdm1dMesher> em1(
			new FdmBlackScholesMesher(xGrid_, p1_, maturity, p1_->x0(), Null<Real>(), Null<Real>(), 0.0001, 1.5, std::pair<Real, Real>(p1_->x0(), 0.1)));

		const boost::shared_ptr<Fdm1dMesher> em2(
			new FdmBlackScholesMesher(yGrid_, p2_, maturity, p2_->x0(), Null<Real>(), Null<Real>(), 0.0001, 1.5, std::pair<Real, Real>(p2_->x0(), 0.1)));

		const boost::shared_ptr<Fdm1dMesher> em3(
			new FdmBlackScholesMesher(zGrid_, p3_, maturity, p3_->x0(), Null<Real>(), Null<Real>(), 0.0001, 1.5, std::pair<Real, Real>(p3_->x0(), 0.1)));

		const boost::shared_ptr<FdmMesher> mesher(new FdmMesherComposite(em1, em2, em3));

		// 3. Calculator
		const boost::shared_ptr<FdmInnerValueCalculator> calculator(new FdmLogBasketInnerValue(payoff, mesher));

		// 4. Step conditions
		const boost::shared_ptr<FdmStepConditionComposite> conditions =
			FdmStepConditionComposite::vanillaComposite(DividendSchedule(), arguments_.exercise, mesher, calculator, p1_->riskFreeRate()->referenceDate(), p1_->riskFreeRate()->dayCounter());

		// 5. Boundary conditions
		const FdmBoundaryConditionSet boundaries;

		// 6. Solver
		const FdmSolverDesc solverDesc = { mesher, boundaries,
										   conditions, calculator,
										   maturity, tGrid_, dampingSteps_ };

		boost::shared_ptr<Fdm3dBlackScholesSolver> solver(
			new Fdm3dBlackScholesSolver(
				Handle<GeneralizedBlackScholesProcess>(p1_),
				Handle<GeneralizedBlackScholesProcess>(p2_),
				Handle<GeneralizedBlackScholesProcess>(p3_),
				correlation_, solverDesc, schemeDesc_));

		const Real x = p1_->x0();
		const Real y = p2_->x0();
		const Real z = p3_->x0();

		results_.value = solver->valueAt(x, y, z);
		results_.theta = solver->thetaAt(x, y, z);
	}
}
