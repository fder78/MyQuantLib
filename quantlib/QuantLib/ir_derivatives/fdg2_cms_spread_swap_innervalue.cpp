
#include "fdg2_cms_spread_swap_innervalue.hpp"

#include <ql/models/shortrate/twofactormodels/g2.hpp>
#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>


namespace QuantLib {

    template <>
    Disposable<Array> FdmCmsSpreadSwapInnerValue<HullWhite>::getState(
        const boost::shared_ptr<HullWhite>& model, Time t,
        const FdmLinearOpIterator& iter) const {

        Array retVal(1, model->dynamics()->shortRate(t,
                                    mesher_->location(iter, direction_)));
        return retVal;
    }

    template <>
    Disposable<Array> FdmCmsSpreadSwapInnerValue<G2>::getState(
        const boost::shared_ptr<G2>&, Time,
        const FdmLinearOpIterator& iter) const {

        Array retVal(2);
        retVal[0] = mesher_->location(iter, direction_);
        retVal[1] = mesher_->location(iter, direction_+1);

        return retVal;
    }

}
