#include "range_accrual_note_tree.hpp"

#include <ds_interestrate_derivatives/instruments/notes/range_accrual_note.hpp>
#include <ds_interestrate_derivatives/pricingengine/tree_engine/tree_callable_bond_engine.hpp>
#include <ds_interestrate_derivatives/hw_calibration/hull_white_calibration.hpp>

namespace QuantLib {

	std::vector<Real> single_rangeaccrual(Date evaluationDate,
		Real notional,
		std::vector<Rate> couponRate,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Schedule callDates,
		Size pastAccrual,
		boost::shared_ptr<YieldTermStructure> refCurve,
		const HullWhiteTimeDependentParameters& geneHWparams,
		boost::shared_ptr<YieldTermStructure> discCurve,
		Size steps,
		Real alpha,
		Real fixingRate) {

			Date todaysDate = evaluationDate;
			Settings::instance().evaluationDate() = todaysDate;

			boost::shared_ptr<IborIndex> index(new Euribor3M(Handle<YieldTermStructure>(refCurve)));
			std::vector<Real> gearing(1, QL_MIN_POSITIVE_REAL);
			std::vector<Real> spread(couponRate);
			std::vector<Real> lowerTrigger1(lowerBound);
			std::vector<Real> upperTrigger1(upperBound);
			Period obsTenor(Daily);
			
			CallabilitySchedule callSchedule;
			Real callValue = notional;
			if (alpha!=Null<Real>())
				callValue = 0.0;
			for (Size i=0; i<callDates.size(); ++i) {
				boost::shared_ptr<Callability> callability(new 
					Callability(Callability::Price(callValue, Callability::Price::Clean), Callability::Call, callDates[i]));				
				callSchedule.push_back(callability);
			}

			//boost::shared_ptr<StochasticProcess1D> discProcess(new 
			//	HullWhiteProcess(Handle<YieldTermStructure>(disc.yts), disc.hwParams.a, disc.hwParams.sigma));
			/***********************************************************************************/

			RangeAccrualNote testProduct(0, notional, schedule, index, index, dayCounter, bdc, Null<Natural>(), 
				gearing, spread, lowerTrigger1, upperTrigger1, obsTenor, Unadjusted, 100.0, Date(), 
				callSchedule, Exercise::Bermudan, alpha, fixingRate);


			//boost::shared_ptr<GeneralizedHullWhite> model(new 
			//	GeneralizedHullWhite(Handle<YieldTermStructure>(refCurve), geneHWparams.tenor, geneHWparams.tenor, std::vector<Real>(1,geneHWparams.a), geneHWparams.sigma));
			boost::shared_ptr<Generalized_HullWhite> model(new 
				Generalized_HullWhite(Handle<YieldTermStructure>(refCurve), geneHWparams.tenor, geneHWparams.sigma, geneHWparams.a));

			/*****Pricing Engine*****/
			boost::shared_ptr<PricingEngine> engine_tree(new HwTreeCallableBondEngine(model, 
				steps, 
				Handle<YieldTermStructure>(discCurve),
				pastAccrual)); //pastAccrual
			testProduct.setPricingEngine(engine_tree);

			std::vector<Real> rst;
			rst.push_back(testProduct.NPV());
			//rst.push_back(testProduct.errorEstimate());
			return rst;
	}
	
}