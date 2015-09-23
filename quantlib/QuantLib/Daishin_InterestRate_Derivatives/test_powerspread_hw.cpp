
#define testtesttesttest
#ifdef testtesttesttest

#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>

#include "power_spread_note.hpp"
#include "power_spread_swap.hpp"

namespace QuantLib
{
	Integer sessionId()
	{
		return 0;
	}

	void* mutex = NULL;
	void* createMutex() { return NULL; }
	void __Lock::AchieveLock() { }
	void __Lock::ReleaseLock() { }
}

using namespace QuantLib;

int main() {

	try {

		boost::timer timer;

		Date todaysDate = Date::todaysDate();
		Date startDate(4, May, 2012);
		Integer mat = 10;
		Date termDate(startDate + mat*Years);
		Schedule schedule(startDate, termDate, Period(Annual), SouthKorea(), Following, Following, DateGeneration::Backward, false);
		Schedule floatingSchedule(startDate, termDate, Period(Quarterly), SouthKorea(), Following, Following, DateGeneration::Backward, false);

		Real notional = 10000;
		std::vector<Real> gearing(1, 10);
		std::vector<Real> spread(1, 0.03);
		std::vector<Real> caps(1, 0.1);
		std::vector<Real> floors(1, 0.0);
		bool isAvg = false;

		Date firstCallDate = startDate + 1*Years;
		DayCounter dayCounter = Actual365Fixed();
		BusinessDayConvention bdc = Following;

		Real alpha = 0.0;
		Rate floatingFixingRate = 0.03;


		std::vector<Date> dates, dates_yen, dates_ktb;
		std::vector<Rate> yields, yields_yen, yields_ktb;	

		BigInteger dateNum[] = {41149, 41240, 41333, 41423, 41515, 41880, 42247, 42611,	42976, 43706, 44802, 45533, 46629, 48456, 59413};
		Rate rates[] = {0.0318, 0.0318, 0.0301, 0.0294, 0.0288, 0.0277, 0.0277, 0.0278, 0.028, 0.0286, 0.0296, 0.03, 0.0299, 0.0306, 0.0306};

		BigInteger dateNum_ktb[] = {41149, 41253, 41343, 41435, 41800, 42165, 42804, 44722, 48192};
		Rate rates_ktb[] = {0.0285, 0.0285, 0.0286, 0.0285, 0.0281, 0.0279, 0.0289, 0.0306, 0.0312};

		BigInteger dateNum_yen[] = {41149, 41240, 41333, 41516,	41880,  42247, 42612, 42977, 43707,	44803, 45534, 46629, 48456, 59413};
		Rate rates_yen[] = {0.0019, 0.0019, 0.0033, 0.0032, 0.003, 0.0031, 0.0033, 0.0038, 0.0053, 0.0084, 0.0105, 0.0132, 0.0162, 0.0162};

		for (Size i=0; i<15; ++i) {
			dates.push_back(Date(dateNum[i]));
			yields.push_back(rates[i]);
		}
		for (Size i=0; i<9; ++i) {
			dates_ktb.push_back(Date(dateNum_ktb[i]));
			yields_ktb.push_back(rates_ktb[i]);
		}
		for (Size i=0; i<14; ++i) {
			dates_yen.push_back(Date(dateNum_yen[i]));
			yields_yen.push_back(rates_yen[i]);
		}


		//for (Size i=0; i<yields_ktb.size()+1; ++i) {

		//	if (i<yields_ktb.size())
		//		yields_ktb[i] += 0.003;

			boost::shared_ptr<YieldTermStructure> disc(new InterpolatedZeroCurve<Linear>(dates_ktb, yields_ktb, Actual365Fixed(), Linear()));
			boost::shared_ptr<YieldTermStructure> rts1(new InterpolatedZeroCurve<Linear>(dates, yields, Actual365Fixed(), Linear()));
			//boost::shared_ptr<YieldTermStructure> rts2(new InterpolatedZeroCurve<Linear>(dates_yen, yields_yen, Actual365Fixed(), Linear()));
			boost::shared_ptr<YieldTermStructure> rts2(new InterpolatedZeroCurve<Linear>(dates_ktb, yields_ktb, Actual365Fixed(), Linear()));

			Size numSimulation = 10000;
			Size numCalibration =512;

			Real a = 0.02847;
			Real sigma = 0.0065758;

			Real a_ktb = 0.0187206;
			Real sigma_ktb = 0.006701688;

			Real a_yen = 7.4e-8;
			Real sigma_yen = 0.0020298;

			YieldCurveParams discCurve(disc, a, sigma);
			
						
			//PowerSpreadSwap testProduct(0, notional, PowerSpreadSwap::Payer, floatingSchedule, floatingcashflows,
			//	alpha, 
			//	fixedSchedule, index, dayCounter, bdc, Null<Natural>(),
			//	gearing, spread, caps, floors, isAvg, 100.0, Date(), 
			//	callSchedule, Exercise::Bermudan);

			//
			//Leg floatingcashflows = IborLeg(floatingSchedule, index1)
			//	.withNotionals(notional)
			//	.withPaymentDayCounter(floatingDayCounter)
			//	.withPaymentAdjustment(bdc)
			//	.withSpreads(alpha)
			//	.withGearings(floatingGearing)
			//	.withPaymentAdjustment(bdc);



			//std::vector<Real> price = power_spread_swap(todaysDate,
			//	notional, PowerSpreadSwap::Receiver, alpha, floatingSchedule, schedule,	dayCounter, bdc,
			//	gearing, spread, caps, floors, isAvg, firstCallDate,
			//	0.03, floatingFixingRate,
			//	boost::shared_ptr<HullWhiteProcess>(new HullWhiteProcess(Handle<YieldTermStructure>(rts1), a, sigma)),
			//	boost::shared_ptr<HullWhiteProcess>(new HullWhiteProcess(Handle<YieldTermStructure>(rts2), a, sigma)),
			//	discCurve, 
			//	0.8, 0.8, 0.8, 
			//	numSimulation, numCalibration);
			//std::cout.precision(8);	
			//std::cout<<i+1<<": Price = "<<price[0];//<<std::endl;

			std::vector<Real> price2 = power_spread_note(todaysDate,
				notional, schedule,	dayCounter, bdc,
				gearing, spread, caps, floors, isAvg, firstCallDate, 
				0.03, 
				boost::shared_ptr<HullWhiteProcess>(new HullWhiteProcess(Handle<YieldTermStructure>(rts1), a, sigma)),
				boost::shared_ptr<HullWhiteProcess>(new HullWhiteProcess(Handle<YieldTermStructure>(rts2), a, sigma)),
				discCurve,
				0.8, 0.8, 0.8, 
				numSimulation, numCalibration);
			std::cout.precision(8);	
			std::cout<<"\t"<<price2[0]<<std::endl;

			//if (i<yields_ktb.size())
			//	yields_ktb[i] -= 0.003;
				
		//}

		return 0;

	} catch (std::exception& e) {

		std::cerr << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "unknown error" << std::endl;
		return 1;
	}

}

#endif