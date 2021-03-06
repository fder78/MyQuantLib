
#pragma once

#include <ql/quantlib.hpp>
#include <ds_interestrate_derivatives/instruments/swaps/power_spread_swap.hpp>
#include "dual_rangeaccrual.hpp"

namespace QuantLib {

	std::vector<Real> power_spread_note(Date evaluationDate,
		Real notional,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> gearing,
		std::vector<Real> spread,
		std::vector<Real> caps,
		std::vector<Real> floors,
		bool isAvg,
		Date firstCallDate,
		Real pastFixing,
		boost::shared_ptr<StochasticProcess1D> obs1Process,
		boost::shared_ptr<StochasticProcess1D> obs2Process,
		boost::shared_ptr<HullWhiteProcess> discProcess,
		Real rho12,
		Real rho1disc,
		Real rho2disc,
		Size numSimulation,
		Size numCalibration);

}