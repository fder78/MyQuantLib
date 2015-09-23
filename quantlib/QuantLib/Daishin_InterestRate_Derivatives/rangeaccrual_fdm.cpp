#define testtesttesttest
#ifdef testtesttesttest

#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>
#include <ds_interestrate_derivatives/hw_calibration/hull_white_calibration.hpp>
#include <ds_interestrate_derivatives/pricingengine/fdm_engine/fdm_ra_engine_ghw.hpp>

#include "dual_rangeaccrual.hpp"
#include "dual_rangeaccrual_swap.hpp"
#include "range_accrual_note_tree.hpp"

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

void range_accrual_fdm() {
	Date todaysDate = Date::todaysDate();
	Date startDate(todaysDate);
	Integer mat = 10;
	Date termDate(startDate + mat*Years);
	Schedule schedule(startDate, termDate, Period(Quarterly), NullCalendar(), Unadjusted, Unadjusted, DateGeneration::Backward, false);
	Schedule callSchedule(startDate+1*Years, termDate, Period(Quarterly), NullCalendar(), Unadjusted, Unadjusted, DateGeneration::Backward, false);
	//callSchedule = Schedule(std::vector<Date>(1, startDate + mat*Years));
	Schedule floatingSchedule(startDate, termDate, Period(Quarterly), NullCalendar(), Unadjusted, Unadjusted, DateGeneration::Backward, false);

	Real notional = 10000;
	std::vector<Real> couponRate;
	couponRate.push_back(0.043);
	std::vector<Real> lowerBound;
	std::vector<Real> upperBound;
	lowerBound.push_back(0.02); 
	upperBound.push_back(0.04); 

	Date firstCallDate = startDate + 1*Years;
	DayCounter dayCounter = SimpleDayCounter();
	BusinessDayConvention bdc = Following;

	Real pastAccrual = (todaysDate-startDate)/365.0;
	Real alpha = 0.0012;
	Rate floatingFixingRate = 0.03;
	////////////////////////////////////////////////////////////////////////////

	Real discRate = 0.03;
	Date today = todaysDate;//Date(Date::todaysDate().serialNumber());
	Handle<YieldTermStructure> rts_hw = Handle<YieldTermStructure>(boost::shared_ptr<YieldTermStructure>(new FlatForward(today, discRate, SimpleDayCounter())));		
	boost::shared_ptr<IborIndex> index(new Euribor3M(rts_hw));

	std::vector<Size> tenor;
	std::vector<Rate> vol;
	tenor.push_back(1); vol.push_back(0.16);
	tenor.push_back(2); vol.push_back(0.16);
	tenor.push_back(3); vol.push_back(0.16);
	tenor.push_back(4); vol.push_back(0.16);
	tenor.push_back(5); vol.push_back(0.16);
	tenor.push_back(7); vol.push_back(0.16);
	tenor.push_back(10); vol.push_back(0.16);

	std::vector<Period> maturity;
	std::vector<Period> length;
	std::vector<Rate> swaptionVol;
	maturity.push_back(Period(6, Months)); length.push_back(Period(2, Years)); swaptionVol.push_back(0.176155);
	maturity.push_back(Period(1, Years)); length.push_back(Period(2, Years)); swaptionVol.push_back(0.181483);
	maturity.push_back(Period(18, Months)); length.push_back(Period(1, Years)); swaptionVol.push_back(0.186488);
	maturity.push_back(Period(2, Years)); length.push_back(Period(1, Years)); swaptionVol.push_back(0.190012);

	Real fixedA = 0.03;
	Frequency fixedFreq(Quarterly);
	DayCounter fixedDC = Actual365Fixed();

	HullWhiteTimeDependentParameters results0(fixedA, std::vector<Date>(), swaptionVol);
	Matrix prices(maturity.size()+2, 10, 0.0);

	//for (Size k=0; k<=maturity.size()+1; ++k) {
	//	if (k==maturity.size()+1){
	//		for (Size j=0; j<maturity.size(); ++j)
	//			swaptionVol[j] +=0.01;
	//	}
	//	else if (k>0)
	//		swaptionVol[k-1] += 0.01;

		SwaptionVolData volData;
		volData.maturities = maturity;
		volData.lengths = length;
		volData.vols = swaptionVol;
		/*
		HullWhiteTimeDependentParameters results = calibration_hull_white(today, index, volData, fixedFreq, fixedDC, fixedDC, fixedA, results0.sigma);

		std::cout<<"mean-reversion = "<<results.a<<std::endl;
		std::cout<<"Maturity,Tenor,MktVol,Sigma,Market,Model\n";
		for (Size i=0; i<results.tenor.size(); ++i) {
			std::cout<<std::fixed;
			std::cout.precision(2);
			std::cout<<maturity[i]<<","<<length[i]<<","<<swaptionVol[i]*100<<", ";
			std::cout.precision(5);
			std::cout<<results.sigma[i]<<", ";
			std::cout.precision(2);
			std::cout<<results.helpers[i]->marketValue()*10000;
			std::cout<<","<<results.helpers[i]->modelValue()*10000<<std::endl;
		}
		std::cout<<"------------------"<<std::endl;

		boost::shared_ptr<GeneralizedHullWhite> hwmodel = results.model;
		boost::shared_ptr<YieldTermStructure> discCurve(new FlatForward(todaysDate, 0.032, SimpleDayCounter()));
		*/


		///////////////////////////////////////////////////////////////////
		Real a = 0.03;
		Real sigma = 0.01;
		Real corr = 0.6;

		std::vector<Date> dates;
		std::vector<Real> yields;
		dates.push_back(today+	0	*Days);	yields.push_back(	0.001485	);
		dates.push_back(today+	1	*Days);	yields.push_back(	0.001485	);
		dates.push_back(today+	7	*Days);	yields.push_back(	0.001677	);
		dates.push_back(today+	14	*Days);	yields.push_back(	0.001799	);
		dates.push_back(today+	30	*Days);	yields.push_back(	0.001992	);
		dates.push_back(today+	90	*Days);	yields.push_back(	0.002751	);
		dates.push_back(today+	1460	*Days);	yields.push_back(	0.00674	);
		dates.push_back(today+	1825	*Days);	yields.push_back(	0.00905	);
		dates.push_back(today+	2190	*Days);	yields.push_back(	0.011495	);
		dates.push_back(today+	2555	*Days);	yields.push_back(	0.01385	);
		dates.push_back(today+	2920	*Days);	yields.push_back(	0.01596	);
		dates.push_back(today+	3285	*Days);	yields.push_back(	0.01784	);
		dates.push_back(today+	3650	*Days);	yields.push_back(	0.01951	);
		dates.push_back(today+	4015	*Days);	yields.push_back(	0.020975	);
		dates.push_back(today+	4380	*Days);	yields.push_back(	0.02227	);
		dates.push_back(today+	5475	*Days);	yields.push_back(	0.02503	);
		dates.push_back(today+	7300	*Days);	yields.push_back(	0.02744	);
		dates.push_back(today+	9125	*Days);	yields.push_back(	0.02862	);
		dates.push_back(today+	10950	*Days);	yields.push_back(	0.02928	);
		dates.push_back(today+	14600	*Days);	yields.push_back(	0.02959	);

		Handle<YieldTermStructure> rts_hw1 = Handle<YieldTermStructure>(boost::shared_ptr<YieldTermStructure>(new 
			InterpolatedZeroCurve<Linear>(dates, yields, SimpleDayCounter())));
		

		boost::shared_ptr<HullWhiteProcess> hw0(new HullWhiteProcess(rts_hw, 0.0001, 0.008));
		boost::shared_ptr<HullWhiteProcess> hw1(new HullWhiteProcess(rts_hw1, 0.00000007, 0.00292926));
		boost::shared_ptr<PricingEngine> engine(new Fdm_R2_Dual_RA_Engine(hw0, hw1, corr, 0, 40, 40, 40));
		
		Real faceAmount = 10000;
		CallabilitySchedule callabilitySchedule;
		for (Size i=0; i<callSchedule.size(); ++i) {
			boost::shared_ptr<Callability> callability(new Callability(Callability::Price(faceAmount, Callability::Price::Clean), Callability::Call, callSchedule[i]));				
			callabilitySchedule.push_back(callability);
		}

		RangeAccrualNote note(0, faceAmount, schedule, index, index, index, SimpleDayCounter(), Unadjusted, 0, 
			std::vector<Real>(1, 0.0), std::vector<Spread>(1, 0.045), 
			std::vector<Rate>(12, 0.0), std::vector<Rate>(12, 0.045),
			std::vector<Rate>(12, 0.0), std::vector<Rate>(12, 0.045), 
			Period(1,Days), Unadjusted, 100.0, Date(), callabilitySchedule);

		note.setPricingEngine(engine);

		//std::cout<<note.NPV()<<std::endl;

		
		boost::shared_ptr<HullWhiteProcess> hw00(new HullWhiteProcess(rts_hw, a, sigma));
		boost::shared_ptr<HullWhiteProcess> hw10(new HullWhiteProcess(rts_hw1, a, sigma));
		std::vector<Real> rst = dual_rangeaccrual_fdm(todaysDate, faceAmount, 0.05, schedule, SimpleDayCounter(), Unadjusted,
			std::vector<Real>(2, 0.0), std::vector<Real>(2, 0.04), callSchedule[0], 0, hw0, hw1, corr, 80, 80);
		std::cout<<rst[0]<<std::endl;

		//boost::shared_ptr<HullWhiteProcess> hw01(new HullWhiteProcess(rts_hw1, a, sigma));
		//boost::shared_ptr<HullWhiteProcess> hw11(new HullWhiteProcess(rts_hw1, a, sigma));
		//rst = dual_rangeaccrual_fdm(todaysDate, faceAmount, 0.05, schedule, SimpleDayCounter(), Unadjusted,
		//	std::vector<Real>(2, 0.0), std::vector<Real>(2, 0.04), callSchedule[0], 0, hw01, hw11, corr, 80, 80);
		//std::cout<<rst[0]<<std::endl;

		//boost::shared_ptr<HullWhiteProcess> hw02(new HullWhiteProcess(rts_hw, a, sigma*1.1));
		//boost::shared_ptr<HullWhiteProcess> hw12(new HullWhiteProcess(rts_hw, a, sigma*1.1));
		//rst = dual_rangeaccrual_fdm(todaysDate, faceAmount, 0.05, schedule, SimpleDayCounter(), Unadjusted,
		//	std::vector<Real>(2, 0.0), std::vector<Real>(2, 0.04), callSchedule[0], 0, hw02, hw12, corr, 80, 80);
		//std::cout<<rst[0]<<std::endl;

		//boost::shared_ptr<HullWhiteProcess> hw03(new HullWhiteProcess(rts_hw1, a, sigma*1.1));
		//boost::shared_ptr<HullWhiteProcess> hw13(new HullWhiteProcess(rts_hw1, a, sigma*1.1));
		//rst = dual_rangeaccrual_fdm(todaysDate, faceAmount, 0.05, schedule, SimpleDayCounter(), Unadjusted,
		//	std::vector<Real>(2, 0.0), std::vector<Real>(2, 0.04), callSchedule[0], 0, hw03, hw13, corr, 80, 80);
		//std::cout<<rst[0]<<std::endl;

		//for (Size h=0; h<10; ++h) {

		//	lowerBound[0] = 0.02 + h*0.002/2;
		//	upperBound[0] = 0.04 - h*0.002/2;

		//	std::vector<Real> price = single_rangeaccrual(todaysDate,
		//		notional, couponRate, schedule,	dayCounter, bdc,
		//		lowerBound, upperBound, callSchedule,
		//		pastAccrual, rts_hw.currentLink(), results, discCurve, 200);

		//	prices[k][h] = price[0];
		//}

	//	if (k==0)
	//		results0 = results;

	//	if (k>0 && k<=maturity.size())
	//		swaptionVol[k-1] -= 0.01;
	//}

	//for (Size i=0; i<10; ++i) {
	//	for (Size k=0; k<=maturity.size()+1; ++k) {			
	//		std::cout<<prices[k][i]<<",";
	//	}
	//	std::cout<<std::endl;
	//}
}


int main() {

	try {

		boost::timer timer;
		range_accrual_fdm();
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