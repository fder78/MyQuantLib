
#pragma once

#include <ql/quantlib.hpp>

namespace QuantLib {

	std::vector<Real> cap_floor(Date evaluationDate,
		CapFloor::Type type,
		Real strike,
		Real nominal,
		Schedule schedule,
		Natural fixingDays,
		BusinessDayConvention convention,
		boost::shared_ptr<IborIndex> index,
		boost::shared_ptr<YieldTermStructure> termStructure,
		Volatility volatility);

	Real swaption(Date evaluationDate,
		VanillaSwap::Type type,
		Settlement::Type settlementType,
		Real strike,
		Real nominal,
		Date exerciseDate,
		Schedule fixedSchedule,
		DayCounter fixedDayCount,
		Schedule floatSchedule,
		DayCounter floatDayCount,
		Natural fixingDays,
		BusinessDayConvention convention,
		boost::shared_ptr<IborIndex> index,
		boost::shared_ptr<YieldTermStructure> termStructure,
		Volatility volatility);
}