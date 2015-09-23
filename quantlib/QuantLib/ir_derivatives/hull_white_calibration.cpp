
#include "hull_white_calibration.hpp"

#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>
#include <ql/experimental/shortrate/generalizedhullwhite.hpp>
#include <ql/models/calibrationhelper.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/pricingengines/capfloor/analyticcapfloorengine.hpp>
#include <ql/pricingengines/capfloor/treecapfloorengine.hpp>
#include <ql/pricingengines/swaption/treeswaptionengine.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/models/shortrate/calibrationhelpers/caphelper.hpp>
#include <ql/models/shortrate/calibrationhelpers/swaptionhelper.hpp>
#include <ql/math/optimization/levenbergmarquardt.hpp>
#include <ql/quotes/simplequote.hpp>
#include <iostream>

#include <ir_derivatives/generalized_hullwhite.hpp>

using namespace QuantLib;

namespace QuantLib {

	HullWhiteTimeDependentParameters calibration_hull_white(
		const Date& evalDate,
		const CapVolData& volData
	)
	{
			boost::shared_ptr<IborIndex> index = volData.index;
			Frequency fixedFreq = volData.fixedFreq;
			DayCounter fixedDC = volData.fixedDC;
			Real FixedA = volData.fixedA;
			std::vector<Real> initialSigma = volData.initialSigma;

			Settings::instance().evaluationDate() = Date( evalDate.serialNumber() );

			Date today  = Settings::instance().evaluationDate();
			std::vector<Date> dates;
			for (Size i=0; i<volData.tenors.size(); ++i){
				dates.push_back(today+volData.tenors[i]*Years);
			}
			dates.back() = today+50*Years;
			std::set<Date> temp(dates.begin(), dates.end());
			dates = std::vector<Date>(temp.begin(), temp.end());

			Handle<YieldTermStructure> rts_hw(index->forwardingTermStructure().currentLink());
			boost::shared_ptr<Generalized_HullWhite> model(new Generalized_HullWhite(rts_hw, dates, initialSigma, FixedA));

			boost::shared_ptr<PricingEngine> engine_hw(new AnalyticCapFloorEngine(model));
			//boost::shared_ptr<PricingEngine> engine_hw(new TreeCapFloorEngine(model, 80));
			std::vector<boost::shared_ptr<CalibrationHelper> > caps;

			for (Size i=0; i<volData.tenors.size(); ++i) {
				boost::shared_ptr<CalibrationHelper> helper(
					new CapHelper(Period(volData.tenors[i], Years),
					Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(volData.vols[i]))),
					index, fixedFreq,
					fixedDC,
					false,
					rts_hw, CalibrationHelper::PriceError));
				helper->setPricingEngine(engine_hw);
				caps.push_back(helper);		
			}

			LevenbergMarquardt optimizationMethod(1.0e-8,1.0e-8,1.0e-8);
			EndCriteria endCriteria(5000, 1000, 1e-8, 1e-8, 1e-8);
			Constraint c = BoundaryConstraint(0.01, 3.0);

			model->calibrate(caps, optimizationMethod, endCriteria, c);
			EndCriteria::Type ecType = model->endCriteria();
			Array xMinCalculated = model->params();
			
			//Real a = xMinCalculated[0];
			//Real sigmar = xMinCalculated[1];
			std::vector<Real> sigma;				
			for (Size i=0; i<xMinCalculated.size(); ++i) {
				sigma.push_back(xMinCalculated[i]);
			}

			return HullWhiteTimeDependentParameters(FixedA, dates, sigma, model, caps);
	}


	HullWhiteTimeDependentParameters calibration_hull_white(
		const Date& evalDate,
		const SwaptionVolData& volData
		)
	{
			boost::shared_ptr<IborIndex> index = volData.index;
			Frequency fixedFreq = volData.fixedFreq;
			DayCounter fixedDC = volData.fixedDC;
			DayCounter floatingDC = volData.floatingDC;
			Real FixedA = volData.fixedA;
			std::vector<Real> initialSigma = volData.initialSigma;

			Settings::instance().evaluationDate() = Date( evalDate.serialNumber() );

			Date today  = Settings::instance().evaluationDate();
			std::vector<Date> tmpdates;
			for (Size i=0; i<volData.maturities.size(); ++i){
				tmpdates.push_back(today+volData.maturities[i]);
			}
			tmpdates.back() = today+50*Years;

			std::set<Date> dateSet( tmpdates.begin(), tmpdates.end() );
			std::vector<Date> dates( dateSet.begin(), dateSet.end()	);

			Handle<YieldTermStructure> rts_hw(index->forwardingTermStructure().currentLink());
			//boost::shared_ptr<GeneralizedHullWhite> model(new GeneralizedHullWhite(rts_hw, dates, dates, std::vector<Real>(1, FixedA), initialSigma));
			boost::shared_ptr<Generalized_HullWhite> model(new Generalized_HullWhite(rts_hw, dates, initialSigma, FixedA));

			//boost::shared_ptr<PricingEngine> engine_hw(new AnalyticCapFloorEngine(model));
			//boost::shared_ptr<PricingEngine> engine_hw(new TreeSwaptionEngine(model, 100));
			boost::shared_ptr<PricingEngine> engine_hw(new JamshidianSwaptionEngine(model));
			std::vector<boost::shared_ptr<CalibrationHelper> > swaptions;

			for (Size i=0; i<volData.maturities.size(); ++i) {
				boost::shared_ptr<CalibrationHelper> helper(
					new SwaptionHelper(volData.maturities[i],
					volData.lengths[i],
					Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(volData.vols[i]))),
					index, Period(fixedFreq),
					fixedDC, floatingDC,
					rts_hw, CalibrationHelper::PriceError));
				helper->setPricingEngine(engine_hw);
				swaptions.push_back(helper);
			}

			LevenbergMarquardt optimizationMethod(1.0e-8,1.0e-8,1.0e-8);
			EndCriteria endCriteria(50000, 1000, 1e-8, 1e-8, 1e-8);

			model->calibrate(swaptions, optimizationMethod, endCriteria);
			EndCriteria::Type ecType = model->endCriteria();
			Array xMinCalculated = model->params();

			//Real a = xMinCalculated[0];
			//Real sigmar = xMinCalculated[1];
			std::vector<Real> sigma;				
			for (Size i=0; i<xMinCalculated.size(); ++i) {
				sigma.push_back(xMinCalculated[i]);
			}

			return HullWhiteTimeDependentParameters(FixedA, dates, sigma, model, swaptions);
	}

}