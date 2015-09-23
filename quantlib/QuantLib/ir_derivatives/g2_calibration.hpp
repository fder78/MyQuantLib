#pragma once

#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/models/calibrationhelper.hpp>
#include <ql/models/shortrate/twofactormodels/g2.hpp>
#include "hull_white_calibration.hpp"

namespace QuantLib {
	
	struct G2Parameters {
		Real a;
		Real sigma;
		Real b;
		Real eta;
		Real rho;
		boost::shared_ptr<G2> model;
		std::vector<boost::shared_ptr<CalibrationHelper> > helpers;
		G2Parameters(Real a_, Real sigma_, Real b_, Real eta_, Real rho_,
			boost::shared_ptr<G2> model_ = boost::shared_ptr<G2>(),
			std::vector<boost::shared_ptr<CalibrationHelper> > helpers_ = std::vector<boost::shared_ptr<CalibrationHelper> >()) :
		a(a_), sigma(sigma_), b(b_), eta(eta_), rho(rho_), model(model_), helpers(helpers_) {}
	};

	G2Parameters calibration_g2
	(
		const Date& evalDate,
		const CapVolData& volData
	);

	G2Parameters calibration_g2
	(
		const Date& evalDate,
		const SwaptionVolData& volData
	);

}

