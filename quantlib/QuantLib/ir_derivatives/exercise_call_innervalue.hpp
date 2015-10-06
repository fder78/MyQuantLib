
#pragma once

#include <ql/experimental/coupons/swapspreadindex.hpp>
#include <ql/instruments/floatfloatswap.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>
#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <ql/methods/finitedifferences/utilities/fdmaffinemodeltermstructure.hpp>
#include <ql/cashflows/coupon.hpp>

#include <map>

namespace QuantLib {

    class FdmExerciseCallInnerValue : public FdmInnerValueCalculator {
      public:
		  FdmExerciseCallInnerValue(const Real& callValue) 
			  : callValue_(callValue) {}

		  Real innerValue(const FdmLinearOpIterator& iter, Time t) {
			  return callValue_;
		  }

		  Real avgInnerValue(const FdmLinearOpIterator& iter, Time t) {
			  return callValue_;
		  }

      private:
		const Real callValue_;
    };

}
