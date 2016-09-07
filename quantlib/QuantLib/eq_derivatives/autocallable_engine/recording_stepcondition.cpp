
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <eq_derivatives/autocallable_engine/recording_stepcondition.h>

namespace QuantLib {

	FdmRecordingStepCondition::FdmRecordingStepCondition(
		const boost::shared_ptr<FdmMesher> & mesher)
		: mesher_(mesher){}

	const std::map<Time, Array>& FdmRecordingStepCondition::getValues() const {
		return values_;
	}

	void FdmRecordingStepCondition::applyTo(Array& a, Time t) const {
		values_.insert(std::pair<Time,Array>(t, a));
	}

	FdmWritingStepCondition::FdmWritingStepCondition(const boost::shared_ptr<FdmMesher>& mesher,
		const std::map<Time, Array>& values,
		const boost::shared_ptr<AutocallCondition>& condition)
		: mesher_(mesher), values_(values), condition_(condition) {}

	void FdmWritingStepCondition::applyTo(Array& a, Time t) const {
		const Array temp = (values_.find(t))->second;
		boost::shared_ptr<FdmLinearOpLayout> layout = mesher_->layout();
		const Size dims = layout->dim().size();
		Array locations(dims);
		for (FdmLinearOpIterator iter = layout->begin(); iter != layout->end(); ++iter) {
			for (Size i = 0; i < dims; ++i)
				locations[i] = mesher_->location(iter, i);
			if ((*condition_)(locations))
				a[iter.index()] = temp[iter.index()];
		}
	}

}
