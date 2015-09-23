#include "single_hull_white_calibration.hpp"

#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>
#include <ql/models/calibrationhelper.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/pricingengines/capfloor/analyticcapfloorengine.hpp>
#include <ql/pricingengines/swaption/jamshidianswaptionengine.hpp>
#include <ql/models/shortrate/calibrationhelpers/caphelper.hpp>
#include <ql/models/shortrate/calibrationhelpers/swaptionhelper.hpp>
#include <ql/math/optimization/levenbergmarquardt.hpp>
#include <ql/quotes/simplequote.hpp>

#include <ds_interestrate_derivatives/hw_calibration/hull_white_calibration.hpp>

using namespace QuantLib;

namespace QuantLib {

	HullWhiteParameters single_calibration_hull_white(
		const Date& evalDate,
		const CapVolData& volData
	) {
		boost::shared_ptr<IborIndex> index = volData.index;
		Frequency fixedFreq = volData.fixedFreq;
		DayCounter fixedDC = volData.fixedDC;

			Settings::instance().evaluationDate() = Date( evalDate.serialNumber() );

			Handle<YieldTermStructure> rts_hw(index->forwardingTermStructure().currentLink());
			boost::shared_ptr<HullWhite> model(new HullWhite(rts_hw));
			boost::shared_ptr<PricingEngine> engine_hw(new AnalyticCapFloorEngine(model));
			std::vector<boost::shared_ptr<CalibrationHelper> > caps;


			for (Size i=0; i<volData.tenors.size(); ++i) {
				boost::shared_ptr<CalibrationHelper> helper(
					new CapHelper(Period(volData.tenors[i], Years),
					Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(volData.vols[i]))),
					index, fixedFreq,
					fixedDC,
					true,
					rts_hw,
					CalibrationHelper::ImpliedVolError));
				helper->setPricingEngine(engine_hw);
				caps.push_back(helper);		
			}

			LevenbergMarquardt optimizationMethod(1.0e-8,1.0e-8,1.0e-8);
			EndCriteria endCriteria(10000, 100, 1e-6, 1e-8, 1e-8);

			model->calibrate(caps, optimizationMethod, endCriteria);
			EndCriteria::Type ecType = model->endCriteria();
			Array xMinCalculated = model->params();

			Real a = xMinCalculated[0];
			Real sigmar = xMinCalculated[1];

			return HullWhiteParameters(a,sigmar);
	}

	HullWhiteParameters single_calibration_hull_white(
		const Date& evalDate,
		const SwaptionVolData& volData
	) {

			Settings::instance().evaluationDate() = Date( evalDate.serialNumber() );

			Handle<YieldTermStructure> rts_hw(volData.index->forwardingTermStructure().currentLink());
			boost::shared_ptr<HullWhite> model(new HullWhite(rts_hw));
			boost::shared_ptr<PricingEngine> engine_hw(new JamshidianSwaptionEngine(model));
			std::vector<boost::shared_ptr<CalibrationHelper> > swaptions;


			for (Size i=0; i<volData.lengths.size(); ++i) {

				boost::shared_ptr<CalibrationHelper> helper(
					new SwaptionHelper(volData.maturities[i],
					Period(volData.lengths[i]),
					Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(volData.vols[i]))),
					volData.index, 
					Period(volData.fixedFreq),
					volData.fixedDC,
					volData.floatingDC,
					rts_hw,
					CalibrationHelper::RelativePriceError));

				helper->setPricingEngine(engine_hw);

				swaptions.push_back(helper);		
			}

			LevenbergMarquardt optimizationMethod(1.0e-8,1.0e-8,1.0e-8);
			EndCriteria endCriteria(10000, 100, 1e-6, 1e-8, 1e-8);

			model->calibrate(swaptions, optimizationMethod, endCriteria);
			EndCriteria::Type ecType = model->endCriteria();
			Array xMinCalculated = model->params();

			Real a = xMinCalculated[0];
			Real sigmar = xMinCalculated[1];

			return HullWhiteParameters(a,sigmar);

	}

}