#pragma once

#include <ql/time/daycounter.hpp>
#include <ql/methods/finitedifferences/stepcondition.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <eq_derivatives\autocallable_engine\autocall_condition.h>

namespace QuantLib {

	class FdmInnerValueCalculator;

	class FdmCallStepCondition : public StepCondition<Array> {
	public:
		FdmCallStepCondition(
			const Date& exerciseDates,
			const Date& referenceDate,
			const DayCounter& dayCounter,
			const boost::shared_ptr<FdmMesher> & mesher,
			const boost::shared_ptr<FdmInnerValueCalculator> & calculator,
			const boost::shared_ptr<AutocallCondition> & condition);

		void applyTo(Array& a, Time t) const;
		const std::vector<Time>& exerciseTimes() const;

	private:
		std::vector<Time> exerciseTimes_;
		const boost::shared_ptr<FdmMesher> mesher_;
		const boost::shared_ptr<FdmInnerValueCalculator> calculator_;
		const boost::shared_ptr<AutocallCondition> condition_;
	};
}