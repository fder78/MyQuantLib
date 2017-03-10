
#include <ql/quantlib.hpp>
#include <boost/timer.hpp>
#include <iostream>
#include <fstream>

#include "utilities.hpp"
#include <eq_derivatives\autocallable_engine\autocall_engine.h>
#include <eq_derivatives\autocallable_mc_engine\mc_autocall_engine.h>
#include <eq_derivatives\autocallable_instrument\autocallable_note.h>
#include <eq_derivatives\autocallable_instrument\general_payoff.h>
#include <eq_derivatives\autocallable_instrument\general_basket_payoff.h>

using namespace std;
using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {
	Integer sessionId() { return 0; }
}
#endif

void testEuroTwoValues() {


	DayCounter dc = Actual360();
	Date today0 = Date::todaysDate();
	std::ofstream fout("c:\\drivers\\els_prices.csv");

	for (Size iter = 0; iter < 20; ++iter) {
		boost::timer timer;
		Date effectiveDate(10, June, 2016);
		Settings::instance().evaluationDate() = effectiveDate + 3*Months;
		Date today = Settings::instance().evaluationDate();

		//Spec.
		Real notional = 10000;
		Real couponRate = 0.04;
		Real mat = 3;
		
		Date terminationDate = effectiveDate + mat * Years;
		Period tenor(6, Months);
		//Real redempBarrier[6] = { 90,90,85,85,80,70 };
		//Real KIredempBarrier[6] = { 90,90,85,85,80,70 };
		Real redempBarrier[6] = { 90,50,85,85,80,80 };
		Real KIredempBarrier[6] = { 90,90,85,85,80,80 };
		Real slopes[6] = { 4000,4000,4000,4000,4000,4000 };
		Real terminalSlope = 4000;

		Real kibarrier[2] = { 60, 60 };
		Real redPayoff = 100 * (1 + couponRate * mat);
		Real crossPoint1 = (kibarrier[0] * terminalSlope - redPayoff) / (terminalSlope - 1.0);
		Real crossPoint2 = (kibarrier[1] * terminalSlope - redPayoff) / (terminalSlope - 1.0);
		std::vector<Real> x1 = { 0, crossPoint1, kibarrier[0] };
		std::vector<Real> x2 = { 0, crossPoint2, kibarrier[1] };
		std::vector<Real> y1 = { 0, crossPoint1, redPayoff };
		std::vector<Real> y2 = { 0, crossPoint2, redPayoff };
		std::vector<Real> s = { 1.0, terminalSlope, 0.0 };
		boost::shared_ptr<Payoff> terPayoff1(new GeneralPayoff(x1, y1, s));
		boost::shared_ptr<Payoff> terPayoff2(new GeneralPayoff(x2, y2, s));
		std::vector<boost::shared_ptr<Payoff> > terPayoff;
		terPayoff.push_back(terPayoff1);
		terPayoff.push_back(terPayoff2);
		//terPayoff.push_back(terPayoff2);
		boost::shared_ptr<ArrayPayoff> minofpayoff(new MinOfPayoffs(terPayoff));
		boost::shared_ptr<BasketPayoff> terminalPayoff(new GeneralBasketPayoff(minofpayoff));

		std::vector<boost::shared_ptr<AutocallCondition> > autocallConditions, KIautocallConditions;
		std::vector<boost::shared_ptr<BasketPayoff> > autocallPayoffs, KIautocallPayoffs;
		Schedule exDate = Schedule(effectiveDate, terminationDate, tenor, SouthKorea(), Following, Following, DateGeneration::Forward, false);
		for (Size i = 0; i < exDate.size() - 1; ++i) {
			Real temp = redempBarrier[i];
			if (i == 5)
				temp = kibarrier[0];
			std::vector<Real> redBarriers(1, temp);
			redBarriers.push_back(temp); //TWO way
			//redBarriers.push_back(temp); //TWO way
			autocallConditions.push_back(boost::shared_ptr<AutocallCondition>(new MinUpCondition(redBarriers)));
			Real redpayoff = 100 * (1 + couponRate*(i + 1) / 2.0);
			std::vector<Real> x = { 0, temp - redpayoff / slopes[i], temp };
			std::vector<Real> y = { 0, 0, redpayoff };
			std::vector<Real> s = { 0, slopes[i], 0 };
			boost::shared_ptr<Payoff> payoff(new GeneralPayoff(x, y, s));
			autocallPayoffs.push_back(boost::shared_ptr<BasketPayoff>(new MinBasketPayoff(payoff)));

			std::vector<Real> KIredBarriers(1, KIredempBarrier[i]);
			KIredBarriers.push_back(KIredempBarrier[i]); //TWO way
			//redBarriers.push_back(KIredempBarrier[i]); //TWO way
			KIautocallConditions.push_back(boost::shared_ptr<AutocallCondition>(new MinUpCondition(KIredBarriers)));
			Real KIredpayoff = 100 * (1 + couponRate*(i + 1) / 2.0);
			std::vector<Real> KIx = { 0, KIredempBarrier[i] - KIredpayoff / slopes[i], KIredempBarrier[i] };
			std::vector<Real> KIy = { 0, 0, KIredpayoff };
			std::vector<Real> KIs = { 0, slopes[i], 0 };
			boost::shared_ptr<Payoff> KIpayoff(new GeneralPayoff(KIx, KIy, KIs));
			KIautocallPayoffs.push_back(boost::shared_ptr<BasketPayoff>(new MinBasketPayoff(KIpayoff)));
		}

		AutocallableNote autocallable(
			notional, //notional
			exDate, //exercise
			exDate, //payment
			autocallConditions,
			autocallPayoffs,
			terminalPayoff
			);


		//KI payoff
		Real kix[] = { 0, redempBarrier[5] };
		Real kiy[] = { 0, 100 * (1 + couponRate * mat) };
		Real kislope[] = { 1.0, 0.0 };
		boost::shared_ptr<Payoff> kiPayoff(new GeneralPayoff(std::vector<Real>(kix, kix + 2), std::vector<Real>(kiy, kiy + 2), std::vector<Real>(kislope, kislope + 2)));
		//boost::shared_ptr<BasketPayoff> KIPayoff(new MinBasketPayoff(kiPayoff));

		std::vector<boost::shared_ptr<Payoff> > kipayoffs(1, kiPayoff);
		kipayoffs.push_back(kiPayoff);
		boost::shared_ptr<ArrayPayoff> kipayoff(new MinOfPayoffs(kipayoffs));
		boost::shared_ptr<BasketPayoff> KIPayoff(new GeneralBasketPayoff(kipayoff));

		//two way KI 베리어를 다르게
		std::vector<Real> kib(1, kibarrier[0]);
		kib.push_back(kibarrier[1]);
		boost::shared_ptr<AutocallCondition> kiCondition(new MinDownCondition(kib));
		//autocallable.withKI(
		//	kiCondition, 
		//	KIautocallConditions,
		//	KIautocallPayoffs,
		//	KIPayoff);
		autocallable.withKI(kiCondition, KIPayoff);
		//autocallable.hasKnockedIn();
		

		////////////////////////////
		// Market Data
		////////////////////////////
		boost::shared_ptr<SimpleQuote> spot1(new SimpleQuote(0.0));
		boost::shared_ptr<SimpleQuote> spot2(new SimpleQuote(0.0));

		boost::shared_ptr<SimpleQuote> qRate1(new SimpleQuote(0.0));
		boost::shared_ptr<YieldTermStructure> qTS1 = flatRate(today, qRate1, dc);
		boost::shared_ptr<SimpleQuote> qRate2(new SimpleQuote(0.0));
		boost::shared_ptr<YieldTermStructure> qTS2 = flatRate(today, qRate2, dc);

		boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.0));
		boost::shared_ptr<YieldTermStructure> rTS = flatRate(today, rRate, dc);

		boost::shared_ptr<SimpleQuote> discRate(new SimpleQuote(0.0));
		boost::shared_ptr<YieldTermStructure> discTS = flatRate(today, discRate, dc);

		boost::shared_ptr<SimpleQuote> vol1(new SimpleQuote(0.0));
		boost::shared_ptr<BlackVolTermStructure> volTS1 = flatVol(today, vol1, dc);
		boost::shared_ptr<SimpleQuote> vol2(new SimpleQuote(0.0));
		boost::shared_ptr<BlackVolTermStructure> volTS2 = flatVol(today, vol2, dc);

		Real x = 100 - iter * 4;
		spot1->setValue(x);
		spot2->setValue(x);
		qRate1->setValue(0.01);
		qRate2->setValue(0.01);
		rRate->setValue(0.03);
		discRate->setValue(0.02);
		vol1->setValue(0.2);
		vol2->setValue(0.2);
		Real corr = 0.6;

		boost::shared_ptr<PricingEngine> analyticEngine;
		boost::shared_ptr<GeneralizedBlackScholesProcess> p1, p2;
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

		//boost::shared_ptr<PricingEngine> fdEngine(
		//	new FdAutocallEngine(discTS, p1, p2, corr, 100, 100, 50));


		//ProcessArray
		std::vector<boost::shared_ptr<StochasticProcess1D> > procs;
		procs.push_back(p1);
		procs.push_back(p2);
		//procs.push_back(p2);

		Matrix correlationMatrix(procs.size(), procs.size(), corr);
		for (Integer j = 0; j < procs.size(); j++) {
			correlationMatrix[j][j] = 1.0;
		}
		boost::shared_ptr<StochasticProcessArray> process(new StochasticProcessArray(procs, correlationMatrix));

		boost::shared_ptr<PricingEngine> fdEngine_new(new FdAutocallEngine(discTS, process, 200, 100));
		boost::shared_ptr<PricingEngine> mcEngine = MakeMCAutocallEngine<>(process, discTS)
			.withSteps(1)
			.withSamples(40000);


		std::cout << x << "\t";
		autocallable.setPricingEngine(mcEngine);
		Real mc = autocallable.NPV() * 100;
		Real se = autocallable.errorEstimate() * 100;
		std::cout << mc << "\t";
		// fd engine
		autocallable.setPricingEngine(fdEngine_new);
		Real fdm = autocallable.NPV();

		std::cout << fdm << "\t";
		//std::cout << "theta=" << autocallable.theta()[0] << std::endl;
		//for (Size i = 0; i < n; ++i) {
		//	std::cout << "delta[" << i + 1 << "]=" << autocallable.delta()[i] << "   ";
		//	std::cout << "gamma[" << i + 1 << "]=" << autocallable.gamma()[i] << std::endl;
		//}
		//std::cout << "xgamma=" << std::endl;
		//for (Size i = 0; i < n; ++i) {
		//	for (Size j = 0; j < n; ++j)
		//		std::cout <<  autocallable.xgamma()[i][j] << "   ";
		//	std::cout << std::endl;
		//}
		std::cout << timer.elapsed() << std::endl;
		//std::cout << std::string(30, '-') << std::endl;
		fout << x << "," << fdm << "," << mc << "," << se <<std::endl;
	}
	fout.close();
}



int main(int, char*[]) {
	try {
		boost::timer timer;
		testEuroTwoValues();
		std::cout << "time = " << timer.elapsed() << std::endl;
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
