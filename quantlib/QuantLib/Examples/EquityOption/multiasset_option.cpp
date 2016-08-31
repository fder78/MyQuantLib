
#include "utilities.hpp"
#include <iostream>
#include <fstream>
#include <ql/time/daycounters/actual360.hpp>

#include <ql/time/schedule.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/processes/stochasticprocessarray.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/utilities/dataformatters.hpp>

#include <eq_derivatives\mc_callable_index_ra_engine.hpp>
#include <eq_derivatives\callable_index_rangeaccrual.hpp>
#include <eq_derivatives\participation_payoff.hpp>

#include <boost/timer.hpp>

using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {

	Integer sessionId() { return 0; }

}
#endif

void testIndexRA() {

	//std::ofstream fout("E:\\Index_RA.csv");
	DayCounter dc = Actual365Fixed();
	Date today = Date::todaysDate();

	//////////////////////////////////////////
	//MARKET DATA
	//////////////////////////////////////////	
	Real s1 = 100, s2 = 100;
	Real r = 0.015;
	Real v1 = 0.25, v2 = 0.25;
	Real q1 = 0.02, q2 = 0.03;
	Real r1 = 0.0, r2 = 0.0;
	Real fxvol = 0.12, fxcorr = -0.8;
	Real corr = 0.60;
	//////////////////////////////////////////
	//PRODUCT SPEC
	//////////////////////////////////////////
	Real notional = 10000;
	std::vector<Real> basePrices(2, 100);
	Real barrier = 0.60;
	std::vector<std::pair<Real, Real> > rabounds(2, std::pair<Real, Real>(barrier, QL_MAX_REAL));
	Date startDate = today;
	Schedule couponDates(startDate, startDate + 5 * Years, Period(6, Months), NullCalendar(), ModifiedFollowing, ModifiedFollowing, DateGeneration::Backward, false);
	Schedule paymentDates(couponDates);
	//coupon payoff
	Real participation = 0.27, strike = 0.19;
	Size inRangeCount = 0;
	//////////////////////////////////////////
	//MC SETTINGS
	//////////////////////////////////////////
#ifdef _DEBUG
	Size requiredSamples = 50;
	Size calibrationSamples = 10;
#else
	Size requiredSamples = 3000;
	Size calibrationSamples = 512;
#endif
	Size timeSteps = 252;
	///////////////////////////////////////////
	//for (Size iter1 = 0; iter1 <= 3; ++iter1) {
	//	Real params1 = iter1*0.25;
	//	corr = params1;
		for (Size iter = 0; iter <= 5; ++iter) {
			//Real params = 120 - 5 * iter;
			//s1 = s2 = params;

			Real params = 0.25 + iter*0.01;
			v1 = v2 = params;
			
			boost::shared_ptr<SimpleQuote> spot1(new SimpleQuote(0.0));
			boost::shared_ptr<SimpleQuote> spot2(new SimpleQuote(0.0));

			boost::shared_ptr<SimpleQuote> qRate1(new SimpleQuote(0.0));
			boost::shared_ptr<YieldTermStructure> qTS1 = flatRate(today, qRate1, dc);
			boost::shared_ptr<SimpleQuote> qRate2(new SimpleQuote(0.0));
			boost::shared_ptr<YieldTermStructure> qTS2 = flatRate(today, qRate2, dc);

			boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.0));
			boost::shared_ptr<YieldTermStructure> rTS = flatRate(today, rRate, dc);

			boost::shared_ptr<SimpleQuote> vol1(new SimpleQuote(0.0));
			boost::shared_ptr<BlackVolTermStructure> volTS1 = flatVol(today, vol1, dc);
			boost::shared_ptr<SimpleQuote> vol2(new SimpleQuote(0.0));
			boost::shared_ptr<BlackVolTermStructure> volTS2 = flatVol(today, vol2, dc);


			spot1->setValue(s1);
			spot2->setValue(s2);
			rRate->setValue(r);
			vol1->setValue(v1);
			vol2->setValue(v2);
			qRate1->setValue(q1 + fxcorr*fxvol*v1 + r - r1);
			qRate2->setValue(q2 + fxcorr*fxvol*v2 + r - r2);

			boost::shared_ptr<YieldTermStructure> discTS = rTS;

			boost::shared_ptr<StochasticProcess1D> stochProcess1(new
				BlackScholesMertonProcess(Handle<Quote>(spot1),
					Handle<YieldTermStructure>(qTS1),
					Handle<YieldTermStructure>(rTS),
					Handle<BlackVolTermStructure>(volTS1)));

			boost::shared_ptr<StochasticProcess1D> stochProcess2(new
				BlackScholesMertonProcess(Handle<Quote>(spot2),
					Handle<YieldTermStructure>(qTS2),
					Handle<YieldTermStructure>(rTS),
					Handle<BlackVolTermStructure>(volTS2)));

			std::vector<boost::shared_ptr<StochasticProcess1D> > procs;
			procs.push_back(stochProcess1);
			procs.push_back(stochProcess2);

			Matrix correlation(2, 2, corr);
			correlation[0][0] = correlation[1][1] = 1.0;

			// FLOATING_POINT_EXCEPTION
			boost::shared_ptr<StochasticProcessArray> process(new StochasticProcessArray(procs, correlation));

			BigNatural seed = 1;
			boost::shared_ptr<PricingEngine> mcLSMCEngine =
				MakeMCCallableIndexRAEngine<>(process, discTS)
				.withStepsPerYear(timeSteps)
				.withAntitheticVariate()
				.withSamples(requiredSamples)
				.withCalibrationSamples(calibrationSamples)
				.withSeed(seed);

			boost::shared_ptr<Payoff> payoff(new ParticipationPayoff(participation, strike, couponDates.tenor()));
			boost::shared_ptr<Exercise> bmExercise(new BermudanExercise(couponDates.dates()));
			CallableIndexRangeAccrual amBasketOption(
				notional,
				basePrices,
				rabounds,
				couponDates,
				paymentDates,
				payoff,
				bmExercise,
				inRangeCount);
			amBasketOption.setPricingEngine(mcLSMCEngine);

			Real calculated = amBasketOption.NPV();
			Real errorEstimate = amBasketOption.errorEstimate();
			std::cout << "Price = " << calculated << "     SE = " << errorEstimate << std::endl;
			//fout.precision(20);
			//fout << params1 << "," <<params << "," << calculated << "," << errorEstimate << std::endl;
		}
	//}
	//fout.close();
}

int main_(int, char*[]) {

	try {

		boost::timer timer;

		testIndexRA();

		double seconds = timer.elapsed();
		std::cout << "calculation time = " << std::endl;
		std::cout << std::fixed << std::setprecision(0) << seconds << " s\n" << std::endl;
		return 0;

	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "unknown error" << std::endl;
		return 1;
	}
}

