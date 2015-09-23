#ifdef nlaiskdhg

#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>


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
		Size n = 5000;

		for (Size iter=0; iter<100; ++iter) {
		Matrix delta(n,1,1.0);
		Matrix cov(n,n,1.0);
		Matrix gamma(n,n,1.0);

		Matrix temp(n,n,0);
		for (Size i=0; i<n; ++i) {
			for (Size j=0; j<n; ++j) {
				temp[i][j] = gamma[i][i] * cov[i][j];
			}
		}

		Real tr1 = 0.0;
		for (Size i=0; i<n; ++i)
			tr1 += temp[i][i];

		Real tr2 = 0.0;
		for (Size i=0; i<n; ++i){
			for (Size j=0; j<n; ++j) {
				tr2 += temp[i][j] * temp[j][i];
			}
		}
		
		Matrix test = transpose(delta)*cov*delta;

		Real mu = tr1/2.0;
		Real sigma = std::sqrt(test[0][0] + tr2/2.0);

		std::cout<<iter<<"  "<<mu<<"  "
			<<sigma<<"  "			
			<<std::endl;
		}
		//for (Size iter=0; iter<10; ++iter) {
		//	std::vector<Real> w(5000, 1.);
		//	std::vector<std::vector<Real> > cov(5000, std::vector<Real>(5000, 1.));
		//	std::vector<std::vector<Real> > gamma(5000, std::vector<Real>(5000, 1.));
		//	std::vector<Real> temp(5000, 0.);
		//	Real value = 0.;

		//	for (Size i=0; i<5000; ++i){
		//		for (Size j=0; j<5000; ++j) {
		//			temp[i] += cov[i][j] * w[j];
		//		}
		//		value += temp[i] * w[i];
		//	}

		//	for (Size i=0; i<5000; ++i){
		//		for (Size j=0; j<5000; ++j) {
		//			Real z = 0.0;
		//			for (Size k=0; k<5000; ++k) {

		//			}
		//			[i][j] = 
		//		}
		//	}





		//	std::cout<<value<<std::endl;
		//}

		std::cout<<timer.elapsed()<<std::endl;

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