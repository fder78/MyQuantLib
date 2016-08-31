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

/*! \file Fd3dBlackScholesVanillaEngine.hpp
    \brief Finite-Differences 3 dim Black Scholes vanilla option engine
*/

#pragma once

#include <ql/pricingengine.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>

namespace QuantLib {

    //! Two dimensional finite-differences Black Scholes vanilla option engine

    /*! \ingroup basketengines

        \test the correctness of the returned value is tested by
              reproducing results available in web/literature
              and comparison with Kirk approximation.
    */
    class Fd3dBlackScholesVanillaEngine : public BasketOption::engine {
      public:
          Fd3dBlackScholesVanillaEngine(
                const boost::shared_ptr<GeneralizedBlackScholesProcess>& p1,
                const boost::shared_ptr<GeneralizedBlackScholesProcess>& p2,
			  const boost::shared_ptr<GeneralizedBlackScholesProcess>& p3,
                Matrix corrMatrix,
                std::vector<Size> grid, Size tGrid = 50, Size dampingSteps = 0,
                const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

        void calculate() const;

      private:
        const boost::shared_ptr<GeneralizedBlackScholesProcess> p1_;
        const boost::shared_ptr<GeneralizedBlackScholesProcess> p2_;
		const boost::shared_ptr<GeneralizedBlackScholesProcess> p3_;
        const Matrix correlation_;
        const Size xGrid_, yGrid_, zGrid_, tGrid_;
        const Size dampingSteps_;
        const FdmSchemeDesc schemeDesc_;
    };
}
