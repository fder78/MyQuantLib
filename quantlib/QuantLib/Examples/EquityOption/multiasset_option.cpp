#include "utilities.hpp"
#include <ql/time/daycounters/actual360.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/pricingengines/basket/stulzengine.hpp>
#include <ql/pricingengines/basket/kirkengine.hpp>
#include <ql/pricingengines/basket/mceuropeanbasketengine.hpp>
#include <ql/pricingengines/basket/mcamericanbasketengine.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/processes/stochasticprocessarray.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/pricingengines/basket/fd2dblackscholesvanillaengine.hpp>
#include <ql/utilities/dataformatters.hpp>
//#include <boost/progress.hpp>

#include <boost/timer.hpp>

using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {

	Integer sessionId() { return 0; }

}
#endif


namespace {

	enum BasketType { MinBasket, MaxBasket, SpreadBasket };

	std::string basketTypeToString(BasketType basketType) {
		switch (basketType) {
		case MinBasket:
			return "MinBasket";
		case MaxBasket:
			return "MaxBasket";
		case SpreadBasket:
			return "Spread";
		}
		QL_FAIL("unknown basket option type");
	}

	boost::shared_ptr<BasketPayoff> basketTypeToPayoff(
		BasketType basketType,
		const boost::shared_ptr<Payoff> &p) {
		switch (basketType) {
		case MinBasket:
			return boost::shared_ptr<BasketPayoff>(new MinBasketPayoff(p));
		case MaxBasket:
			return boost::shared_ptr<BasketPayoff>(new MaxBasketPayoff(p));
		case SpreadBasket:
			return boost::shared_ptr<BasketPayoff>(new SpreadBasketPayoff(p));
		}
		QL_FAIL("unknown basket option type");
	}

	struct BasketOptionOneData {
		Option::Type type;
		Real strike;
		Real s;        // spot
		Rate q;        // dividend
		Rate r;        // risk-free rate
		Time t;        // time to maturity
		Volatility v;  // volatility
		Real result;   // expected result
		Real tol;      // tolerance
	};

	struct BasketOptionTwoData {
		BasketType basketType;
		Option::Type type;
		Real strike;
		Real s1;
		Real s2;
		Rate q1;
		Rate q2;
		Rate r;
		Time t; // years
		Volatility v1;
		Volatility v2;
		Real rho;
		Real result;
		Real tol;
	};

	struct BasketOptionThreeData {
		BasketType basketType;
		Option::Type type;
		Real strike;
		Real s1;
		Real s2;
		Real s3;
		Rate r;
		Time t; // months
		Volatility v1;
		Volatility v2;
		Volatility v3;
		Real rho;
		Real euroValue;
		Real amValue;
	};

}

