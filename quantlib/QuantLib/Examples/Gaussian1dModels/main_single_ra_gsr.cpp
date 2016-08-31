
#include <ql/quantlib.hpp>
#include <boost/timer.hpp>
#include "gaussian1d_ffswap_engine.hpp"

using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {
	Integer sessionId() { return 0; }
}
#endif

// helper function that prints a basket of calibrating swaptions to std::cout

void printBasket(
	const std::vector<boost::shared_ptr<CalibrationHelper> > &basket) {
	std::cout << "\n" << std::left << std::setw(20) << "Expiry" << std::setw(20)
		<< "Maturity" << std::setw(20) << "Nominal" << std::setw(14)
		<< "Rate" << std::setw(12) << "Pay/Rec" << std::setw(14)
		<< "Market ivol" << std::fixed << std::setprecision(6)
		<< std::endl;
	std::cout << "==================================================================================================" << std::endl;
	for (Size j = 0; j < basket.size(); ++j) {
		boost::shared_ptr<SwaptionHelper> helper =
			boost::dynamic_pointer_cast<SwaptionHelper>(basket[j]);
		Date endDate = helper->underlyingSwap()->fixedSchedule().dates().back();
		Real nominal = helper->underlyingSwap()->nominal();
		Real vol = helper->volatility()->value();
		Real rate = helper->underlyingSwap()->fixedRate();
		Date expiry = helper->swaption()->exercise()->date(0);
		VanillaSwap::Type type = helper->swaption()->type();
		std::ostringstream expiryString, endDateString;
		expiryString << expiry;
		endDateString << endDate;
		std::cout << std::setw(20) << expiryString.str() << std::setw(20)
			<< endDateString.str() << std::setw(20) << nominal
			<< std::setw(14) << rate << std::setw(12)
			<< (type == VanillaSwap::Payer ? "Payer" : "Receiver")
			<< std::setw(14) << vol << std::endl;
	}
}

// helper function that prints the result of a model calibraiton to std::cout

void printModelCalibration(
	const std::vector<boost::shared_ptr<CalibrationHelper> > &basket,
	const Array &volatility) {

	std::cout << "\n" << std::left << std::setw(20) << "Expiry" << std::setw(14)
		<< "Model sigma" << std::setw(20) << "Model price"
		<< std::setw(20) << "market price" << std::setw(14)
		<< "Model ivol" << std::setw(14) << "Market ivol" << std::fixed
		<< std::setprecision(6) << std::endl;
	std::cout << "==================================================================================================" << std::endl;

	for (Size j = 0; j < basket.size(); ++j) {
		boost::shared_ptr<SwaptionHelper> helper =
			boost::dynamic_pointer_cast<SwaptionHelper>(basket[j]);
		Date expiry = helper->swaption()->exercise()->date(0);
		std::ostringstream expiryString;
		expiryString << expiry;
		std::cout << std::setw(20) << expiryString.str() << std::setw(14)
			<< volatility[j] << std::setw(20) << basket[j]->modelValue()
			<< std::setw(20) << basket[j]->marketValue() << std::setw(14)
			<< basket[j]->impliedVolatility(basket[j]->modelValue(), 1E-6,
				1000, 0.0, 2.0)
			<< std::setw(14) << basket[j]->volatility()->value()
			<< std::endl;
	}
	if (volatility.size() > basket.size()) // only for markov model
		std::cout << std::setw(20) << " " << volatility.back() << std::endl;
}

// helper function that prints timing information to std::cout

class Timer {
	boost::timer timer_;
	double elapsed_;

public:
	void start() { timer_ = boost::timer(); }
	void stop() { elapsed_ = timer_.elapsed(); }
	double elapsed() const { return elapsed_; }
};

void printTiming(const Timer &timer) {
	double seconds = timer.elapsed();
	std::cout << std::fixed << std::setprecision(1) << "\n(this step took "
		<< seconds << "s)" << std::endl;
}

// here the main part of the code starts

