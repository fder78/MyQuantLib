
//#define testtesttesttest
#ifdef testtesttesttest

#include <ql/quantlib.hpp>
#include <iostream>
#include <boost/timer.hpp>

#include <ds_interestrate_derivatives/instruments/notes/fixedrate_cpn_bond.hpp>
#include <ds_interestrate_derivatives/pricingengine/tree_engine/tree_callable_bond_engine.hpp>
#include <ds_interestrate_derivatives/instruments/notes/range_accrual_note.hpp>

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

		Date today = Date::todaysDate();
		Schedule schedule(today, today+10*Years, Period(Quarterly), NullCalendar(), Unadjusted, Unadjusted, DateGeneration::Forward, false);
		//Schedule schedule2(today, today+3*Years, Period(Quarterly), NullCalendar(), Unadjusted, Unadjusted, DateGeneration::Forward, false);
		Rate cpnRate = 0.06;

		CallabilitySchedule callSchedule;
		for (Size i=1; i<schedule.size()-1; ++i) {
			boost::shared_ptr<Callability> callability(new 
				Callability(Callability::Price(10000, Callability::Price::Dirty), Callability::Call, schedule[i]));
			callSchedule.push_back(callability);
		}
		//CallableFixedRateBond bond(0, 10000, schedule, std::vector<Real>(1, cpnRate), SimpleDayCounter(), Unadjusted, 100.0, Date(), callSchedule);
		//FixedRateBond fbond(0, 10000, schedule2, std::vector<Real>(1,cpnRate), SimpleDayCounter(), Unadjusted);

		FixedRateCpnBond bond(0, 10000, schedule, std::vector<Rate>(1, cpnRate), SimpleDayCounter(), Unadjusted, 100.0, Date(), callSchedule);

		Rate yield = 0.05;
		boost::shared_ptr<YieldTermStructure> ts(new FlatForward(0, NullCalendar(), yield, SimpleDayCounter()));
		boost::shared_ptr<ShortRateModel> model(new HullWhite(Handle<YieldTermStructure>(ts), 0.1, 0.01));
		boost::shared_ptr<PricingEngine> engine(new HwTreeCallableBondEngine(model, 500, Handle<YieldTermStructure>(ts)));
		bond.setPricingEngine(engine);

		Real price = bond.NPV();
		std::cout<<"Price = "<<price<<std::endl;
		std::cout<<"Time = "<<timer.elapsed()<<std::endl;

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


#include <iostream>
#include <ql/quantlib.hpp>

using namespace QuantLib;

namespace QuantLib
{
	int sessionId()	{		return 0;	}
	void __Lock::AchieveLock( )	{	}
	void __Lock::ReleaseLock()	{	}
}

void swaption(Real stk){
	std::cout<<"Swaption Test " <<std::endl;


	Date evalDate =  Date(30, May, 2013);
	Date startDate = Date(30,May,2013);
	Settings::instance().evaluationDate() = evalDate;

	//instrument 
	Period swapTenor(3, Years);	
	Real rate = 0.06;	
	Handle<YieldTermStructure> termstructure(boost::shared_ptr<YieldTermStructure>(new FlatForward(evalDate	, rate, SimpleDayCounter())));
	boost::shared_ptr<IborIndex> index(new IborIndex("Libor", Period(6,Months), 0, KRWCurrency(), NullCalendar(), Unadjusted, false, SimpleDayCounter(),termstructure));
	Real strikes = stk; //0.04;
	
	Date exerciseDate =startDate +5*Years;
	const boost::shared_ptr<VanillaSwap> swap 
		= MakeVanillaSwap(swapTenor, index, strikes)
		.withEffectiveDate(exerciseDate)
		.withFixedLegTenor(Period(6,Months))
		.withFloatingLegSpread(0.0)
		.withFixedLegDayCount(SimpleDayCounter())
		.withFloatingLegDayCount(SimpleDayCounter())
		.withType(VanillaSwap::Payer);
	
	const boost::shared_ptr<Exercise> exercise(new EuropeanExercise(exerciseDate));	
	boost::shared_ptr<Swaption> swaption(new Swaption(swap, exercise));

	//pricing engine
	Real volatility = 0.2;		
	Handle<Quote> vol(boost::shared_ptr<Quote>(new SimpleQuote(volatility)));
	boost::shared_ptr<PricingEngine> engine(new BlackSwaptionEngine(termstructure, vol, SimpleDayCounter()));

	swaption->setPricingEngine(engine);	

	std::setprecision(10);
	std::cout<< "price : " << swaption->NPV() <<std::endl;	
}

int main(){
	Real strikes[] ={0.062, 0.03, 0.04,0.05, 0.06, 0.07};

	for(int i=0; i<5; ++i){
		swaption(strikes[i]);
	}	
}