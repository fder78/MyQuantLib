
#include "g2_calibration.hpp"

#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>
#include <ql/models/shortrate/twofactormodels/g2.hpp>
#include <ql/models/calibrationhelper.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/pricingengines/capfloor/analyticcapfloorengine.hpp>
#include <ql/pricingengines/swaption/g2swaptionengine.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/models/shortrate/calibrationhelpers/caphelper.hpp>
#include <ql/models/shortrate/calibrationhelpers/swaptionhelper.hpp>
#include <ql/math/optimization/levenbergmarquardt.hpp>
#include <ql/quotes/simplequote.hpp>
#include <iostream>

using namespace QuantLib;

namespace QuantLib {

	G2Parameters calibration_g2(
		const Date& evalDate,
		const CapVolData& volData,
		const G2Parameters& init
	)
	{
			boost::shared_ptr<IborIndex> index = volData.index;
			Frequency fixedFreq = volData.fixedFreq;
			DayCounter fixedDC = volData.fixedDC;

			Settings::instance().evaluationDate() = Date( evalDate.serialNumber() );

			Handle<YieldTermStructure> rts_hw(index->forwardingTermStructure().currentLink());
			boost::shared_ptr<G2> model(new G2(rts_hw, init.a, init.sigma, init.b, init.eta, init.rho));
			boost::shared_ptr<PricingEngine> engine_g2(new AnalyticCapFloorEngine(model));

			std::vector<boost::shared_ptr<CalibrationHelper> > caps;
			for (Size i=0; i<volData.tenors.size(); ++i) {
				boost::shared_ptr<CalibrationHelper> helper(
					new CapHelper(Period(volData.tenors[i], Years),
					Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(volData.vols[i]))),
					index, fixedFreq,
					fixedDC,
					false,
					rts_hw, CalibrationHelper::PriceError));
				helper->setPricingEngine(engine_g2);
				caps.push_back(helper);		
			}

			LevenbergMarquardt optimizationMethod(1.0e-8,1.0e-8,1.0e-8);
			EndCriteria endCriteria(5000, 1000, 1e-8, 1e-8, 1e-8);
			Constraint c = BoundaryConstraint(0.01, 3.0);

			model->calibrate(caps, optimizationMethod, endCriteria, c);
			EndCriteria::Type ecType = model->endCriteria();
			Array xMinCalculated = model->params();
			return G2Parameters(xMinCalculated[0], xMinCalculated[1], xMinCalculated[2], xMinCalculated[3], xMinCalculated[4], model, caps);
	}


	G2Parameters calibration_g2(
		const Date& evalDate,
		const SwaptionVolData& volData,
		const G2Parameters& init
		)
	{
			boost::shared_ptr<IborIndex> index = volData.index;
			Frequency fixedFreq = volData.fixedFreq;
			DayCounter fixedDC = volData.fixedDC;
			DayCounter floatingDC = volData.floatingDC;

			Settings::instance().evaluationDate() = Date( evalDate.serialNumber() );

			Handle<YieldTermStructure> rts_hw(index->forwardingTermStructure().currentLink());
			boost::shared_ptr<G2> model(new G2(rts_hw, init.a, init.sigma, init.b, init.eta, init.rho));
			boost::shared_ptr<PricingEngine> engine_g2(new G2SwaptionEngine(model, 6., 16));

			std::vector<boost::shared_ptr<CalibrationHelper> > swaptions;

			for (Size i=0; i<volData.maturities.size(); ++i) {
				boost::shared_ptr<CalibrationHelper> helper(
					new SwaptionHelper(volData.maturities[i],
					volData.lengths[i],
					Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(volData.vols[i]))),
					index, Period(fixedFreq),
					fixedDC, floatingDC,
					rts_hw, CalibrationHelper::PriceError));
				helper->setPricingEngine(engine_g2);
				swaptions.push_back(helper);
			}

			LevenbergMarquardt optimizationMethod(1.0e-8,1.0e-8,1.0e-8);
			EndCriteria endCriteria(50000, 1000, 1e-8, 1e-8, 1e-8);

			model->calibrate(swaptions, optimizationMethod, endCriteria);
			EndCriteria::Type ecType = model->endCriteria();
			Array xMinCalculated = model->params();
			return G2Parameters(xMinCalculated[0], xMinCalculated[1], xMinCalculated[2], xMinCalculated[3], xMinCalculated[4], model, swaptions);
	}

}