
#pragma warning(disable:4819)

#include <ql/quantlib.hpp>
#include <ir_derivatives\g2_calibration.hpp>
#include <ir_derivatives\pricing_cms_spread_ra.hpp>

#ifdef BOOST_MSVC
/* Uncomment the following lines to unmask floating-point
   exceptions. Warning: unpredictable results can arise...

   See http://www.wilmott.com/messageview.cfm?catid=10&threadid=9481
   Is there anyone with a definitive word about this?
*/
// #include <float.h>
// namespace { unsigned int u = _controlfp(_EM_INEXACT, _MCW_EM); }
#endif

#include <boost/timer.hpp>
#include <iostream>
#include <iomanip>

using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {
    Integer sessionId() { return 0; }
}
#endif


//Number of swaptions to be calibrated to...

Size numRows = 5;
Size numCols = 5;
Integer swapLenghts[] = {1, 2, 3, 4, 5};
Integer swaptionMaturities[] = {1, 2, 3, 4, 5};
Volatility swaptionVols[] = {
  0.1490, 0.1340, 0.1228, 0.1189, 0.1148,
  0.1290, 0.1201, 0.1146, 0.1108, 0.1040,
  0.1149, 0.1112, 0.1070, 0.1010, 0.0957,
  0.1047, 0.1021, 0.0980, 0.0951, 0.1270,
  0.1000, 0.0950, 0.0900, 0.1230, 0.1160};

void calibrateModel(
          const boost::shared_ptr<ShortRateModel>& model,
          const std::vector<boost::shared_ptr<CalibrationHelper> >& helpers) {

	LevenbergMarquardt optimizationMethod(1.0e-8, 1.0e-8, 1.0e-8);
	EndCriteria endCriteria(50000, 1000, 1e-8, 1e-8, 1e-8);
	model->calibrate(helpers, optimizationMethod, endCriteria);

    // Output the implied Black volatilities
    for (Size i=0; i<numRows; i++) {
        Size j = numCols - i -1; // 1x5, 2x4, 3x3, 4x2, 5x1
        Size k = i*numCols + j;
        Real npv = helpers[i]->modelValue();
        Volatility implied = helpers[i]->impliedVolatility(npv, 1e-4,
                                                           1000, 0.05, 0.50);
        Volatility diff = implied - swaptionVols[k];

        std::cout << i+1 << "x" << swapLenghts[j]
                  << std::setprecision(5) << std::noshowpos
                  << ": model " << std::setw(7) << io::volatility(implied)
                  << ", market " << std::setw(7)
                  << io::volatility(swaptionVols[k])
                  << " (" << std::setw(7) << std::showpos
                  << io::volatility(diff) << std::noshowpos << ")\n";
    }
}

