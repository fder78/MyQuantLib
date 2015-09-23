
#define testtesttesttest
#ifdef testtesttesttest

#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>

#include "cap_floor_swaption.hpp"
#include "vanilla_swap.hpp"
#include <ds_interestrate_derivatives/index/cd91.hpp>


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

		BigInteger num = 41149;
		Date todaysDate = Date(num);
		Date startDate(4, May, 2012);
		Integer mat = 10;
		Date termDate(startDate + mat*Years);
		Schedule schedule(startDate, termDate, Period(Annual), SouthKorea(), Following, Following, DateGeneration::Backward, false);
		Schedule floatingSchedule(startDate, termDate, Period(Quarterly), SouthKorea(), Following, Following, DateGeneration::Backward, false);

		Schedule schedule2(startDate+5*Years, termDate, Period(Annual), SouthKorea(), Following, Following, DateGeneration::Backward, false);

		Real notional = 10000;
		Real strike = 0.035;
		DayCounter dayCounter = Actual365Fixed();
		BusinessDayConvention bdc = Following;

		Volatility vol = 0.15;		
		std::vector<Rate> pastFixing;
		std::vector<Date> fixingDates;
		for (Size i=0; i<365; ++i) {
			if (SouthKorea().isBusinessDay(todaysDate-i*Days)){
				fixingDates.push_back(Date(Date(todaysDate-i*Days).serialNumber()));
				pastFixing.push_back(0.032);
			}
		}
		TimeSeries<Real> pastFixings(fixingDates.begin(), fixingDates.end(), pastFixing.begin());

		std::vector<Date> dates;
		std::vector<Rate> yields;

		BigInteger dateNum[] = {41149, 41240, 41333, 41423, 41515, 41880, 42247, 42611,	42976, 43706, 44802, 45533, 46629, 48456, 59413};
		Rate rates[] = {0.0318, 0.0318, 0.0301, 0.0294, 0.0288, 0.0277, 0.0277, 0.0278, 0.028, 0.0286, 0.0296, 0.03, 0.0299, 0.0306, 0.0306};

		for (Size i=0; i<15; ++i) {
			dates.push_back(Date(dateNum[i]));
			yields.push_back(rates[i]);
		}

		for (Size i=0; i<yields.size()+1; ++i) {

			if (i<yields.size())
				yields[i] += 0.003;

			boost::shared_ptr<YieldTermStructure> rts1(new InterpolatedZeroCurve<Linear>(dates, yields, Actual365Fixed(), Linear()));
			boost::shared_ptr<IborIndex> index(new CD91(Handle<YieldTermStructure>(rts1)));
			index->addFixings(pastFixings);


			std::vector<Real> price = 
				cap_floor(todaysDate, CapFloor::Cap, strike, notional, schedule, 0, bdc, index, rts1, vol);


			std::vector<Real> price1 = 
				swaption(todaysDate, VanillaSwap::Payer, Settlement::Cash, strike, notional, 
				schedule2[0], schedule2, dayCounter, schedule2, dayCounter, 0, bdc, index, rts1, vol);

			std::cout.precision(8);	
			std::cout<<price[0]<<"  ";
			std::cout<<price1[0]<<" ";//std::endl;


			std::vector<Real> price2 = 
				interest_rate_swap(todaysDate, VanillaSwap::Receiver, notional, schedule, 0.03, Actual365Fixed(),
				schedule, index, 0.0005, Actual365Fixed(), rts1);
			std::cout.precision(8);	
			std::cout<<price2[0]<<"\n";

			if (i<yields.size())
				yields[i] -= 0.003;
		}

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