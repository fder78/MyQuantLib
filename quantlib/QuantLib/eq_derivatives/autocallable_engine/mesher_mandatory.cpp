#include <eq_derivatives/autocallable_engine/mesher_mandatory.h>

namespace QuantLib {
	MandatoryMesher::MandatoryMesher(Size n, Real min, Real max, std::vector<Real> mandaroty) : Fdm1dMesher(0) {			
		Real margin = std::log(2);
		Real maxx = max, minx = min;
		if (mandaroty.size() > 0) {
			maxx = (max < mandaroty.back() + margin) ? mandaroty.back() + margin : max;
			minx = (min > mandaroty[0] - margin) ? mandaroty[0] - margin : min;
		}

		mandaroty.insert(mandaroty.begin(), minx);
		mandaroty.push_back(maxx);
		std::vector<Real> xs(1, minx);
		Real minWidth = (max - min) / n / 2.5;

		for (Size k = 1; k < mandaroty.size(); ++k) {
			Real x0 = mandaroty[k - 1], x1 = mandaroty[k];
			Size xg = (Size)((x1 - x0) / (maxx - minx) * n);
			Real dx = (x1 - x0) / xg;
			if (x1 - x0 > minWidth) {
				for (Size i = 1; i < xg; ++i)
					xs.push_back(xs.back() + dx);
				xs.push_back(x1);
			}
		}
		locations_.resize(xs.size());
		dplus_.resize(xs.size());
		dminus_.resize(xs.size());
		std::copy(xs.begin(), xs.end(), locations_.begin());
		dplus_.back() = dminus_.front() = Null<Real>();
		for (Size i = 0; i < xs.size() - 1; ++i) {
			dplus_[i] = dminus_[i + 1] = xs[i + 1] - xs[i];
		}		
	}
}