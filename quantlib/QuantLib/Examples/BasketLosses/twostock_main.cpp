
#include <ql/quantlib.hpp>
#include <boost/timer.hpp>
#include <iostream>

#include "utilities.hpp"
#include <eq_derivatives\3dfdm\fd3dblackscholesvanillaengine.hpp>
#include <eq_derivatives\autocallable_engine\autocall_engine.h>
#include <eq_derivatives\autocallable_instrument\autocallable_note.h>

using namespace std;
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


#ifdef THREE_FDM
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

	for (Size i = 0; i < LENGTH(values); i++) {

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

		boost::shared_ptr<GeneralizedBlackScholesProcess> stochProcess1(new
			BlackScholesMertonProcess(Handle<Quote>(spot1),
				Handle<YieldTermStructure>(qTS),
				Handle<YieldTermStructure>(rTS),
				Handle<BlackVolTermStructure>(volTS1)));

		boost::shared_ptr<GeneralizedBlackScholesProcess> stochProcess2(new
			BlackScholesMertonProcess(Handle<Quote>(spot2),
				Handle<YieldTermStructure>(qTS),
				Handle<YieldTermStructure>(rTS),
				Handle<BlackVolTermStructure>(volTS2)));

		boost::shared_ptr<GeneralizedBlackScholesProcess> stochProcess3(new
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

		// use a 3D sobol sequence...
		// Think long and hard before moving to more than 1 timestep....
		boost::shared_ptr<PricingEngine> mcQuasiEngine =
			MakeMCEuropeanBasketEngine<LowDiscrepancy>(process)
			.withStepsPerYear(1)
			.withSamples(80910)
			.withSeed(42);


		//3d fdm engine...
		boost::shared_ptr<PricingEngine> fdmEngine(new Fd3dBlackScholesVanillaEngine(
			stochProcess1, stochProcess2, stochProcess3, correlation, std::vector<Size>(3, 50), 100, 0, FdmSchemeDesc::Hundsdorfer()));


		BasketOption euroBasketOption(basketTypeToPayoff(values[i].basketType,
			payoff),
			exercise);
		euroBasketOption.setPricingEngine(fdmEngine);

		Real expected = values[i].euroValue;
		Real calculated = euroBasketOption.NPV();
		Real relError = relativeError(calculated, expected, values[i].s1);
		Real mcRelativeErrorTolerance = 0.01;
		std::cout << expected << "\t";
		std::cout << calculated << "\t";

		euroBasketOption.setPricingEngine(mcQuasiEngine);
		std::cout << euroBasketOption.NPV() << "\t";
		std::cout << relError << "\n";

		/*
		//American Option
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

		expected = values[i].amValue;
		calculated = amBasketOption.NPV();
		relError = relativeError(calculated, expected, values[i].s1);
		Real mcAmericanRelativeErrorTolerance = 0.01;
		std::cout << calculated << "\n";
		*/
	}
}

#endif

