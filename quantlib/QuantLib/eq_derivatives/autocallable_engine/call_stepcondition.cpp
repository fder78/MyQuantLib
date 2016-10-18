
#include <ql/methods/finitedifferences/operators/fdmlinearoplayout.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <eq_derivatives\autocallable_engine\call_stepcondition.h>

namespace QuantLib {

	FdmCallStepCondition::FdmCallStepCondition(
		const Date& exerciseDates,
		const Date& referenceDate,
		const DayCounter& dayCounter,
		const boost::shared_ptr<FdmMesher> & mesher,
		const boost::shared_ptr<FdmInnerValueCalculator> & calculator,
		const boost::shared_ptr<AutocallCondition> & condition)
		: mesher_(mesher), condition_(condition), calculator_(calculator) {
		exerciseTimes_.reserve(1);
		exerciseTimes_.push_back(dayCounter.yearFraction(referenceDate, exerciseDates));
	}

	const std::vector<Time>& FdmCallStepCondition::exerciseTimes() const {
		return exerciseTimes_;
	}

	void FdmCallStepCondition::applyTo(Array& a, Time t) const {
		if (std::find(exerciseTimes_.begin(), exerciseTimes_.end(), t) != exerciseTimes_.end()) {

			boost::shared_ptr<FdmLinearOpLayout> layout = mesher_->layout();
			const FdmLinearOpIterator endIter = layout->end();

			const Size dims = layout->dim().size();
			Array locations(dims);
			for (FdmLinearOpIterator iter = layout->begin(); iter != endIter; ++iter) {
				for (Size i = 0; i < dims; ++i)
					locations[i] = std::exp(mesher_->location(iter, i));
				Real innerValue = calculator_->innerValue(iter, t);
				if ((*condition_)(locations)) {
					a[iter.index()] = innerValue;
					continue;
				}
				if (innerValue > a[iter.index()])
					a[iter.index()] = innerValue;
			}
		}
	}
}