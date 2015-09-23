#include "dual_rangeaccrual.hpp"

#include <ds_interestrate_derivatives/instruments/notes/range_accrual_note.hpp>
#include <ds_interestrate_derivatives/pricingengine/mc_rangeaccrual_note_lsmc_engine.hpp>
#include <ds_interestrate_derivatives/pricingengine/fdm_engine/fdm_ra_engine_ghw.hpp>

#include <ds_interestrate_derivatives/hw_calibration/hull_white_calibration.hpp>

namespace QuantLib {


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
		Real invAlpha,
		Real invGearing,
		Real invFixing,
		Real cap,
		Real floor,
		Real alpha,
		Real pastFixing,
		std::vector<Matrix> coeff,
		std::vector<Matrix> tenor) {

			Date todaysDate = evaluationDate;
			Settings::instance().evaluationDate() = todaysDate;

			boost::shared_ptr<IborIndex> index(new Euribor3M(Handle<YieldTermStructure>( discTS )));
			std::vector<Real> gearingVec(gearing);
			std::vector<Real> spread(couponRate);
			std::vector<Real> lowerTrigger1(lowerBound1);
			std::vector<Real> upperTrigger1(upperBound1);
			std::vector<Real> lowerTrigger2(lowerBound2);
			std::vector<Real> upperTrigger2(upperBound2);

			//if( lowerBound2.size() > 0 )
			//{
			//	lowerTrigger2.push_back( lowerBound[ 1 ] );
			//}

			//if( upperBound2.size() > 0 )
			//{
			//	upperTrigger2.push_back( upperBound[ 1 ] );
			//}
			Period obsTenor(Daily);

			Real callValue = ( alpha == Null<Real>() ) ? notional : 0.;
			boost::shared_ptr<Callability> callability(new 
				Callability(Callability::Price(callValue, Callability::Price::Clean), Callability::Call, firstCallDate));
			CallabilitySchedule callSchedule;
			callSchedule.push_back(callability);

			//boost::shared_ptr<StochasticProcess1D> discProcess(new 
			//	HullWhiteProcess(Handle<YieldTermStructure>(disc.yts), disc.hwParams.a, disc.hwParams.sigma));
			/***********************************************************************************/

			RangeAccrualNote testProduct(0, notional, schedule, index, index, index, dayCounter, bdc, Null<Natural>(), 
				gearingVec, spread, lowerTrigger1, upperTrigger1, lowerTrigger2, upperTrigger2, obsTenor, Unadjusted, 100.0, Date(), 
				callSchedule, Exercise::Bermudan, alpha, pastFixing, coeff, tenor);

			if (invGearing!=Null<Real>() && invAlpha!=Null<Real>()) {
				testProduct.setInverseFloater(invAlpha, invGearing, cap, floor, invFixing);
			}

			boost::shared_ptr<Generalized_HullWhite> obs1Model(new 
				Generalized_HullWhite(Handle<YieldTermStructure>( obs1Curve ), obs1GenHWParams.tenor, obs1GenHWParams.sigma, obs1GenHWParams.a, obs1FXVol, obs1FXCorr ) );

			boost::shared_ptr<Generalized_HullWhite> obs2Model(new 
				Generalized_HullWhite(Handle<YieldTermStructure>( obs2Curve ), obs2GenHWParams.tenor, obs2GenHWParams.sigma, obs2GenHWParams.a, obs2FXVol, obs2FXCorr ) );

			/*****Pricing Engine*****/
			boost::shared_ptr<PricingEngine> engine(new Fdm_R2_Dual_RA_Engine( obs1Model, obs2Model, Handle<YieldTermStructure>( discTS ), rho, pastAccrual, tGrid, rGrid, rGrid ) );
			testProduct.setPricingEngine(engine);

			std::vector<Real> rst;
			rst.push_back(testProduct.NPV());
			return rst;
	}


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
		Size numCalibration) {

			Date todaysDate = evaluationDate;
			Settings::instance().evaluationDate() = todaysDate;

			boost::shared_ptr<IborIndex> index(new Euribor3M(Handle<YieldTermStructure>( discProcess->yieldTermStructure() )));
			std::vector<Real> gearing(1, QL_MIN_POSITIVE_REAL);
			std::vector<Real> spread(1, couponRate);
			std::vector<Real> lowerTrigger1(1, lowerBound[0]);
			std::vector<Real> upperTrigger1(1, upperBound[0]);
			std::vector<Real> lowerTrigger2(1, lowerBound[1]);
			std::vector<Real> upperTrigger2(1, upperBound[1]);
			Period obsTenor(Daily);

			boost::shared_ptr<Callability> callability(new 
				Callability(Callability::Price(notional, Callability::Price::Clean), Callability::Call, firstCallDate));
			CallabilitySchedule callSchedule;
			callSchedule.push_back(callability);

			/***********************************************************************************/


			RangeAccrualNote testProduct(0, notional, schedule, index, index, index, dayCounter, bdc, Null<Natural>(), 
				gearing, spread, lowerTrigger1, upperTrigger1, lowerTrigger2, upperTrigger2, obsTenor, Unadjusted, 100.0, Date(), 
				callSchedule, Exercise::Bermudan);


			/*****Pricing Engine*****/
			std::vector<boost::shared_ptr<StochasticProcess1D> > pros;
			pros.push_back(discProcess);
			pros.push_back(obs1Process);
			pros.push_back(obs2Process);
			Matrix corr(3,3,1.0);
			corr[0][1] = corr[1][0] = rho1disc;
			corr[0][2] = corr[2][0] = rho2disc;
			corr[1][2] = corr[2][1] = rho12;

			boost::shared_ptr<StochasticProcessArray> processes(new StochasticProcessArray(pros, corr));

			boost::shared_ptr<PricingEngine> engine_lsmc(new MC_RangeAccrual_Engine_LSMC<>(processes,
				pastAccrual, //pastAccrual
				256, //seed 
				numSimulation, //required samples
				numCalibration, //calibration samples
				true, //antithetic
				false,  //control variate
				false //brownian bridge
				));
			testProduct.setPricingEngine(engine_lsmc);

			std::vector<Real> rst;
			rst.push_back(testProduct.NPV());
			rst.push_back(testProduct.errorEstimate());
			return rst;
	}

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
		Size numCalibration) {

			Date todaysDate = evaluationDate;
			Settings::instance().evaluationDate() = todaysDate;

			boost::shared_ptr<IborIndex> index(new Euribor3M(Handle<YieldTermStructure>(disc.yts)));
			std::vector<Real> gearing(1, QL_MIN_POSITIVE_REAL);
			std::vector<Real> spread(1, couponRate);
			std::vector<Real> lowerTrigger1(1, lowerBound[0]);
			std::vector<Real> upperTrigger1(1, upperBound[0]);
			std::vector<Real> lowerTrigger2(1, lowerBound[1]);
			std::vector<Real> upperTrigger2(1, upperBound[1]);
			Period obsTenor(Daily);

			boost::shared_ptr<Callability> callability(new 
				Callability(Callability::Price(notional, Callability::Price::Clean), Callability::Call, firstCallDate));
			CallabilitySchedule callSchedule;
			callSchedule.push_back(callability);

			boost::shared_ptr<HullWhiteProcess> discProcess(new 
				HullWhiteProcess(Handle<YieldTermStructure>(disc.yts), disc.hwParams.a, disc.hwParams.sigma));
			boost::shared_ptr<HullWhiteProcess> obs1Process(new 
				HullWhiteProcess(Handle<YieldTermStructure>(obs1.yts), obs1.hwParams.a, obs1.hwParams.sigma));
			boost::shared_ptr<GeneralizedBlackScholesProcess> obs2Process(new 
				BSM_QuantoAdjusted_Process(Handle<Quote>(new SimpleQuote(obs2.s)), 
				Handle<YieldTermStructure>(obs2.div),
				Handle<YieldTermStructure>(obs2.rf),
				Handle<BlackVolTermStructure>(obs2.vol),
				obs2.fxVol, obs2.fxCorr));
			/***********************************************************************************/

			RangeAccrualNote testProduct(0, notional, schedule, index, index, index, dayCounter, bdc, Null<Natural>(), 
				gearing, spread, lowerTrigger1, upperTrigger1, lowerTrigger2, upperTrigger2, obsTenor, Unadjusted, 100.0, Date(), 
				callSchedule, Exercise::Bermudan);

			/*****Pricing Engine*****/
			std::vector<boost::shared_ptr<StochasticProcess1D> > pros;
			pros.push_back(discProcess);
			pros.push_back(obs1Process);
			pros.push_back(obs2Process);
			Matrix corr(3,3,1.0);
			corr[0][1] = corr[1][0] = rho1disc;
			corr[0][2] = corr[2][0] = rho2disc;
			corr[1][2] = corr[2][1] = rho12;

			boost::shared_ptr<StochasticProcessArray> processes(new StochasticProcessArray(pros, corr));

			boost::shared_ptr<PricingEngine> engine_lsmc(new MC_RangeAccrual_Engine_LSMC<>(processes,
				pastAccrual, //pastAccrual
				256, //seed 
				numSimulation, //required samples
				numCalibration, //calibration samples
				true, //antithetic
				false,  //control variate
				false //brownian bridge
				)); //product code
			testProduct.setPricingEngine(engine_lsmc);

			std::vector<Real> rst;
			rst.push_back(testProduct.NPV());
			rst.push_back(testProduct.errorEstimate());
			return rst;
	}

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
		Size numCalibration) {

			Date todaysDate = evaluationDate;
			Settings::instance().evaluationDate() = todaysDate;

			boost::shared_ptr<IborIndex> index(new Euribor3M(Handle<YieldTermStructure>(discProcess->yieldTermStructure())));
			std::vector<Real> gearing(1, QL_MIN_POSITIVE_REAL);
			std::vector<Real> spread(1, couponRate);
			std::vector<Real> lowerTrigger1(1, lowerBound[0]);
			std::vector<Real> upperTrigger1(1, upperBound[0]);
			std::vector<Real> lowerTrigger2(1, lowerBound[1]);
			std::vector<Real> upperTrigger2(1, upperBound[1]);
			Period obsTenor(Daily);

			boost::shared_ptr<Callability> callability(new 
				Callability(Callability::Price(notional, Callability::Price::Clean), Callability::Call, firstCallDate));
			CallabilitySchedule callSchedule;
			callSchedule.push_back(callability);

			/***********************************************************************************/

			RangeAccrualNote testProduct(0, notional, schedule, index, index, index, dayCounter, bdc, Null<Natural>(), 
				gearing, spread, lowerTrigger1, upperTrigger1, lowerTrigger2, upperTrigger2, obsTenor, Unadjusted, 100.0, Date(), 
				callSchedule, Exercise::Bermudan);

			/*****Pricing Engine*****/
			std::vector<boost::shared_ptr<StochasticProcess1D> > pros;
			pros.push_back(discProcess);
			pros.push_back(obs1Process);
			pros.push_back(obs2Process);
			Matrix corr(3,3,1.0);
			corr[0][1] = corr[1][0] = rho1disc;
			corr[0][2] = corr[2][0] = rho2disc;
			corr[1][2] = corr[2][1] = rho12;

			boost::shared_ptr<StochasticProcessArray> processes(new StochasticProcessArray(pros, corr));

			boost::shared_ptr<PricingEngine> engine_lsmc(new MC_RangeAccrual_Engine_LSMC<>(processes,
				pastAccrual, //pastAccrual
				256, //seed 
				numSimulation, //required samples
				numCalibration, //calibration samples
				true, //antithetic
				false,  //control variate
				false, //brownian bridge
				1, fixingCMS));
			testProduct.setPricingEngine(engine_lsmc);

			std::vector<Real> rst;
			rst.push_back(testProduct.NPV());
			rst.push_back(testProduct.errorEstimate());
			return rst;

	}



}