int main(int, char* []) {

    try {

        boost::timer timer;
        std::cout << std::endl;

        Date todaysDate(15, February, 2002);
        Calendar calendar = TARGET();
        Date settlementDate(19, February, 2002);
        Settings::instance().evaluationDate() = todaysDate;

        // flat yield term structure impling 1x5 swap at 5%
        boost::shared_ptr<Quote> flatRate(new SimpleQuote(0.04875825));
        Handle<YieldTermStructure> rhTermStructure(boost::shared_ptr<FlatForward>(new FlatForward(settlementDate, Handle<Quote>(flatRate), Actual365Fixed())));
        boost::shared_ptr<IborIndex> indexSixMonths(new Euribor6M(rhTermStructure));

		//parameters calibration
		SwaptionVolData swaptionVolData;
		for (Size i = 0; i < numRows; i++) {
			Size j = numCols - i - 1; // 1x5, 2x4, 3x3, 4x2, 5x1
			Size k = i*numCols + j;
			swaptionVolData.vols.push_back(swaptionVols[k]);
			swaptionVolData.lengths.push_back(Period(swapLenghts[j], Years));
			swaptionVolData.maturities.push_back(Period(swaptionMaturities[i], Years));
		}
		swaptionVolData.fixedFreq = indexSixMonths->tenor().frequency();
		swaptionVolData.fixedDC = indexSixMonths->dayCounter();
		swaptionVolData.floatingDC = indexSixMonths->dayCounter();
		swaptionVolData.index = indexSixMonths;

		G2Parameters param = calibration_g2(todaysDate, swaptionVolData);
		std::cout << "calibrated to:\n"
			<< "a     = " << param.a << ", "
			<< "sigma = " << param.sigma << "\n"
			<< "b     = " << param.b << ", "
			<< "eta   = " << param.eta << "\n"
			<< "rho   = " << param.rho << std::endl << std::endl; 
		

		// defining the models
        boost::shared_ptr<G2> modelG2(new G2(rhTermStructure));

		// Define the swaps
		Frequency fixedLegFrequency = Annual;
		BusinessDayConvention fixedLegConvention = Unadjusted;
		BusinessDayConvention floatingLegConvention = ModifiedFollowing;
		DayCounter fixedLegDayCounter = Thirty360(Thirty360::European);
		Frequency floatingLegFrequency = Semiannual;
		VanillaSwap::Type type = VanillaSwap::Payer;
		boost::shared_ptr<SwapIndex> si1(new UsdLiborSwapIsdaFixPm(Period(10, Years), rhTermStructure));
		boost::shared_ptr<SwapIndex> si2(new UsdLiborSwapIsdaFixPm(Period(2, Years), rhTermStructure));
		boost::shared_ptr<SwapSpreadIndex> swapSpreadIndex(new SwapSpreadIndex("CMS10-2", si1, si2));
		Date startDate = calendar.advance(settlementDate, 1, Years, floatingLegConvention);
		Date maturity = calendar.advance(startDate, 5, Years, floatingLegConvention);
		Schedule fixedSchedule(startDate, maturity, Period(fixedLegFrequency), calendar, fixedLegConvention, fixedLegConvention, DateGeneration::Forward, false);
		Schedule floatSchedule(startDate, maturity, Period(floatingLegFrequency), calendar, floatingLegConvention, floatingLegConvention, DateGeneration::Forward, false);

		std::vector<Real> rst = cms_spread_rangeaccrual_fdm(todaysDate, 10000,
			std::vector<Rate>(1, 0.05),		//std::vector<Rate> couponRate,
			std::vector<Rate>(1, 0.0),		//std::vector<Real> gearing,
			fixedSchedule,					//	Schedule schedule,
			fixedLegDayCounter,				//	DayCounter dayCounter,
			fixedLegConvention,				//	BusinessDayConvention bdc,
			std::vector<Real>(1, 0.0),		//	std::vector<Real> lowerBound,
			std::vector<Real>(1, 0.05),		//	std::vector<Real> upperBound,
			fixedSchedule[1],				//	Date firstCallDate,
			0.0,							//	Real pastAccrual,
			rhTermStructure.currentLink(),	//	boost::shared_ptr<YieldTermStructure> obs1Curve,
			param,							//	const G2Parameters& obs1G2Params,
			0.0, 0.0,						//	Real obs1FXVol, Real obs1FXCorr,
			rhTermStructure,				//	Handle<YieldTermStructure>& discTS,
			50, 20,							//	Size tGrid, Size rGrid,
			0.0,							//	Real alpha,
			0.0,							//	Real pastFixing,
			floatSchedule);					//	Schedule floatingSchedule);
		std::cout << "price = " << rst[0] << std::endl;

		/***********************************************************************/
		double seconds = timer.elapsed();
		Integer hours = int(seconds / 3600);
		seconds -= hours * 3600;
		Integer minutes = int(seconds / 60);
		seconds -= minutes * 60;
		std::cout << " \nRun completed in ";
		if (hours > 0)
			std::cout << hours << " h ";
		if (hours > 0 || minutes > 0)
			std::cout << minutes << " m ";
		std::cout << std::fixed << std::setprecision(0)
			<< seconds << " s\n" << std::endl;

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}