int main(int argc, char *argv[]) {

	try {

		std::cout << "\nGaussian1dModel Examples" << std::endl;

		Timer timer;

		Date refDate(30, April, 2014);
		Settings::instance().evaluationDate() = refDate;// -3 * Years;

		std::cout << "\nThe evaluation date = " << Settings::instance().evaluationDate() << std::endl;


		//CURVES
		Real forward6mLevel = 0.025;
		Real oisLevel = 0.02;

		Handle<Quote> forward6mQuote(boost::make_shared<SimpleQuote>(forward6mLevel));
		Handle<Quote> oisQuote(boost::make_shared<SimpleQuote>(oisLevel));

		Handle<YieldTermStructure> yts6m(boost::make_shared<FlatForward>(0, TARGET(), forward6mQuote, Actual365Fixed()));
		Handle<YieldTermStructure> ytsOis(boost::make_shared<FlatForward>(0, TARGET(), oisQuote, Actual365Fixed()));

		boost::shared_ptr<IborIndex> euribor6m = boost::make_shared<Euribor>(6 * Months, yts6m);

		std::cout << "\nThe discounting curve = " << oisLevel
			<< "\nThe forwarding curve = Euribior 6m curve @ " << forward6mLevel << std::endl;

		//SWAPTION VOL 
		Real volLevel = 0.20;
		Handle<Quote> volQuote(boost::make_shared<SimpleQuote>(volLevel));
		Handle<SwaptionVolatilityStructure> swaptionVol(boost::make_shared<ConstantSwaptionVolatility>(0, TARGET(), ModifiedFollowing, volQuote, Actual365Fixed()));

		std::cout << "The volatility = " << volLevel << std::endl;

		//BERMUDAN SWAPTION SPEC
		//Real strike = 0.025;
		//std::cout << "\nWe consider a standard 10y bermudan payer swaption with yearly exercises at a strike of " << strike << std::endl;

		Date effectiveDate = TARGET().advance(refDate, 2 * Days);
		Date maturityDate = TARGET().advance(effectiveDate, 10 * Years);

		Schedule fixedSchedule(effectiveDate, maturityDate, 1 * Years, TARGET(), ModifiedFollowing, ModifiedFollowing, DateGeneration::Forward, false);
		Schedule floatingSchedule(effectiveDate, maturityDate, 6 * Months, TARGET(), ModifiedFollowing, ModifiedFollowing, DateGeneration::Forward, false);

		std::vector<Date> exerciseDates;
		for (Size i = 1; i < 10; ++i)
			exerciseDates.push_back(TARGET().advance(fixedSchedule[i], -2 * Days));
		boost::shared_ptr<Exercise> exercise = boost::make_shared<BermudanExercise>(exerciseDates, false);

		//GSR MODEL SPECIFICATION
		std::vector<Date> stepDates(exerciseDates.begin(), exerciseDates.end() - 1);
		std::vector<Real> sigmas(stepDates.size() + 1, 0.01);
		Real reversion = 0.01;
		boost::shared_ptr<Gsr> gsr = boost::make_shared<Gsr>(yts6m, stepDates, sigmas, reversion);

		//CALIBRATION BASKET
		boost::shared_ptr<PricingEngine> swaptionEngine = boost::make_shared<Gaussian1dSwaptionEngine>(gsr, 64, 7.0, true, false, ytsOis);
		boost::shared_ptr<SwapIndex> swapIndex = boost::make_shared<EuriborSwapIsdaFixA>(10 * Years, yts6m, ytsOis);

		Rate fixedRate = 0.06;
		std::pair<Real, Real> indexRange(-1.5, 1.5);
		boost::shared_ptr<FloatFloatSwap> underlying4(new RAFloatSwap(
			VanillaSwap::Receiver, 10000.0, 10000.0,
			fixedSchedule, fixedRate, swapIndex, indexRange, Thirty360(),
			floatingSchedule, euribor6m, Actual360(),
			false, false, 1.0, 0.0, Null<Real>(), Null<Real>(), 0.0, 0.00));

		boost::shared_ptr<FloatFloatSwaption> swaption4 = boost::make_shared<FloatFloatSwaption>(underlying4, exercise);

		boost::shared_ptr<G1d_FFSwap_Engine> floatSwaptionEngine(new G1d_FFSwap_Engine(gsr, 64, 7.0, true, false, Handle<Quote>(), ytsOis, true));

		swaption4->setPricingEngine(floatSwaptionEngine);

		std::cout << "\nWe generate a naive calibration basket and calibrate the GSR model to it:" << std::endl;

		timer.start();
		std::vector<boost::shared_ptr<CalibrationHelper> > basket = swaption4->calibrationBasket(swapIndex, *swaptionVol, BasketGeneratingEngine::Naive);
		for (Size i = 0; i < basket.size(); ++i)
			basket[i]->setPricingEngine(swaptionEngine);

		LevenbergMarquardt method;
		EndCriteria ec(1000, 10, 1E-8, 1E-8, 1E-8);
		//gsr->calibrateVolatilitiesIterative(basket, method, ec);
		timer.stop();

		printBasket(basket);
		//printModelCalibration(basket, gsr->volatility());
		printTiming(timer);

		timer.start();
		Real optionValue = swaption4->NPV();
		Real swapValue = (-1.0)*swaption4->result<Real>("underlyingValue");
		timer.stop();

		std::cout << "\nSwaption NPV (option value) = " << std::setprecision(6) << optionValue << std::endl;
		std::cout << "RA swap NPV (non-call) = " << std::setprecision(6) << swapValue << std::endl;
		std::cout << "RA swap NPV (Total Value) = " << std::setprecision(6) << optionValue + swapValue << std::endl;
		printTiming(timer);
	}
	catch (QuantLib::Error e) {
		std::cout << "terminated with a ql exception: " << e.what()
			<< std::endl;
		return 1;
	}
	catch (std::exception e) {
		std::cout << "terminated with a general exception: " << e.what()
			<< std::endl;
		return 1;
	}
}
