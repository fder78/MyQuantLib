#pragma once

#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/models/calibrationhelper.hpp>
#include <ql/experimental/shortrate/generalizedhullwhite.hpp>
#include <ir_derivatives/generalized_hullwhite.hpp>

namespace QuantLib {
	
	struct HullWhiteTimeDependentParameters {
		Real a;
		std::vector<Date> tenor;
		std::vector<Real> sigma;
		boost::shared_ptr<Generalized_HullWhite> model;
		std::vector<boost::shared_ptr<CalibrationHelper> > helpers;
		HullWhiteTimeDependentParameters(Real a_, std::vector<Date> tenor_, std::vector<Real> sigma_, 
			boost::shared_ptr<Generalized_HullWhite> model_ = boost::shared_ptr<Generalized_HullWhite>(),
			std::vector<boost::shared_ptr<CalibrationHelper> > helpers_ = std::vector<boost::shared_ptr<CalibrationHelper> >()) :
		a(a_), tenor(tenor_), sigma(sigma_), model(model_), helpers(helpers_) {}
	};

	struct CapVolData {
		std::vector<Size> tenors;
		std::vector<Rate> vols;
		Frequency fixedFreq;
		DayCounter fixedDC;
		boost::shared_ptr<IborIndex> index;
		Real fixedA;
		std::vector<Real> initialSigma;
	};

	struct SwaptionVolData {
		std::vector<Period> maturities;
		std::vector<Period> lengths;
		std::vector<Rate> vols;
		Frequency fixedFreq;
		DayCounter fixedDC;
		DayCounter floatingDC;
		boost::shared_ptr<IborIndex> index;
		Real fixedA;
		std::vector<Real> initialSigma;
	};

	HullWhiteTimeDependentParameters calibration_hull_white
	(
		const Date& evalDate,
		const CapVolData& volData
	);

	HullWhiteTimeDependentParameters calibration_hull_white(
		const Date& evalDate,
		const SwaptionVolData& volData
	);

}

