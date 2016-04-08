
#include "mc_callable_index_ra_engine.hpp"
#include <ql/math/functional.hpp>
#include <ql/methods/montecarlo/lsmbasissystem.hpp>
#include <boost/bind.hpp>

using boost::bind;

namespace QuantLib {

    CallableIndexRAPathPricer::CallableIndexRAPathPricer(
        Size assetNumber,
        const boost::shared_ptr<Payoff>& payoff,
		const Real& notional,
		const std::vector<Real>& basePrices,
		const std::vector<std::pair<Real, Real> >& rabounds,
		const Schedule& couponDates,
		const Schedule& paymentDates,
		const Size& inRangeCount, 
		const Size& timeStepPerYear,
		const std::vector<Size>& exerciseIndex,
		const std::vector<DiscountFactor>& df,
        Size polynomOrder,
        LsmBasisSystem::PolynomType polynomType)
    : assetNumber_ (assetNumber), payoff_(payoff), v_(LsmBasisSystem::multiPathBasisSystem(assetNumber_, polynomOrder, polynomType)), inRangeCount_(inRangeCount), timeStepPerYear_(timeStepPerYear),
		notional_(notional), basePrices_(basePrices), rabounds_(rabounds), couponDates_(couponDates), paymentDates_(paymentDates), exerciseIndex_(exerciseIndex), df_(df) {

        QL_REQUIRE(   polynomType == LsmBasisSystem::Monomial
                   || polynomType == LsmBasisSystem::Laguerre
                   || polynomType == LsmBasisSystem::Hermite
                   || polynomType == LsmBasisSystem::Hyperbolic
                   || polynomType == LsmBasisSystem::Chebyshev2nd,
                   "insufficient polynom type");

		for (Size i = 0; i < rabounds_.size(); ++i)
			boundValues_.push_back(
				std::pair<Real, Real>(basePrices_[i] * rabounds_[i].first, basePrices_[i] * rabounds_[i].second));

        //v_.push_back(boost::bind(&CallableIndexRAPathPricer::payoff, this, _1)); 
    }

    Array CallableIndexRAPathPricer::state(const MultiPath& path, Size t) const {
        QL_REQUIRE(path.assetNumber() == assetNumber_, "invalid multipath");
        Array tmp(assetNumber_);
        for (Size i=0; i<assetNumber_; ++i) {
			tmp[i] = path[i][exerciseIndex_[t]];
        }
        return tmp;
    }

	//EXERCISE VALUE
    Real CallableIndexRAPathPricer::operator()(const MultiPath& path, Size t) const {
		std::vector<Size> inRange(exerciseIndex_.size()-1, 0);
		std::vector<Real> exerciseValues(exerciseIndex_.size() - 1, 0);
		for (Size i = 0; i < exerciseIndex_.size()-1; ++i) {
			for (Size k = exerciseIndex_[i]; k < exerciseIndex_[i + 1]; ++k) {
				Array tmp(assetNumber_);
				for (Size i = 0; i<assetNumber_; ++i) {
					tmp[i] = path[i][k];
				}
				if (this->isInRange(tmp))
					inRange[i]++;
			}
			Real s = (double)inRange[i] / timeStepPerYear_ + (i == 0 ? inRangeCount_ : 0) / 365.0;
			Real payoff = (*payoff_)(s);
			if (i == 0) {
				exerciseValues[i] = payoff + 1.0;
			}
			else {
				Real prev = exerciseValues[i - 1] - 1.0;
				exerciseValues[i] = prev / ((prev < 0.0) ? 1.0 : df_[i]) + payoff + 1.0;
			}
		}
		return (-1.0)*(exerciseValues[t - 1]);
    }

	bool CallableIndexRAPathPricer::isInRange(Array& prices) const {
		Size n = prices.size();		
		for (Size i = 0; i < n; ++i) {
			if (prices[i] < boundValues_[i].first || prices[i] > boundValues_[i].second)
				return false;
		}
		return true;
	}

    std::vector<boost::function1<Real, Array> >
    CallableIndexRAPathPricer::basisSystem() const {
        return v_;
    }

}
