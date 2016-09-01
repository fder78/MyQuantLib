
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <eq_derivatives\autocallable_engine\autocall_stepcondition.h>

namespace QuantLib {

	FdmAutocallStepCondition::FdmAutocallStepCondition(
		const std::vector<Date>& exerciseDates,
		const Date& referenceDate,
		const DayCounter& dayCounter,
		const boost::shared_ptr<FdmMesher> & mesher,
		const boost::shared_ptr<FdmInnerValueCalculator> & calculator,
		const boost::shared_ptr<AutocallCondition> & condition)
		: mesher_(mesher), condition_(condition), calculator_(calculator) {
		exerciseTimes_.reserve(exerciseDates.size());
		for (std::vector<Date>::const_iterator iter = exerciseDates.begin();
		iter != exerciseDates.end(); ++iter) {
			exerciseTimes_.push_back(
				dayCounter.yearFraction(referenceDate, *iter));
		}
	}

	const std::vector<Time>& FdmAutocallStepCondition::exerciseTimes() const {
		return exerciseTimes_;
	}

	void FdmAutocallStepCondition::applyTo(Array& a, Time t) const {
		if (std::find(exerciseTimes_.begin(), exerciseTimes_.end(), t) != exerciseTimes_.end()) {

			boost::shared_ptr<FdmLinearOpLayout> layout = mesher_->layout();
			const FdmLinearOpIterator endIter = layout->end();

			const Size dims = layout->dim().size();
			Array locations(dims);
			for (FdmLinearOpIterator iter = layout->begin(); iter != endIter; ++iter) {
				for (Size i = 0; i < dims; ++i)
					locations[i] = mesher_->location(iter, i);				
				if ((*condition_)(locations)) {
					Real innerValue = calculator_->innerValue(iter, t);
					a[iter.index()] = innerValue;
				}
			}

		}
	}
}