void testEuroTwoValues() {

	BasketOptionTwoData values[] = {
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.90, 10.898, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.70,  8.483, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.50,  6.844, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30,  5.531, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.10,  4.413, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.50, 0.70, 0.00,  4.981, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.50, 0.30, 0.00,  4.159, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.50, 0.10, 0.00,  2.597, 1.0e-3 },
		{ MinBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.50, 0.10, 0.50,  4.030, 1.0e-3 },

		{ MaxBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.90, 17.565, 1.0e-3 },
		{ MaxBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.70, 19.980, 1.0e-3 },
		{ MaxBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.50, 21.619, 1.0e-3 },
		{ MaxBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30, 22.932, 1.0e-3 },
		{ MaxBasket, Option::Call,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.10, 24.049, 1.1e-3 },
		{ MaxBasket, Option::Call,  100.0,  80.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30, 16.508, 1.0e-3 },
		{ MaxBasket, Option::Call,  100.0,  80.0,  80.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30,  8.049, 1.0e-3 },
		{ MaxBasket, Option::Call,  100.0,  80.0, 120.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30, 30.141, 1.0e-3 },
		{ MaxBasket, Option::Call,  100.0, 120.0, 120.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30, 42.889, 1.0e-3 },

		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.90, 11.369, 1.0e-3 },
		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.70, 12.856, 1.0e-3 },
		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.50, 13.890, 1.0e-3 },
		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30, 14.741, 1.0e-3 },
		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.10, 15.485, 1.0e-3 },

		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 0.50, 0.30, 0.30, 0.10, 11.893, 1.0e-3 },
		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 0.25, 0.30, 0.30, 0.10,  8.881, 1.0e-3 },
		{ MinBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 2.00, 0.30, 0.30, 0.10, 19.268, 1.0e-3 },

		{ MaxBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.90,  7.339, 1.0e-3 },
		{ MaxBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.70,  5.853, 1.0e-3 },
		{ MaxBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.50,  4.818, 1.0e-3 },
		{ MaxBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.30,  3.967, 1.1e-3 },
		{ MaxBasket,  Option::Put,  100.0, 100.0, 100.0, 0.00, 0.00, 0.05, 1.00, 0.30, 0.30, 0.10,  3.223, 1.0e-3 },

		{ MinBasket, Option::Call,   98.0, 100.0, 105.0, 0.00, 0.00, 0.05, 0.50, 0.11, 0.16, 0.63,  4.8177, 1.0e-4 },
		{ MaxBasket, Option::Call,   98.0, 100.0, 105.0, 0.00, 0.00, 0.05, 0.50, 0.11, 0.16, 0.63, 11.6323, 1.0e-4 },
		{ MinBasket,  Option::Put,   98.0, 100.0, 105.0, 0.00, 0.00, 0.05, 0.50, 0.11, 0.16, 0.63,  2.0376, 1.0e-4 },
		{ MaxBasket,  Option::Put,   98.0, 100.0, 105.0, 0.00, 0.00, 0.05, 0.50, 0.11, 0.16, 0.63,  0.5731, 1.0e-4 },
		{ MinBasket, Option::Call,   98.0, 100.0, 105.0, 0.06, 0.09, 0.05, 0.50, 0.11, 0.16, 0.63,  2.9340, 1.0e-4 },
		{ MinBasket,  Option::Put,   98.0, 100.0, 105.0, 0.06, 0.09, 0.05, 0.50, 0.11, 0.16, 0.63,  3.5224, 1.0e-4 },
		{ MaxBasket, Option::Call,   98.0, 100.0, 105.0, 0.06, 0.09, 0.05, 0.50, 0.11, 0.16, 0.63,  8.0701, 1.0e-4 },
		{ MaxBasket,  Option::Put,   98.0, 100.0, 105.0, 0.06, 0.09, 0.05, 0.50, 0.11, 0.16, 0.63,  1.2181, 1.0e-4 },

		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.20, 0.20, -0.5, 4.7530, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.20, 0.20,  0.0, 3.7970, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.20, 0.20,  0.5, 2.5537, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.25, 0.20, -0.5, 5.4275, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.25, 0.20,  0.0, 4.3712, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.25, 0.20,  0.5, 3.0086, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.20, 0.25, -0.5, 5.4061, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.20, 0.25,  0.0, 4.3451, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.1, 0.20, 0.25,  0.5, 2.9723, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.20, 0.20, -0.5,10.7517, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.20, 0.20,  0.0, 8.7020, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.20, 0.20,  0.5, 6.0257, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.25, 0.20, -0.5,12.1941, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.25, 0.20,  0.0, 9.9340, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.25, 0.20,  0.5, 7.0067, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.20, 0.25, -0.5,12.1483, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.20, 0.25,  0.0, 9.8780, 1.0e-3 },
		{ SpreadBasket, Option::Call, 3.0,  122.0, 120.0, 0.0, 0.0, 0.10,  0.5, 0.20, 0.25,  0.5, 6.9284, 1.0e-3 }
	};

	DayCounter dc = Actual360();
	Date today = Date::todaysDate();

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

	const Real mcRelativeErrorTolerance = 0.01;
	const Real fdRelativeErrorTolerance = 0.01;

	for (Size i = 0; i<LENGTH(values); i++) {

		boost::shared_ptr<PlainVanillaPayoff> payoff(new PlainVanillaPayoff(values[i].type, values[i].strike));

		Date exDate = today + Integer(values[i].t * 360 + 0.5);
		std::vector<Date> dates;
		std::vector<boost::shared_ptr<AutocallCondition> > autocallConditions;
		std::vector<boost::shared_ptr<BasketPayoff> > autocallPayoffs;
		boost::shared_ptr<BasketPayoff> terminalPayoff(new MinBasketPayoff(payoff));
		for (Size i = 1; i <= 12; ++i) {
			dates.push_back(today + i*Months);
			autocallConditions.push_back(boost::shared_ptr<AutocallCondition>(new MinUpCondition(100)));
			autocallPayoffs.push_back(boost::shared_ptr<BasketPayoff>(new MinBasketPayoff(payoff)));
		}
		//boost::shared_ptr<Exercise> exercise(new BermudanExercise(dates));

		spot1->setValue(values[i].s1);
		spot2->setValue(values[i].s2);
		qRate1->setValue(values[i].q1);
		qRate2->setValue(values[i].q2);
		rRate->setValue(values[i].r);
		vol1->setValue(values[i].v1);
		vol2->setValue(values[i].v2);

		boost::shared_ptr<PricingEngine> analyticEngine;
		boost::shared_ptr<GeneralizedBlackScholesProcess> p1, p2;
		switch (values[i].basketType) {
		case MaxBasket:
		case MinBasket:
			p1 = boost::shared_ptr<GeneralizedBlackScholesProcess>(
				new BlackScholesMertonProcess(
					Handle<Quote>(spot1),
					Handle<YieldTermStructure>(qTS1),
					Handle<YieldTermStructure>(rTS),
					Handle<BlackVolTermStructure>(volTS1)));
			p2 = boost::shared_ptr<GeneralizedBlackScholesProcess>(
				new BlackScholesMertonProcess(
					Handle<Quote>(spot2),
					Handle<YieldTermStructure>(qTS2),
					Handle<YieldTermStructure>(rTS),
					Handle<BlackVolTermStructure>(volTS2)));
			analyticEngine = boost::shared_ptr<PricingEngine>(
				new StulzEngine(p1, p2, values[i].rho));
			break;
		case SpreadBasket:
			p1 = boost::shared_ptr<GeneralizedBlackScholesProcess>(
				new BlackProcess(Handle<Quote>(spot1),
					Handle<YieldTermStructure>(rTS),
					Handle<BlackVolTermStructure>(volTS1)));
			p2 = boost::shared_ptr<GeneralizedBlackScholesProcess>(
				new BlackProcess(Handle<Quote>(spot2),
					Handle<YieldTermStructure>(rTS),
					Handle<BlackVolTermStructure>(volTS2)));

			analyticEngine = boost::shared_ptr<PricingEngine>(
				new KirkEngine(boost::dynamic_pointer_cast<BlackProcess>(p1),
					boost::dynamic_pointer_cast<BlackProcess>(p2),
					values[i].rho));
			break;
		default:
			QL_FAIL("unknown basket type");
		}

		std::vector<boost::shared_ptr<StochasticProcess1D> > procs;
		procs.push_back(p1);
		procs.push_back(p2);

		Matrix correlationMatrix(2, 2, values[i].rho);
		for (Integer j = 0; j < 2; j++) {
			correlationMatrix[j][j] = 1.0;
		}

		boost::shared_ptr<StochasticProcessArray> process(
			new StochasticProcessArray(procs, correlationMatrix));

		boost::shared_ptr<PricingEngine> mcEngine =
			MakeMCEuropeanBasketEngine<PseudoRandom, Statistics>(process)
			.withStepsPerYear(1)
			.withSamples(10000)
			.withSeed(42);

		boost::shared_ptr<PricingEngine> fdEngine(
			new FdAutocallEngine(p1, p2, values[i].rho,	50, 50, 15));

		AutocallableNote autocallable(
			10000, //notional
			dates, //exercise
			dates, //payment
			autocallConditions,
			autocallPayoffs,
			terminalPayoff
			);

		//// analytic engine
		//basketOption.setPricingEngine(analyticEngine);
		//Real calculated = basketOption.NPV();
		Real expected = values[i].result;
		//Real error = std::fabs(calculated - expected);
		//std::cout << calculated << " " << expected << " " << error << std::endl;

		// fd engine
		autocallable.setPricingEngine(fdEngine);
		Real calculated = autocallable.NPV();
		Real relError = relativeError(calculated, expected, expected);
		std::cout << calculated << " " << expected << " " << relError << std::endl;
		std::cout << "theta=" << autocallable.theta()[0] << std::endl;
		std::cout << "delta=" << autocallable.delta()[0] << "   " << autocallable.delta()[1] << std::endl;
		std::cout << "gamma=" << autocallable.gamma()[0] << "   " << autocallable.gamma()[1] << std::endl;

		//// mc engine
		//basketOption.setPricingEngine(mcEngine);
		//calculated = basketOption.NPV();
		//relError = relativeError(calculated, expected, values[i].s1);
		//std::cout << calculated << " " << expected << " " << relError << std::endl;
		//std::cout << std::string(30, '-') << std::endl;
	}
}

int main(int, char*[]) {
	try {
		
		boost::timer timer;
		testEuroTwoValues();
		std::cout << "time = " << timer.elapsed() << std::endl;
		/*
		testBarraquandThreeValues();
		std::cout << "time = " << timer.elapsed() << std::endl;
		*/
		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error" << endl;
		return 1;
	}
}
