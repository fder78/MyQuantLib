
#pragma once

#include <ql/quantlib.hpp>

namespace QuantLib {

	std::vector<Real> interest_rate_swap(Date evaluationDate,
		VanillaSwap::Type type,
		Real nominal,
		Schedule fixedSchedule,
		Rate fixedRate,
		DayCounter fixedDayCount,
		Schedule floatSchedule,
		boost::shared_ptr<IborIndex> iborIndex,
		Spread spread,
		DayCounter floatingDayCount,
		boost::shared_ptr<YieldTermStructure> termStructure);

	std::vector<Real> cross_currency_swap(Date evaluationDate,
		VanillaSwap::Type type,
		Real nominal_krw,
		Real nominal_frn,
		Schedule fixedSchedule,
		Rate fixedRate,
		DayCounter fixedDayCount,
		Schedule floatSchedule,
		boost::shared_ptr<IborIndex> iborIndex,
		Spread spread,
		DayCounter floatingDayCount,
		Real spotFX,
		boost::shared_ptr<YieldTermStructure> krw_termStructure,
		boost::shared_ptr<YieldTermStructure> frn_termStructure);

}