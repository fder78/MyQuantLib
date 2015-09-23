
#pragma once
#include <ql/quantlib.hpp>

#include <ds_interestrate_derivatives/instruments/swaps/power_spread_swap.hpp>

namespace QuantLib {
	struct YieldCurveParams;
	std::vector<Real> power_spread_swap(Date evaluationDate,
		Real notional,
		PowerSpreadSwap::Side side,
		Rate alpha,
		Schedule floatingSchedule,
		Schedule fixedSchedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> gearing,
		std::vector<Real> spread,
		std::vector<Real> caps,
		std::vector<Real> floors,
		bool isAvg,
		Date firstCallDate,
		Real pastFixing,
		Rate floatingFixingRate,
		Real floatingGearing,
		DayCounter floatingDayCounter,
		boost::shared_ptr<StochasticProcess1D> obs1Process,
		boost::shared_ptr<StochasticProcess1D> obs2Process,
		boost::shared_ptr<HullWhiteProcess> discProcess,
		Real rho12,
		Real rho1disc,
		Real rho2disc,
		Size numSimulation,
		Size numCalibration);

}
