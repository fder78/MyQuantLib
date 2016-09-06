#pragma once

#include <ql/methods/finitedifferences/meshers/predefined1dmesher.hpp>

namespace QuantLib {

	class MandatoryMesher : public Fdm1dMesher {
	public:
		MandatoryMesher(Size n, Real min, Real max, std::vector<Real> mandaroty);
	};
}