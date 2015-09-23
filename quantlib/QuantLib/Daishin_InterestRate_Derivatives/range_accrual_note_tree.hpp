#pragma once

#include <ql/quantlib.hpp>
#include "dual_rangeaccrual.hpp"

namespace QuantLib {

	struct HullWhiteTimeDependentParameters;

	std::vector<Real> single_rangeaccrual(Date evaluationDate,
		Real notional,
		std::vector<Rate> couponRate,
		std::vector<Real> gearing,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Schedule callDates,
		std::vector<Real> callValues,
		Size pastAccrual,
		boost::shared_ptr<YieldTermStructure> refCurve,
		const HullWhiteTimeDependentParameters& geneHWparams,
		boost::shared_ptr<YieldTermStructure> discCurve,
		Size steps,
		Real invAlpha = Null<Real>(),
		Real invGearing = Null<Real>(),
		Real invFixing = Null<Real>(),
		Real cap = Null<Real>(),
		Real floor = Null<Real>(),
		Real alpha = Null<Real>(),
		Real pastFixing = Null<Real>()
		);
}
