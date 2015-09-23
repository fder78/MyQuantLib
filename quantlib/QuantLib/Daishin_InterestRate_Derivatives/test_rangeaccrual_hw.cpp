#define testtesttesttest
#ifdef testtesttesttest

#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>
#include <ds_interestrate_derivatives/hw_calibration/hull_white_calibration.hpp>
#include <ds_interestrate_derivatives/model/generalized_hullwhite.hpp>

#include <ds_interestrate_derivatives/hw_calibration/g2_calibration.hpp>
#include <ql/models/shortrate/twofactormodels/g2.hpp>

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

void range_accrual_tree() {

	for (Size h=0; h<=40; ++h) {

	Date todaysDate = Date::todaysDate() + h*Days;
	Date startDate(Date::todaysDate());
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
	lowerBound.push_back(0); 
	upperBound.push_back(0.045); 
	lowerBound.push_back(-3); 
	upperBound.push_back(10); 

	DayCounter dayCounter = SimpleDayCounter();
	BusinessDayConvention bdc = Following;

	Real pastAccrual = 0;
	Real alpha = 0.0012;
	Rate floatingFixingRate = 0.03;
	////////////////////////////////////////////////////////////////////////////

	Real discRate = 0.028;
	Date today = Date(todaysDate.serialNumber());
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
	std::vector<Date> maturityDate;
	std::vector<Period> length;
	std::vector<Rate> swaptionVol;
	maturity.push_back(Period(12, Months)); length.push_back(Period(2, Years)); swaptionVol.push_back(0.176155/30.0); maturityDate.push_back(todaysDate + Period(6, Months));
	maturity.push_back(Period(2, Years)); length.push_back(Period(2, Years)); swaptionVol.push_back(0.181483/30.0); maturityDate.push_back(todaysDate + Period(12, Months));
	maturity.push_back(Period(36, Months)); length.push_back(Period(1, Years)); swaptionVol.push_back(0.186488/30.0); maturityDate.push_back(todaysDate + Period(18, Months));
	maturity.push_back(Period(36, Months)); length.push_back(Period(2, Years)); swaptionVol.push_back(0.186488/30.0); maturityDate.push_back(todaysDate + Period(18, Months));
	maturity.push_back(Period(5, Years)); length.push_back(Period(1, Years)); swaptionVol.push_back(0.190012/30.0); maturityDate.push_back(todaysDate + Period(600, Months));

	Real fixedA = 0.03;
	Frequency fixedFreq(Quarterly);
	DayCounter fixedDC = Actual365Fixed();


	SwaptionVolData volData;
	volData.maturities = maturity;
	volData.lengths = length;
	volData.vols = swaptionVol;
	volData.fixedFreq = fixedFreq;
	volData.fixedDC = fixedDC;
	volData.floatingDC = fixedDC;
	volData.index = index;
	volData.fixedA = 0.03;
	volData.initialSigma = std::vector<Real>(swaptionVol.size(), 0.005);
	
	HullWhiteTimeDependentParameters rst = calibration_hull_white(today, volData);	

	G2Parameters rstG2 = calibration_g2(today, volData);


	std::vector<Real> rstSigma = rst.sigma;
	//for (Size i=0; i<swaptionVol.size(); ++i){
	//	std::cout<<swaptionVol[i]<<"  "<<rstSigma[i]<<"  ";
	//	std::cout<<rst.helpers[i]->marketValue()*10000<<"  ";
	//	std::cout<<rst.helpers[i]->modelValue()*10000<<std::endl;
	//}
	
	
	HullWhiteTimeDependentParameters results0(fixedA, std::vector<Date>(), vol);
	Matrix prices(maturity.size()+2, 10, 0.0);

	std::cout.precision(10);

	for (Size k=0; k<1; ++k) {

		if (k==maturity.size()+1){
			for (Size j=0; j<maturity.size(); ++j)
				swaptionVol[j] +=0.01;
		}
		else if (k>0)
			swaptionVol[k-1] += 0.01;

		SwaptionVolData volData;
		volData.maturities = maturity;
		volData.lengths = length;
		volData.vols = swaptionVol;
		volData.fixedFreq = fixedFreq;
		volData.fixedDC = fixedDC;
		volData.floatingDC = fixedDC;
		volData.index = index;
		volData.fixedA = fixedA;
		volData.initialSigma = results0.sigma;

		//HullWhiteTimeDependentParameters results = calibration_hull_white(today, volData);
		HullWhiteTimeDependentParameters results(fixedA, maturityDate, swaptionVol,
			boost::shared_ptr<Generalized_HullWhite>(new 
			Generalized_HullWhite(rts_hw, maturityDate, swaptionVol, fixedA)));

		//std::cout<<"mean-reversion = "<<results.a<<std::endl;
		//std::cout<<"Maturity,Tenor,MktVol,Sigma,Market,Model\n";
		//for (Size i=0; i<results.tenor.size(); ++i) {
		//	std::cout<<std::fixed;
		//	std::cout.precision(2);
		//	std::cout<<maturity[i]<<","<<length[i]<<","<<swaptionVol[i]*100<<", ";
		//	std::cout.precision(5);
		//	std::cout<<results.sigma[i]<<", ";
		//	std::cout.precision(2);
		//	std::cout<<results.helpers[i]->marketValue()*10000;
		//	std::cout<<","<<results.helpers[i]->modelValue()*10000<<std::endl;
		//}
		//std::cout<<"------------------"<<std::endl;

		boost::shared_ptr<Generalized_HullWhite> hwmodel = results.model;
		boost::shared_ptr<YieldTermStructure> discCurve(new FlatForward(todaysDate, 0.028, SimpleDayCounter()));


			//upperBound[0] = 0.01 + 0.001*h;
			boost::timer timer;
			//std::vector<Real> price1 = single_rangeaccrual(todaysDate,
			//			notional, couponRate, std::vector<Real>(QL_MIN_POSITIVE_REAL), schedule,	dayCounter, bdc,
			//			std::vector<Real>(1,lowerBound[0]), std::vector<Real>(1,upperBound[0]), callSchedule,
			//			1/*pastAccrual*/, rts_hw.currentLink(), results, discCurve, 200, 
			//			0.0, -1, 0.05, 0.1, 0.0, 
			//			0.001, 0.025);

			//std::cout<<upperBound[0]<<"  "<<price1[0]<<"  ";
			////std::cout<<timer.elapsed()<<std::endl;
			//timer.restart();
			std::vector<Matrix> m = std::vector<Matrix>(1, Matrix(2,2,1));
			m[0][1][0] = m[0][1][1] = 0.0;
			m[0][0][1] = -1.0;
			std::vector<Matrix> tenor = std::vector<Matrix>(1, Matrix(2,2,5));

			std::vector<Real> price = dual_rangeaccrual_fdm(todaysDate, notional, couponRate, std::vector<Real>(QL_MIN_POSITIVE_REAL), schedule, dayCounter, bdc,
				std::vector<Real>(1, 0.0), std::vector<Real>(1, 0.1), std::vector<Real>(1, 0.0), std::vector<Real>(1, 0.1), callSchedule[0], 0,/*pastAccrual*/
				rts_hw.currentLink(), results, 0, 0, rts_hw.currentLink(), results, 0, 0, Handle<YieldTermStructure>(discCurve), 0.5, 50, 50, 
				0.0, -1, 0.05, 0.1, 0.0, 
				0.001, 0.025, m, tenor);

			std::cout<<price[0]<<std::endl;
			//std::cout<<timer.elapsed()<<std::endl;
		}
	}
}


int main() {

	try {

		boost::timer timer;
		range_accrual_tree();
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