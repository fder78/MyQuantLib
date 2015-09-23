
#pragma once

#include <ql/quantlib.hpp>

namespace QuantLib {
	struct HWParams {
		HWParams(Real a, Real sigma) : a(a), sigma(sigma) {}
		Real a;
		Real sigma;
	};

	struct YieldCurveParams {
		YieldCurveParams(boost::shared_ptr<YieldTermStructure> yts, Real a, Real sigma) 
			: yts(yts), hwParams(a, sigma) {}
		boost::shared_ptr<YieldTermStructure> yts;
		HWParams hwParams;
	};

	struct GBMParams {
		GBMParams(Real s, 
			boost::shared_ptr<YieldTermStructure> div,
			boost::shared_ptr<YieldTermStructure> rf,
			boost::shared_ptr<BlackVolTermStructure> vol,
			Real fxVol = 0.0,
			Real fxCorr = 0.0)
			: s(s), div(div), rf(rf), vol(vol), fxVol(fxVol), fxCorr(fxCorr) {}
		Real s;
		boost::shared_ptr<YieldTermStructure> div;
		boost::shared_ptr<YieldTermStructure> rf;
		boost::shared_ptr<BlackVolTermStructure> vol;
		Real fxVol;
		Real fxCorr;
	};

	struct HullWhiteTimeDependentParameters;

	std::vector<Real> dual_rangeaccrual_fdm(Date evaluationDate,
		Real notional,
		std::vector<Rate> couponRate,
		std::vector<Real> gearing,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound1,
		std::vector<Real> upperBound1,
		std::vector<Real> lowerBound2,
		std::vector<Real> upperBound2,
		Date firstCallDate,
		Real pastAccrual,
		boost::shared_ptr<YieldTermStructure> obs1Curve,
		const HullWhiteTimeDependentParameters& obs1GenHWParams,
		Real obs1FXVol, Real obs1FXCorr,
		boost::shared_ptr<YieldTermStructure> obs2Curve,
		const HullWhiteTimeDependentParameters& obs2GenHWParams,
		Real obs2FXVol, Real obs2FXCorr,
		Handle<YieldTermStructure>& discTS,
		Real rho, Size tGrid, Size rGrid,
		Real invAlpha = Null<Real>(),
		Real invGearing = Null<Real>(),
		Real invFixing = Null<Real>(),
		Real cap = Null<Real>(),
		Real floor = Null<Real>(),
		Real alpha = Null<Real>(),
		Real pastFixing = Null<Real>(),
		std::vector<Matrix> coeff = std::vector<Matrix>(1,Matrix()),
		std::vector<Matrix> tenor = std::vector<Matrix>(1,Matrix()));


	std::vector<Real> dual_rangeaccrual(Date evaluationDate,
		Real notional,
		Rate couponRate,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Date firstCallDate,
		Real pastAccrual,
		boost::shared_ptr<StochasticProcess1D> obs1Process,
		boost::shared_ptr<StochasticProcess1D> obs2Process,
		boost::shared_ptr<HullWhiteProcess> discProcess,
		Real rho12,
		Real rho1disc,
		Real rho2disc,
		Size numSimulation,
		Size numCalibration);

	std::vector<Real> dual_rangeaccrual(Date evaluationDate,
		Real notional,
		Rate couponRate,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Date firstCallDate,
		Real pastAccrual,
		YieldCurveParams obs1,
		GBMParams obs2,
		YieldCurveParams disc,
		Real rho12,
		Real rho1disc,
		Real rho2disc,
		Size numSimulation,
		Size numCalibration);

	std::vector<Real> dual_rangeaccrual_minusCMS(Date evaluationDate,
		Real notional,
		Rate couponRate,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Date firstCallDate,
		Real pastAccrual,
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