void testBarraquandThreeValues() {

		/*
		Data from:
		"Numerical Valuation of High Dimensional American Securities"
		Barraquand, J. and Martineau, D.
		Journal of Financial and Quantitative Analysis 1995 3(30) 383-405
		*/
		BasketOptionThreeData  values[] = {
		// time in months is with 30 days to the month..
		// basketType, optionType,       strike,    s1,    s2,   s3,    r,    t,   v1,   v2,  v3,  rho, euro, american,
		// Table 2
		// not using 4 month case to speed up test
		/*
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.0, 8.59, 8.59},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.0, 3.84, 3.84},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.0, 0.89, 0.89},
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.0, 12.55, 12.55},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.0, 7.87, 7.87},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.0, 4.26, 4.26},
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.0, 15.29, 15.29},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.0, 10.72, 10.72},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.0, 6.96, 6.96},
		*/
		/*
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.5, 7.78, 7.78},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.5, 3.18, 3.18},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.5, 0.82, 0.82},
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.5, 10.97, 10.97},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.5, 6.69, 6.69},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.5, 3.70, 3.70},
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.5, 13.23, 13.23},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.5, 9.11, 9.11},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.5, 5.98, 5.98},
		*/
		/*
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 1.0, 6.53, 6.53},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 1.0, 2.38, 2.38},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 1.0, 0.74, 0.74},
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 1.0, 8.51, 8.51},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 1.0, 4.92, 4.92},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 1.0, 2.97, 2.97},
		{MaxBasket, Option::Call,  35.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 1.0, 10.04, 10.04},
		{MaxBasket, Option::Call,  40.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 1.0, 6.64, 6.64},
		{MaxBasket, Option::Call,  45.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 1.0, 4.61, 4.61},
		*/
		// Table 3

			{ MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.0, 0.00, 0.00 },
			{ MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.0, 0.13, 0.23 },
			{ MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.0, 2.26, 5.00 },
		//{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.0, 0.01, 0.01},
			{ MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.0, 0.25, 0.44 },
			{ MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.0, 1.55, 5.00 },
		//{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.0, 0.03, 0.04},
		//{MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.0, 0.31, 0.57},
			{ MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.0, 1.41, 5.00 },

		/*
		{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.5, 0.00, 0.00},
		{MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.5, 0.38, 0.48},
		{MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 0.5, 3.00, 5.00},
		{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.5, 0.07, 0.09},
		{MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.5, 0.72, 0.93},
		{MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 0.5, 2.65, 5.00},
		{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.5, 0.17, 0.20},
		*/
			{ MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.5, 0.91, 1.19 },
		/*
		{MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 0.5, 2.63, 5.00},

		{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 1.0, 0.01, 0.01},
		{MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 1.0, 0.84, 0.08},
		{MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 1.00, 0.20, 0.30, 0.50, 1.0, 4.18, 5.00},
		{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 1.0, 0.19, 0.19},
		{MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 1.0, 1.51, 1.56},
		{MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 4.00, 0.20, 0.30, 0.50, 1.0, 4.49, 5.00},
		{MaxBasket, Option::Put,  35.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 1.0, 0.41, 0.42},
		{MaxBasket, Option::Put,  40.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 1.0, 1.87, 1.96},
		{MaxBasket, Option::Put,  45.0,  40.0,  40.0, 40.0, 0.05, 7.00, 0.20, 0.30, 0.50, 1.0, 4.70, 5.20}
		*/
	};

	DayCounter dc = Actual360();
	Date today = Date::todaysDate();

	boost::shared_ptr<SimpleQuote> spot1(new SimpleQuote(0.0));
	boost::shared_ptr<SimpleQuote> spot2(new SimpleQuote(0.0));
	boost::shared_ptr<SimpleQuote> spot3(new SimpleQuote(0.0));

	boost::shared_ptr<SimpleQuote> qRate(new SimpleQuote(0.0));
	boost::shared_ptr<YieldTermStructure> qTS = flatRate(today, qRate, dc);

	boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.0));
	boost::shared_ptr<YieldTermStructure> rTS = flatRate(today, rRate, dc);

	boost::shared_ptr<SimpleQuote> vol1(new SimpleQuote(0.0));
	boost::shared_ptr<BlackVolTermStructure> volTS1 = flatVol(today, vol1, dc);
	boost::shared_ptr<SimpleQuote> vol2(new SimpleQuote(0.0));
	boost::shared_ptr<BlackVolTermStructure> volTS2 = flatVol(today, vol2, dc);
	boost::shared_ptr<SimpleQuote> vol3(new SimpleQuote(0.0));
	boost::shared_ptr<BlackVolTermStructure> volTS3 = flatVol(today, vol3, dc);

	for (Size i = 0; i<LENGTH(values); i++) {

		boost::shared_ptr<PlainVanillaPayoff> payoff(new
			PlainVanillaPayoff(values[i].type, values[i].strike));

		Date exDate = today + Integer(values[i].t) * 30;
		boost::shared_ptr<Exercise> exercise(new EuropeanExercise(exDate));
		boost::shared_ptr<Exercise> amExercise(new AmericanExercise(today,
			exDate));

		spot1->setValue(values[i].s1);
		spot2->setValue(values[i].s2);
		spot3->setValue(values[i].s3);
		rRate->setValue(values[i].r);
		vol1->setValue(values[i].v1);
		vol2->setValue(values[i].v2);
		vol3->setValue(values[i].v3);

		boost::shared_ptr<StochasticProcess1D> stochProcess1(new
			BlackScholesMertonProcess(Handle<Quote>(spot1),
				Handle<YieldTermStructure>(qTS),
				Handle<YieldTermStructure>(rTS),
				Handle<BlackVolTermStructure>(volTS1)));

		boost::shared_ptr<StochasticProcess1D> stochProcess2(new
			BlackScholesMertonProcess(Handle<Quote>(spot2),
				Handle<YieldTermStructure>(qTS),
				Handle<YieldTermStructure>(rTS),
				Handle<BlackVolTermStructure>(volTS2)));

		boost::shared_ptr<StochasticProcess1D> stochProcess3(new
			BlackScholesMertonProcess(Handle<Quote>(spot3),
				Handle<YieldTermStructure>(qTS),
				Handle<YieldTermStructure>(rTS),
				Handle<BlackVolTermStructure>(volTS3)));

		std::vector<boost::shared_ptr<StochasticProcess1D> > procs;
		procs.push_back(stochProcess1);
		procs.push_back(stochProcess2);
		procs.push_back(stochProcess3);

		Matrix correlation(3, 3, values[i].rho);
		for (Integer j = 0; j < 3; j++) {
			correlation[j][j] = 1.0;
		}

		// FLOATING_POINT_EXCEPTION
		boost::shared_ptr<StochasticProcessArray> process(
			new StochasticProcessArray(procs, correlation));

		Size requiredSamples = 1000;
		Size timeSteps = 500;
		BigNatural seed = 1;
		boost::shared_ptr<PricingEngine> mcLSMCEngine =
			MakeMCAmericanBasketEngine<>(process)
			.withSteps(timeSteps)
			.withAntitheticVariate()
			.withSamples(requiredSamples)
			.withCalibrationSamples(requiredSamples / 4)
			.withSeed(seed);

		BasketOption amBasketOption(basketTypeToPayoff(values[i].basketType,
			payoff),
			amExercise);
		amBasketOption.setPricingEngine(mcLSMCEngine);

		Real calculated = amBasketOption.NPV();
		Real errorEstimate = amBasketOption.errorEstimate();
		std::cout << "Price = " << calculated << "     SE = " << errorEstimate << std::endl;
	}
}

