#include "range_accrual_note_tree.hpp"

#include <ds_interestrate_derivatives/instruments/notes/range_accrual_note.hpp>
#include <ds_interestrate_derivatives/pricingengine/tree_engine/tree_callable_bond_engine.hpp>
#include <ds_interestrate_derivatives/hw_calibration/hull_white_calibration.hpp>

namespace QuantLib {

	std::vector<Real> single_rangeaccrual(Date evaluationDate,
		Real notional,
		std::vector<Rate> couponRate,
		std::vector<Real> gearing,
		Schedule schedule,
		DayCounter dayCounter,
		BusinessDayConvention bdc,
		std::vector<Real> lowerBound,
		std::vector<Real> upperBound,
		Schedule callDates,
		std::vector<Real> callValues,
		Size pastAccrual,
		boost::shared_ptr<YieldTermStructure> refCurve,
		const HullWhiteTimeDependentParameters& geneHWparams,
		boost::shared_ptr<YieldTermStructure> discCurve,
		Size steps,
		Real invAlpha,
		Real invGearing,
		Real invFixing,
		Real cap,
		Real floor,
		Real alpha,
		Real pastFixing ) {

			Date todaysDate = evaluationDate;
			Settings::instance().evaluationDate() = todaysDate;

			boost::shared_ptr<IborIndex> index(new Euribor3M(Handle<YieldTermStructure>(refCurve)));
			std::vector<Real> gearingVec(gearing);
			std::vector<Real> spread(couponRate);
			std::vector<Real> lowerTrigger1(lowerBound);
			std::vector<Real> upperTrigger1(upperBound);
			Period obsTenor(Daily);
			
			CallabilitySchedule callSchedule;
			for (Size i=0; i<callDates.size(); ++i) {
				Real callValue = ( callValues.empty() ) ? ( ( alpha == Null<Real>() ) ? notional : 0. ) : callValues[ i ];
				boost::shared_ptr<Callability> callability(new 
					Callability(Callability::Price(callValue, Callability::Price::Clean), Callability::Call, callDates[i]));				
				callSchedule.push_back(callability);
			}

			//boost::shared_ptr<StochasticProcess1D> discProcess(new 
			//	HullWhiteProcess(Handle<YieldTermStructure>(disc.yts), disc.hwParams.a, disc.hwParams.sigma));
			/***********************************************************************************/

			RangeAccrualNote testProduct(0, notional, schedule, index, index, dayCounter, bdc, Null<Natural>(), 
				gearingVec, spread, lowerTrigger1, upperTrigger1, obsTenor, Unadjusted, 100.0, Date(), 
				callSchedule, Exercise::Bermudan, alpha, pastFixing);

			if (invGearing!=Null<Real>()) {
				testProduct.setInverseFloater(invAlpha, invGearing, cap, floor, invFixing);
			}

			boost::shared_ptr<Generalized_HullWhite> model(new 
				Generalized_HullWhite(Handle<YieldTermStructure>( refCurve ), geneHWparams.tenor, geneHWparams.sigma, geneHWparams.a ) );
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