#include "utilities.hpp"
#include <iostream>
#include <ql/instruments/swap.hpp>
#include <ql/pricingengines/swap/discountingswapengine.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/indexes/swap/euriborswap.hpp>
#include <ql/cashflows/capflooredcoupon.hpp>
#include <ql/cashflows/conundrumpricer.hpp>
#include <ql/cashflows/cashflowvectors.hpp>
#include <ql/cashflows/lineartsrpricer.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolmatrix.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube2.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube1.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/time/daycounters/actualactual.hpp>
#include <ql/time/schedule.hpp>
#include <ql/utilities/dataformatters.hpp>
#include <ql/instruments/makecms.hpp>

using namespace QuantLib;
using boost::shared_ptr;

namespace {

	struct CommonVars {
		// global data
		RelinkableHandle<YieldTermStructure> termStructure;

		shared_ptr<IborIndex> iborIndex;

		Handle<SwaptionVolatilityStructure> atmVol;
		Handle<SwaptionVolatilityStructure> SabrVolCube1;
		Handle<SwaptionVolatilityStructure> SabrVolCube2;

		std::vector<GFunctionFactory::YieldCurveModel> yieldCurveModels;
		std::vector<shared_ptr<CmsCouponPricer> > numericalPricers;
		std::vector<shared_ptr<CmsCouponPricer> > analyticPricers;

		// cleanup
		SavedSettings backup;

		// setup
		CommonVars() {

			Calendar calendar = TARGET();

			Date referenceDate = calendar.adjust(Date::todaysDate());
			Settings::instance().evaluationDate() = referenceDate;

			termStructure.linkTo(flatRate(referenceDate, 0.025, Actual365Fixed()));

			iborIndex = shared_ptr<IborIndex>(new Euribor6M(termStructure));
			shared_ptr<SwapIndex> swapIndexBase(new EuriborSwapIsdaFixA(10 * Years, termStructure));
			shared_ptr<SwapIndex> shortSwapIndexBase(new EuriborSwapIsdaFixA(2 * Years, termStructure));

			// ATM Volatility structure
			std::vector<Period> atmOptionTenors;
			atmOptionTenors.push_back(Period(1, Months));
			atmOptionTenors.push_back(Period(6, Months));
			atmOptionTenors.push_back(Period(1, Years));
			atmOptionTenors.push_back(Period(5, Years));
			atmOptionTenors.push_back(Period(10, Years));
			atmOptionTenors.push_back(Period(30, Years));

			std::vector<Period> atmSwapTenors;
			atmSwapTenors.push_back(Period(1, Years));
			atmSwapTenors.push_back(Period(5, Years));
			atmSwapTenors.push_back(Period(10, Years));
			atmSwapTenors.push_back(Period(30, Years));

			Matrix m(atmOptionTenors.size(), atmSwapTenors.size());
			m[0][0] = 0.1300; m[0][1] = 0.1560; m[0][2] = 0.1390; m[0][3] = 0.1220;
			m[1][0] = 0.1440; m[1][1] = 0.1580; m[1][2] = 0.1460; m[1][3] = 0.1260;
			m[2][0] = 0.1600; m[2][1] = 0.1590; m[2][2] = 0.1470; m[2][3] = 0.1290;
			m[3][0] = 0.1640; m[3][1] = 0.1470; m[3][2] = 0.1370; m[3][3] = 0.1220;
			m[4][0] = 0.1400; m[4][1] = 0.1300; m[4][2] = 0.1250; m[4][3] = 0.1100;
			m[5][0] = 0.1130; m[5][1] = 0.1090; m[5][2] = 0.1070; m[5][3] = 0.0930;

			atmVol = Handle<SwaptionVolatilityStructure>(
				shared_ptr<SwaptionVolatilityStructure>(new
					SwaptionVolatilityMatrix(calendar,
						Following,
						atmOptionTenors,
						atmSwapTenors,
						m,
						Actual365Fixed())));

			yieldCurveModels.clear();
			yieldCurveModels.push_back(GFunctionFactory::Standard);
			yieldCurveModels.push_back(GFunctionFactory::ExactYield);
			yieldCurveModels.push_back(GFunctionFactory::ParallelShifts);
			yieldCurveModels.push_back(GFunctionFactory::NonParallelShifts);
			yieldCurveModels.push_back(GFunctionFactory::NonParallelShifts); // for linear tsr model

			Handle<Quote> zeroMeanRev(shared_ptr<Quote>(new SimpleQuote(0.0)));

			numericalPricers.clear();
			analyticPricers.clear();
			for (Size j = 0; j < yieldCurveModels.size(); ++j) {
				if (j < yieldCurveModels.size() - 1)
					numericalPricers.push_back(
						shared_ptr<CmsCouponPricer>(new NumericHaganPricer(
							atmVol, yieldCurveModels[j], zeroMeanRev)));
				else
					numericalPricers.push_back(shared_ptr<CmsCouponPricer>(
						new LinearTsrPricer(atmVol, zeroMeanRev)));

				analyticPricers.push_back(shared_ptr<CmsCouponPricer>(new
					AnalyticHaganPricer(atmVol, yieldCurveModels[j],
						zeroMeanRev)));
			}
		}
	};

}