void testTavellaValues() {
		/*
		Data from:
		"Quantitative Methods in Derivatives Pricing"
		Tavella, D. A.   -   Wiley (2002)
		*/
		BasketOptionThreeData  values[] = {
		// time in months is with 30 days to the month..
		// basketType, optionType,       strike,    s1,    s2,   s3,    r,    t,   v1,   v2,  v3,  rho, euroValue, american Value,
			{ MaxBasket, Option::Call,  100,    100,   100, 100,  0.05, 3.00, 0.20, 0.20, 0.20, 0.0, -999, 18.082 }
	};
		std::cout << "\nTavella" << std::endl;
	DayCounter dc = Actual360();
	Date today = Date::todaysDate();

	boost::shared_ptr<SimpleQuote> spot1(new SimpleQuote(0.0));
	boost::shared_ptr<SimpleQuote> spot2(new SimpleQuote(0.0));
	boost::shared_ptr<SimpleQuote> spot3(new SimpleQuote(0.0));

	boost::shared_ptr<SimpleQuote> qRate(new SimpleQuote(0.1));
	boost::shared_ptr<YieldTermStructure> qTS = flatRate(today, qRate, dc);

	boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.05));
	boost::shared_ptr<YieldTermStructure> rTS = flatRate(today, rRate, dc);

	boost::shared_ptr<SimpleQuote> vol1(new SimpleQuote(0.0));
	boost::shared_ptr<BlackVolTermStructure> volTS1 = flatVol(today, vol1, dc);
	boost::shared_ptr<SimpleQuote> vol2(new SimpleQuote(0.0));
	boost::shared_ptr<BlackVolTermStructure> volTS2 = flatVol(today, vol2, dc);
	boost::shared_ptr<SimpleQuote> vol3(new SimpleQuote(0.0));
	boost::shared_ptr<BlackVolTermStructure> volTS3 = flatVol(today, vol3, dc);

	Real mcRelativeErrorTolerance = 0.01;
	Size requiredSamples = 10000;
	Size timeSteps = 20;
	BigNatural seed = 0;


	boost::shared_ptr<PlainVanillaPayoff> payoff(new
		PlainVanillaPayoff(values[0].type, values[0].strike));

	Date exDate = today + Integer(values[0].t * 360 + 0.5);
	boost::shared_ptr<Exercise> exercise(new AmericanExercise(today, exDate));

	spot1->setValue(values[0].s1);
	spot2->setValue(values[0].s2);
	spot3->setValue(values[0].s3);
	vol1->setValue(values[0].v1);
	vol2->setValue(values[0].v2);
	vol3->setValue(values[0].v3);

	boost::shared_ptr<StochasticProcess1D> stochProcess1(new
		BlackScholesMertonProcess(Handle<Quote>(spot1),
			Handle<YieldTermStructure>(qTS),
			Handle<YieldTermStructure>(rTS),
			Handle<BlackVolTermStructure>(volTS1)));

	boost::shared_ptr<StochasticProcess1D> stochProcess2(new
		BlackScholesMertonProcess(Handle<Quote>(spot2),
			Handle<YieldTermStructure>(qTS),
			Handle<YieldTermStructure>(rTS),
			Handle<BlackVolTermStructure>(volTS2)));

	boost::shared_ptr<StochasticProcess1D> stochProcess3(new
		BlackScholesMertonProcess(Handle<Quote>(spot3),
			Handle<YieldTermStructure>(qTS),
			Handle<YieldTermStructure>(rTS),
			Handle<BlackVolTermStructure>(volTS3)));

	std::vector<boost::shared_ptr<StochasticProcess1D> > procs;
	procs.push_back(stochProcess1);
	procs.push_back(stochProcess2);
	procs.push_back(stochProcess3);

	Matrix correlation(3, 3, 0.0);
	for (Integer j = 0; j < 3; j++) {
		correlation[j][j] = 1.0;
	}
	correlation[1][0] = -0.25;
	correlation[0][1] = -0.25;
	correlation[2][0] = 0.25;
	correlation[0][2] = 0.25;
	correlation[2][1] = 0.3;
	correlation[1][2] = 0.3;

	boost::shared_ptr<StochasticProcessArray> process(
		new StochasticProcessArray(procs, correlation));
	boost::shared_ptr<PricingEngine> mcLSMCEngine =
		MakeMCAmericanBasketEngine<>(process)
		.withSteps(timeSteps)
		.withAntitheticVariate()
		.withSamples(requiredSamples)
		.withCalibrationSamples(requiredSamples / 4)
		.withSeed(seed);

	BasketOption basketOption(basketTypeToPayoff(values[0].basketType,
		payoff),
		exercise);
	basketOption.setPricingEngine(mcLSMCEngine);

	Real calculated = basketOption.NPV();
	Real errorEstimate = basketOption.errorEstimate();

	std::cout << "Price = " << calculated << "     SE = " << errorEstimate << std::endl;

}

int main(int, char*[]) {

	try {

		boost::timer timer;

		testBarraquandThreeValues();
		testTavellaValues();		
		
		double seconds = timer.elapsed();
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

