#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>
#include <fstream>

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

		std::ofstream fout;
		fout.open("C:\\test.csv");
		boost::timer timer;

		Real a = 0.1;
		Real sigma = 0.005;
		std::vector<Date> dates;
		std::vector<Rate> yields;
		for (Size i=0; i<12; ++i) {
			dates.push_back(Date::todaysDate()+i*Years);
			yields.push_back(0.025 + sqrt(double(i))/200.);
		}
		Handle<YieldTermStructure> ts(new InterpolatedZeroCurve<Cubic>(dates, yields, Actual365Fixed()));
		HullWhite hw(ts, a, sigma);
		HullWhiteProcess process(ts, a, sigma);
		ZigguratRng rnd(128);
		Real rnum, rt, price, spotRate;
				
		for (Size i=0; i<=50; ++i) {
			Real t = i/10.0;			
			rnum = rnd.next().value;
			if (i==0)
				rt = process.x0();
			else
				rt = process.evolve(t-0.1, rt, 0.1, rnum);

			//for (Size j=0; j<=100; ++j) {
			//	Real mat = j/10.0;

			//	if (j>i) {
			//		price = hw.discountBond(t, mat, rt);
			//		spotRate = -1/(mat-t)*std::log(price); 
			//		fout<<spotRate<<",";
			//	} else if (j==i) {
			//		fout<<rt<<",";
			//	} else {
			//		fout<<",";
			//	}
			//}					
			//fout<<std::endl;

			Real annuity = 0.0, tau = 0.25;
			for (Size j=1; j<=20; ++j){
				annuity += tau* hw.discountBond(t, t+tau*j, rt);
			}
			Real cms = (1.0 - hw.discountBond(t, t+5, rt))/annuity;
						
			fout<< t<<", "<<rt<<","<<cms<< std::endl;

		}

		fout.close();
		return 0;

	} catch (std::exception& e) {

		std::cerr << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "unknown error" << std::endl;
		return 1;
	}

}

