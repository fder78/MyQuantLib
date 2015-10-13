
#pragma once

#include <ql/instruments/floatfloatswaption.hpp>
#include <ql/pricingengines/genericmodelengine.hpp>
#include <ql/models/shortrate/twofactormodels/g2.hpp>
#include <ql/methods/finitedifferences/solvers/fdmbackwardsolver.hpp>

namespace QuantLib {

    class FdG2CmsSpreadRAEngine
        : public GenericModelEngine<G2, FloatFloatSwaption::arguments, FloatFloatSwaption::results> {
      public:
        FdG2CmsSpreadRAEngine(
            const boost::shared_ptr<G2>& model,
			const Real pastAccrual,
			const Real pastFixing,
            Size tGrid = 100, Size xGrid = 50, Size yGrid = 50,
            Size dampingSteps = 0, Real invEps = 1e-5,
            const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

        void calculate() const;

      private:
		  const Size tGrid_, xGrid_, yGrid_, dampingSteps_;
		  const Real pastAccrual_, pastFixing_;
		  const Real invEps_;
		  const FdmSchemeDesc schemeDesc_;
    };
}