int main_() {

	CommonVars vars;

	shared_ptr<SwapIndex> swapIndex(new SwapIndex("EuriborSwapIsdaFixA",
		10 * Years,
		vars.iborIndex->fixingDays(),
		vars.iborIndex->currency(),
		vars.iborIndex->fixingCalendar(),
		1 * Years,
		Unadjusted,
		vars.iborIndex->dayCounter(),//??
		vars.iborIndex));
	Date startDate = vars.termStructure->referenceDate() + 6 * Months;
	Date paymentDate = startDate + 3*Days;

	for (Size iter = 0; iter < 21; ++iter) {

		Real nominal = 1.0;
		Real R0 = 0.015+0.001*iter;
		Real strike1 = 1.*R0, strike2 = 2.0*R0;
		Real couponRate = 0.05;
		Real tau = 1;
	
		Real p1 = 1 + couponRate, p2 = 0.0;
		Real gearing = (p1-p2) / (strike1-strike2);
		Spread spread = p1 - gearing * strike1;
		Rate infiniteCap = 1 + couponRate;
		Rate infiniteFloor = 0.0;

		CappedFlooredCmsCoupon coupon(paymentDate, nominal,
			startDate, startDate + 12 * Months,
			swapIndex->fixingDays(), swapIndex,
			gearing, spread,
			infiniteCap, infiniteFloor,
			startDate, startDate + 12 * Months,
			ActualActual(ActualActual::ISMA));

		boost::shared_ptr<YieldTermStructure> disc = flatRate(vars.termStructure->referenceDate(), 0.025, ActualActual());

	//for (Size j = 0; j < vars.yieldCurveModels.size(); ++j) {
		Size j = vars.yieldCurveModels.size() - 2;
		vars.numericalPricers[j]->setSwaptionVolatility(vars.atmVol);
		coupon.setPricer(vars.numericalPricers[j]);		
		Rate rate0 = coupon.rate();
		Rate NPV = coupon.amount() * disc->discount(coupon.date());

		vars.analyticPricers[j]->setSwaptionVolatility(vars.atmVol);
		coupon.setPricer(vars.analyticPricers[j]);
		Rate rate1 = coupon.rate();
		Rate NPV1 = coupon.amount() *disc->discount(coupon.date());

		Spread difference = std::fabs(NPV1 - NPV);
		bool linearTsr = j == vars.yieldCurveModels.size() - 1;

		std::cout << R0 << "," << NPV << "," << NPV1 << "\n";
	}

	return 0;

}



// normal_distribution
#include <iostream>
#include <random>
#include <fstream>



int main()
{
	std::ofstream out("c:\\test.csv");
	out << "TEST,TEST" << std::endl;

	const int nrolls = 10000;  // number of experiments
	const int nstars = 100;    // maximum number of stars to distribute

	std::mt19937 generator;
	std::normal_distribution<double> distribution(5.0, 2.0);

	int p[10] = {};

	for (int i = 0; i<nrolls; ++i) {
		double number = distribution(generator);
		if ((number >= 0.0) && (number<10.0)) ++p[int(number)];
		std::cout << number << std::endl;
	}

	std::cout << "normal_distribution (5.0,2.0):" << std::endl;

	for (int i = 0; i<10; ++i) {
		std::cout << i << "-" << (i + 1) << ": ";
		std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
	}

	return 0;
}
