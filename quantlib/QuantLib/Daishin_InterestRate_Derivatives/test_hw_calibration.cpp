#define hwCALIBRATION_
#ifdef hwCALIBRATION_

#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>
#include <ds_interestrate_derivatives/hw_calibration/hull_white_calibration.hpp>

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

		Real discRate = 0.028;
		Date today = Date(Date::todaysDate().serialNumber());
		Handle<YieldTermStructure> rts_hw = Handle<YieldTermStructure>(boost::shared_ptr<YieldTermStructure>(new FlatForward(today, discRate, Actual365Fixed())));		
		boost::shared_ptr<IborIndex> index(new Euribor3M(rts_hw));
		index->addFixing(Date(25,Jan,2013),discRate);

		std::vector<Size> tenor;
		std::vector<Rate> vol;
		//tenor.push_back(1); vol.push_back(0.1);
		//tenor.push_back(2); vol.push_back(0.1);
		//tenor.push_back(3); vol.push_back(0.1);
		//tenor.push_back(4); vol.push_back(0.1);
		//tenor.push_back(5); vol.push_back(0.1);

		tenor.push_back(1); vol.push_back(0.1399);
		tenor.push_back(2); vol.push_back(0.1558);
		tenor.push_back(3); vol.push_back(0.1683);
		tenor.push_back(4); vol.push_back(0.1733);
		tenor.push_back(5); vol.push_back(0.1765);
		tenor.push_back(7); vol.push_back(0.1730);
		tenor.push_back(10); vol.push_back(0.1675);
		//tenor.push_back(15); vol.push_back(0.1655);
		//tenor.push_back(20); vol.push_back(0.163);

		Real fixedA = 0.1;
		Frequency fixedFreq(Quarterly);
		DayCounter fixedDC = Actual365Fixed();

		HullWhiteTimeDependentParameters results0(fixedA, std::vector<Date>(), vol);
		Matrix price(tenor.size()+2, 4, 0.0);

		for (Size k=0; k<=tenor.size()+1; ++k) {
			if (k==tenor.size()+1){
				for (Size j=0; j<tenor.size(); ++j)
					vol[j] +=0.001;
			}
			else if (k>0)
				vol[k-1] += 0.001;

			CapVolData volData;
			volData.tenors = tenor;
			volData.vols = vol;

			HullWhiteTimeDependentParameters results = calibration_hull_white(today, index, volData, fixedFreq, fixedDC, fixedA, results0.sigma);

			std::cout<<"mean-reversion = "<<results.a<<std::endl;
			std::cout<<"Tenor,CapVol,Sigma,Market,Model\n";
			for (Size i=0; i<results.tenor.size(); ++i) {
				std::cout<<std::fixed;
				std::cout.precision(2);
				std::cout<<tenor[i]<<","<<vol[i]*100<<", ";
				std::cout.precision(5);
				std::cout<<results.sigma[i]<<", ";
				std::cout.precision(2);
				std::cout<<results.helpers[i]->marketValue()*10000;
				std::cout<<","<<results.helpers[i]->modelValue()*10000<<std::endl;
			}
			std::cout<<"------------------"<<std::endl;

			boost::shared_ptr<GeneralizedHullWhite> hwmodel = results.model;
			boost::shared_ptr<PricingEngine> engine(new TreeCallableFixedRateBondEngine(hwmodel, 100));

			Schedule schedule(today, today+5*Years, Period(6, Months), NullCalendar(), Unadjusted, Unadjusted, DateGeneration::Backward, false);
			CallabilitySchedule callSchedule;
			for (Size i=1; i<schedule.size(); ++i) {
				boost::shared_ptr<Callability> c(new Callability(
					Callability::Price(10000, Callability::Price::Clean), Callability::Call, schedule[i]));
				callSchedule.push_back(c);
			}
			CallableFixedRateBond bond1(0, 10000, schedule, std::vector<Rate>(1, 0.025), SimpleDayCounter(), Unadjusted, 100, Date(), callSchedule);
			CallableFixedRateBond bond2(0, 10000, schedule, std::vector<Rate>(1, 0.030), SimpleDayCounter(), Unadjusted, 100, Date(), callSchedule);
			CallableFixedRateBond bond3(0, 10000, schedule, std::vector<Rate>(1, 0.035), SimpleDayCounter(), Unadjusted, 100, Date(), callSchedule);
			CallableFixedRateBond bond4(0, 10000, schedule, std::vector<Rate>(1, 0.04), SimpleDayCounter(), Unadjusted, 100, Date(), callSchedule);
			bond1.setPricingEngine(engine);
			bond2.setPricingEngine(engine);
			bond3.setPricingEngine(engine);
			bond4.setPricingEngine(engine);

			price[k][0] = bond1.NPV();
			price[k][1] = bond2.NPV();
			price[k][2] = bond3.NPV();
			price[k][3] = bond4.NPV();

			if (k==0)
				results0 = results;

			if (k>0 && k<=tenor.size())
				vol[k-1] -= 0.001;
		}
		for (Size k=0; k<=tenor.size()+1; ++k) {
			for (Size i=0; i<4; ++i) {
				std::cout<<price[k][i]<<"  ";
			}
			std::cout<<std::endl;
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