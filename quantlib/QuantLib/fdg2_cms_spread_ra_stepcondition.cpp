
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include "fdg2_cms_spread_ra_stepcondition.h"

namespace QuantLib {

	FdmRAStepCondition::FdmRAStepCondition(
		const std::vector<Time>& accrualTimes,
		const boost::shared_ptr<FdmMesher> & mesher,
		const boost::shared_ptr<FdmInnerValueCalculator> & calculator)
		: mesher_(mesher),
		calculator_(calculator),
		accrualTimes_(accrualTimes) {}
	
	const std::vector<Time>& FdmRAStepCondition::accrualTimes() const {
		return accrualTimes_;
	}

	void FdmRAStepCondition::applyTo(Array& a, Time t) const {
		if (std::find(accrualTimes_.begin(), accrualTimes_.end(), t) != accrualTimes_.end()) {			
			boost::shared_ptr<FdmLinearOpLayout> layout = mesher_->layout();
			const FdmLinearOpIterator endIter = layout->end();
			for (FdmLinearOpIterator iter = layout->begin(); iter != endIter; ++iter) {
				a[iter.index()] += calculator_->innerValue(iter, t);
			}
		}
	}
}
