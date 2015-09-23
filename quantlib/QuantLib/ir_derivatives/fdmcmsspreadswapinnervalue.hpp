
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

    template <class ModelType>
    class FdmCmsSpreadSwapInnerValue : public FdmInnerValueCalculator {
      public:
        FdmCmsSpreadSwapInnerValue(
            const boost::shared_ptr<ModelType>& disModel,
            const boost::shared_ptr<ModelType>& fwdModel,
            const boost::shared_ptr<FloatFloatSwap>& swap,
            const std::map<Time, Date>& exerciseDates,
            const boost::shared_ptr<FdmMesher>& mesher,
            Size direction);

        Real innerValue(const FdmLinearOpIterator& iter, Time t);
        Real avgInnerValue(const FdmLinearOpIterator& iter, Time t);

      private:
        Disposable<Array> getState(
            const boost::shared_ptr<ModelType>& model,
            Time t,
            const FdmLinearOpIterator& iter) const;

        RelinkableHandle<YieldTermStructure> disTs_, fwdTs_;
        const boost::shared_ptr<ModelType> disModel_, fwdModel_;

        const boost::shared_ptr<SwapSpreadIndex> index_;
        const boost::shared_ptr<FloatFloatSwap> swap_;
        const std::map<Time, Date> exerciseDates_;
        const boost::shared_ptr<FdmMesher> mesher_;
        const Size direction_;
    };

    template <class ModelType> inline
    FdmCmsSpreadSwapInnerValue<ModelType>::FdmCmsSpreadSwapInnerValue(
        const boost::shared_ptr<ModelType>& disModel,
        const boost::shared_ptr<ModelType>& fwdModel,
        const boost::shared_ptr<FloatFloatSwap>& swap,
        const std::map<Time, Date>& exerciseDates,
        const boost::shared_ptr<FdmMesher>& mesher,
        Size direction)
    : disModel_(disModel),
      fwdModel_(fwdModel),
	  index_(boost::dynamic_pointer_cast<SwapSpreadIndex>(swap->index1())),
      swap_(swap),
      exerciseDates_(exerciseDates),
      mesher_(mesher),
      direction_(direction) {
    }

    template <class ModelType> inline
    Real FdmCmsSpreadSwapInnerValue<ModelType>::innerValue(const FdmLinearOpIterator& iter, Time t) {

        const Date& iterExerciseDate = exerciseDates_.find(t)->second;

        const Array disRate(getState(disModel_, t, iter));
        const Array fwdRate(getState(fwdModel_, t, iter));

        if (disTs_.empty() || iterExerciseDate != disTs_->referenceDate()) {
            const Handle<YieldTermStructure> discount = disModel_->termStructure();
            disTs_.linkTo(boost::shared_ptr<YieldTermStructure>(
                new FdmAffineModelTermStructure(disRate, discount->calendar(), discount->dayCounter(), iterExerciseDate, discount->referenceDate(), disModel_)));

            const Handle<YieldTermStructure> fwd = fwdModel_->termStructure();
			fwdTs_.linkTo(boost::shared_ptr<YieldTermStructure>(
				new FdmAffineModelTermStructure(fwdRate, fwd->calendar(), fwd->dayCounter(), iterExerciseDate, fwd->referenceDate(), fwdModel_)));
        }
        else {
            boost::dynamic_pointer_cast<FdmAffineModelTermStructure>(disTs_.currentLink())->setVariable(disRate);
            boost::dynamic_pointer_cast<FdmAffineModelTermStructure>(fwdTs_.currentLink())->setVariable(fwdRate);
        }

        Real npv = 0.0;
        for (Size j = 0; j < 2; j++) {
            for (Leg::const_iterator i = swap_->leg(j).begin(); i != swap_->leg(j).end(); ++i) {
				Date as = boost::dynamic_pointer_cast<Coupon>(*i)->accrualStartDate();
				Real temp = 0.0;
				if (as >= iterExerciseDate)
					temp = (*i)->amount() * disTs_->discount((*i)->date());
				npv += temp;
            }
            if (j == 0)
				npv *= -1.0;
        }
        if (swap_->type() == VanillaSwap::Receiver)
            npv *= -1.0;

        return std::max(0.0, npv);
    }

    template <class ModelType> inline
    Real FdmCmsSpreadSwapInnerValue<ModelType>::avgInnerValue(const FdmLinearOpIterator& iter, Time t) {
        return innerValue(iter, t);
    }

}
