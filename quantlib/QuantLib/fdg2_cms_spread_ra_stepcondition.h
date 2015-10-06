#pragma once

#include <ql/time/daycounter.hpp>
#include <ql/methods/finitedifferences/stepcondition.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>

namespace QuantLib {

	class FdmInnerValueCalculator;

	class FdmRAStepCondition : public StepCondition<Array> {
	public:
		FdmRAStepCondition(
			const std::vector<Time> & accrualTimes,
			const boost::shared_ptr<FdmMesher> & mesher,
			const boost::shared_ptr<FdmInnerValueCalculator> & calculator);

		void applyTo(Array& a, Time t) const;
		const std::vector<Time>& accrualTimes() const;

	private:
		const std::vector<Time> accrualTimes_, timeInterval_;
		const boost::shared_ptr<FdmMesher> mesher_;
		const boost::shared_ptr<FdmInnerValueCalculator> calculator_;
	};
}

