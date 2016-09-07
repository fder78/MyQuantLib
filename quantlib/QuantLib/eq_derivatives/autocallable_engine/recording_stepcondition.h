#pragma once

#include <ql/methods/finitedifferences/stepcondition.hpp>
#include <ql/methods/finitedifferences/meshers/fdmmesher.hpp>
#include <ql/methods/finitedifferences/utilities/fdminnervaluecalculator.hpp>
#include <eq_derivatives/autocallable_engine/autocall_condition.h>

namespace QuantLib {

	class FdmRecordingStepCondition : public StepCondition<Array> {
	public:
		FdmRecordingStepCondition(const boost::shared_ptr<FdmMesher> & mesher);
		void applyTo(Array& a, Time) const;
		const std::map<Time, Array>& getValues() const;
	private:
		const boost::shared_ptr<FdmMesher> mesher_;
		mutable std::map<Time, Array> values_;
	};

	class FdmWritingStepCondition : public StepCondition<Array> {
	public:
		FdmWritingStepCondition(
			const boost::shared_ptr<FdmMesher>& mesher,
			const std::map<Time, Array>& values,
			const boost::shared_ptr<AutocallCondition>& condition);
		
		void applyTo(Array& a, Time t) const;

	private:
		const boost::shared_ptr<FdmMesher> mesher_;
		const std::map<Time, Array> values_;
		const boost::shared_ptr<AutocallCondition> condition_;
	};

}

