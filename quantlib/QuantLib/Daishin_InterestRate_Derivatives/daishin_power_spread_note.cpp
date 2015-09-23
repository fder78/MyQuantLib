#include "StdAfx.h"

#include "daishin_power_spread_note.hpp"
#include <ds_interestrate_derivatives/instruments/notes/power_spread_note.hpp>
#include <ds_interestrate_derivatives/pricingengine/mc_powerspread_note_lsmc_engine.hpp>

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
		Size numCalibration) {

			Date todaysDate = evaluationDate;
			Settings::instance().evaluationDate() = todaysDate;

			boost::shared_ptr<IborIndex> index1(new Euribor3M(Handle<YieldTermStructure>( discProcess->yieldTermStructure() )));
			boost::shared_ptr<SpreadIndex> index(new SpreadIndex(index1, index1));

			boost::shared_ptr<Callability> callability(new 
				Callability(Callability::Price(notional, Callability::Price::Clean), Callability::Call, firstCallDate));
			CallabilitySchedule callSchedule;
			callSchedule.push_back(callability);

			/***********************************************************************************/


			PowerSpreadNote testProduct(0, notional, schedule, index, dayCounter, bdc, Null<Natural>(), 
				gearing, spread, caps, floors, isAvg, 100.0, Date(), 
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

			boost::shared_ptr<PricingEngine> engine_lsmc(new MC_PowerSpread_Engine_LSMC<>(processes,
				0.0, //pastAccrual
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

}