#include <eq_derivatives/autocallable_engine/mesher_mandatory.h>

namespace QuantLib {
	MandatoryMesher::MandatoryMesher(Size n, Real min, Real max, std::vector<Real> mandaroty)
		: Fdm1dMesher(n + 1) {

		std::vector<Real> xs(n + 1, 0.0);
		Real margin = std::log(2);
		Real mustHave = mandaroty[0];
		Real maxx = (max < mustHave + margin) ? mustHave + margin : max; 
		Real minx = (min > mustHave - margin) ? mustHave - margin : min; 
		Size xg2 = (Size)((maxx - mustHave) / (maxx - minx) * n);
		Size xg1 = n - xg2;
		Real dx1 = (mustHave - minx) / xg1;
		Real dx2 = (maxx - mustHave) / xg2;

		for (Size i = 0; i <= n; ++i) {
			if (i < xg1)
				xs[i] = minx + dx1 * i;
			else
				xs[i] = mustHave + dx2 * (i - xg1);
		}

		std::copy(xs.begin(), xs.end(), locations_.begin());
		dplus_.back() = dminus_.front() = Null<Real>();
		for (Size i = 0; i < xs.size() - 1; ++i) {
			dplus_[i] = dminus_[i + 1] = xs[i + 1] - xs[i];
		}		
	}
}