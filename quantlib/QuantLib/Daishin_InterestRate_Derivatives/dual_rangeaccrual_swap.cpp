
#include "dual_rangeaccrual_swap.hpp"

#include <ds_interestrate_derivatives/pricingengine/mc_rangeaccrual_swap_lsmc_engine.hpp>


namespace QuantLib {

	std::vector<Real> dual_rangeaccrual_swap(Date evaluationDate,
		Real notional,
		RangeAccrualSwap::Side side,
		Rate alpha,
		Schedule floatingSchedule,
		Rate couponRate,
		Schedule schedule,
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


			RangeAccrualSwap testProduct(0, notional, side, floatingSchedule, alpha, schedule, index, index, index, dayCounter, bdc, Null<Natural>(), 
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

			boost::shared_ptr<PricingEngine> engine_lsmc(new MC_RangeAccrual_Swap_Engine_LSMC<>(processes,
				pastAccrual, //pastAccrual
				floatingFixingRate,
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

	std::vector<Real> dual_rangeaccrual_swap(Date evaluationDate,
		Real notional,
		RangeAccrualSwap::Side side,
		Rate alpha,
		Schedule floatingSchedule,
		Rate couponRate,
		Schedule schedule,
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

			RangeAccrualSwap testProduct(0, notional, side, floatingSchedule, alpha, schedule, index, index, index, dayCounter, bdc, Null<Natural>(), 
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

			boost::shared_ptr<PricingEngine> engine_lsmc(new MC_RangeAccrual_Swap_Engine_LSMC<>(processes,
				pastAccrual, //pastAccrual
				floatingFixingRate,
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

	std::vector<Real> dual_rangeaccrual_swap_minusCMS(Date evaluationDate,
		Real notional,
		RangeAccrualSwap::Side side,
		Rate alpha,
		Schedule floatingSchedule,
		Rate couponRate,
		Schedule schedule,
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

			RangeAccrualSwap testProduct(0, notional, side, floatingSchedule, alpha, schedule, index, index, index, dayCounter, bdc, Null<Natural>(), 
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

			boost::shared_ptr<PricingEngine> engine_lsmc(new MC_RangeAccrual_Swap_Engine_LSMC<>(processes,
				pastAccrual, //pastAccrual
				floatingFixingRate,
				256, //seed 
				numSimulation, //required samples
				numCalibration, //calibration samples
				true, //antithetic
				false,  //control variate
				false, //brownian bridge
				1,
				fixingCMS));
			testProduct.setPricingEngine(engine_lsmc);

			std::vector<Real> rst;
			rst.push_back(testProduct.NPV());
			rst.push_back(testProduct.errorEstimate());
			return rst;

	}



}