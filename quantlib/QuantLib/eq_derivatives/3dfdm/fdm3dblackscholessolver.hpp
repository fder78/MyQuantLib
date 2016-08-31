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

/*! \file fdmhestonhullwhitesolver.hpp
*/

#pragma once

#include <ql/handle.hpp>
#include <ql/patterns/lazyobject.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/solvers/fdmsolverdesc.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>
#include <ql/methods/finitedifferences/utilities/fdmdirichletboundary.hpp>


namespace QuantLib {

	class Fdm3DimSolver;

	class Fdm3dBlackScholesSolver : public LazyObject {
	public:
		Fdm3dBlackScholesSolver(
			const Handle<GeneralizedBlackScholesProcess>& p1,
			const Handle<GeneralizedBlackScholesProcess>& p2,
			const Handle<GeneralizedBlackScholesProcess>& p3,
			const Matrix corr,
			const FdmSolverDesc& solverDesc,
			const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

		Real valueAt(Real s1, Real s2, Real s3) const;
		Real thetaAt(Real s1, Real s2, Real s3) const;

		// First and second order derivative with respect to S_t. 
		// Please note that this is not the "model implied" delta or gamma.
		// E.g. see Fabio Mercurio, Massimo Morini 
		// "A Note on Hedging with Local and Stochastic Volatility Models",
		// http://papers.ssrn.com/sol3/papers.cfm?abstract_id=1294284  
		Real deltaAt(Real s1, Real s2, Real s3, Real eps) const;
		Real gammaAt(Real s1, Real s2, Real s3, Real eps) const;

	protected:
		void performCalculations() const;

	private:
		const Handle<GeneralizedBlackScholesProcess> p1_, p2_, p3_;
		const Matrix corr_;

		const FdmSolverDesc solverDesc_;
		const FdmSchemeDesc schemeDesc_;

		mutable boost::shared_ptr<Fdm3DimSolver> solver_;
	};
}

