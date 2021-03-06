
#pragma once
#include <ql/quantlib.hpp>
#include <ir_derivatives/g2_calibration.hpp>

namespace QuantLib {

	std::vector<Real> cms_spread_rangeaccrual_fdm(Date evaluationDate,
		VanillaSwap::Type type,
		Real notional,
		std::vector<Rate> couponRate,
		std::vector<Real> gearing,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Size> tenorsInYears,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Date firstCallDate,
		Real pastAccrual,
		boost::shared_ptr<YieldTermStructure> obs1Curve,
		const G2Parameters& obs1G2Params,
		Real obs1FXVol, Real obs1FXCorr,
		Handle<YieldTermStructure>& discTS,
		Size rGrid, Size tGrid,
		Schedule floatingSchedule,
		Real alpha,
		Real pastFixing);



}