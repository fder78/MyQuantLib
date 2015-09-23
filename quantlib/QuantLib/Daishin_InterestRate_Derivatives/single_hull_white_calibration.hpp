

#ifndef hullwhite_calibration_hpp
#define hullwhite_calibration_hpp

#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>

namespace QuantLib {
	struct CapVolData;
	struct SwaptionVolData;

	struct HullWhiteParameters {
		Real a;
		Real sigma;
		HullWhiteParameters(Real a_, Real sigma_) :
		a(a_), sigma(sigma_) {}
	};
	
	HullWhiteParameters single_calibration_hull_white(
		const Date& evalDate,
		const CapVolData& volData
	);

	HullWhiteParameters single_calibration_hull_white(
		const Date& evalDate,
		const SwaptionVolData& volData
	);

}

#endif