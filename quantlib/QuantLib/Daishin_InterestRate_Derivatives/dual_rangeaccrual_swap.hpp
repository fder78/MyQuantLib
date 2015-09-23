#pragma once

// #include <ql/quantlib.hpp>
#include "dual_rangeaccrual.hpp"
#include <ds_interestrate_derivatives/instruments/swaps/range_accrual_swap.hpp>

namespace QuantLib {

	std::vector<Real> dual_rangeaccrual_swap(Date evaluationDate,
		Real notional,
		RangeAccrualSwap::Side side,
		Rate alpha,
		Schedule floatingSchedule,
		Rate couponRate,
		Schedule fixedSchedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Date firstCallDate,
		Real pastAccrual,
		Rate floatingFixingRate,
		boost::shared_ptr<StochasticProcess1D> obs1Process,
		boost::shared_ptr<StochasticProcess1D> obs2Process,
		boost::shared_ptr<HullWhiteProcess> discProcess,
		Real rho12,
		Real rho1disc,
		Real rho2disc,
		Size numSimulation,
		Size numCalibration);

	std::vector<Real> dual_rangeaccrual_swap(Date evaluationDate,
		Real notional,
		RangeAccrualSwap::Side side,
		Rate alpha,
		Schedule floatingSchedule,
		Rate couponRate,
		Schedule fixedSchedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Date firstCallDate,
		Real pastAccrual,
		Rate floatingFixingRate,
		YieldCurveParams obs1,
		GBMParams obs2,
		YieldCurveParams disc,
		Real rho12,
		Real rho1disc,
		Real rho2disc,
		Size numSimulation,
		Size numCalibration);

	std::vector<Real> dual_rangeaccrual_swap_minusCMS(Date evaluationDate,
		Real notional,
		RangeAccrualSwap::Side side,
		Rate alpha,
		Schedule floatingSchedule,
		Rate couponRate,
		Schedule fixedSchedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Date firstCallDate,
		Real pastAccrual,
		Rate floatingFixingRate,
		Rate fixingCMS,
		boost::shared_ptr<StochasticProcess1D> obs1Process,
		boost::shared_ptr<StochasticProcess1D> obs2Process,
		boost::shared_ptr<HullWhiteProcess> discProcess,
		Real rho12,
		Real rho1disc,
		Real rho2disc,
		Size numSimulation,
		Size numCalibration);


}