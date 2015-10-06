
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
			const std::vector<Time> & accrualTimes,
			const std::map<Time, Time> & timeInterval,
			const std::map<Time, std::pair<Size,Time> > & cfIndex,
            const boost::shared_ptr<FdmMesher>& mesher,
            Size direction);

        Real innerValue(const FdmLinearOpIterator& iter, Time t);
        Real avgInnerValue(const FdmLinearOpIterator& iter, Time t);

      private:
        Disposable<Array> getState(
            const boost::shared_ptr<ModelType>& model,
            Time t,
            const FdmLinearOpIterator& iter) const;

		Rate fairSpread(Time, const Array& f) const;
		Real discount(Time, Time, const Array& f) const;

        RelinkableHandle<YieldTermStructure> disTs_, fwdTs_;
        const boost::shared_ptr<ModelType> disModel_, fwdModel_;
		const std::vector<Time> accrualTimes_;
		const std::map<Time, Time> timeInterval_;
		const std::map<Time, std::pair<Size, Time> > cfIndex_;
        const boost::shared_ptr<SwapSpreadIndex> index_;
        const boost::shared_ptr<FloatFloatSwap> swap_;
        const boost::shared_ptr<FdmMesher> mesher_;
        const Size direction_;
		std::vector<Size> length_, tenor_;
    };

    template <class ModelType> inline
    FdmCmsSpreadSwapInnerValue<ModelType>::FdmCmsSpreadSwapInnerValue(
        const boost::shared_ptr<ModelType>& disModel,
        const boost::shared_ptr<ModelType>& fwdModel,
        const boost::shared_ptr<FloatFloatSwap>& swap,
		const std::vector<Time> & accrualTimes,
		const std::map<Time, Time> & timeInterval,
		const std::map<Time, std::pair<Size, Time> > & cfIndex,
        const boost::shared_ptr<FdmMesher>& mesher,
        Size direction)
    : disModel_(disModel),
		fwdModel_(fwdModel),
		index_(boost::dynamic_pointer_cast<SwapSpreadIndex>(swap->index1())),
		swap_(swap), accrualTimes_(accrualTimes), timeInterval_(timeInterval), cfIndex_(cfIndex), 
		mesher_(mesher), tenor_(std::vector<Size>(2)), length_(std::vector<Size>(2)),
		direction_(direction) {
		tenor_[0] = index_->swapIndex1()->fixedLegTenor().frequency(); 
		tenor_[1] = index_->swapIndex2()->fixedLegTenor().frequency();
		length_[0] = (Size)years(index_->swapIndex1()->tenor()); 
		length_[1] = (Size)years(index_->swapIndex2()->tenor());
    }

	template <class ModelType>
	Rate FdmCmsSpreadSwapInnerValue<ModelType>::fairSpread(Time t, const Array& f) const {
		Real swapRate[2] = { 0, 0 };
		for (Size j = 0; j < 2; ++j) {
			for (Size i = 1; i <= length_[j]*tenor_[j]; ++i) {
				swapRate[j] += fwdModel_->discountBond(t, t + (double)i / tenor_[j], f) / tenor_[j];
			}
			swapRate[j] = (1.0 - fwdModel_->discountBond(t, t + (double)length_[j], f)) / swapRate[j];
		}		
		return swapRate[0] - swapRate[1];
	}
	template <class ModelType>
	Real FdmCmsSpreadSwapInnerValue<ModelType>::discount(Time now, Time t, const Array& f) const {
		return disModel_->discountBond(now, t, f);
	}
	
    template <class ModelType> inline
    Real FdmCmsSpreadSwapInnerValue<ModelType>::innerValue(const FdmLinearOpIterator& iter, Time t) {

        const Array disRate(getState(disModel_, t, iter));
        const Array fwdRate(getState(fwdModel_, t, iter));
		
		Rate sp = fairSpread(t, fwdRate);

				
		Leg leg1 = swap_->leg1();
		Size idx = (cfIndex_.find(t)->second).first;
		Real coupon = swap_->spread1()[idx];
		Real upperTrigger = swap_->cappedRate1()[idx];
		Real lowerTrigger = swap_->flooredRate1()[idx];
		bool flag = (sp <= upperTrigger && sp >= lowerTrigger) ? true : false;

		Real payTime = (cfIndex_.find(t)->second).second;
		Real df = discount(t, payTime, disRate);
		return flag * coupon * df * timeInterval_.find(t)->second;
    }

    template <class ModelType> inline
    Real FdmCmsSpreadSwapInnerValue<ModelType>::avgInnerValue(const FdmLinearOpIterator& iter, Time t) {
        return innerValue(iter, t);
    }

}
