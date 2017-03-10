
#include <eq_derivatives\autocallable_mc_engine\mc_autocall_engine.h>

namespace QuantLib {

    AutocallPricer::AutocallPricer(AutocallableNote::arguments& arguments,
		const boost::shared_ptr<YieldTermStructure>& discCurve)
		: arguments_(arguments), discCurve_(discCurve), nextCallIdx_(-1), callIdx_(std::vector<Size>()) {
		std::vector<Date> dates = arguments_.autocallDates;
		Date evalDate = Settings::instance().evaluationDate();
		for (Size i = 0; i < dates.size(); ++i) {
			if (dates[i] > evalDate) {
				if (nextCallIdx_==-1)
					nextCallIdx_ = i;
				if (arguments_.isKI)
					callIdx_.push_back(i - nextCallIdx_ + 1);
				else
					callIdx_.push_back(dates[i] - evalDate);
			}
		}
	}

    Real AutocallPricer::operator()(const MultiPath& multiPath) const {
        Size n = multiPath.pathSize();
        QL_REQUIRE(n>0, "the path cannot be empty");
        Size numAssets = multiPath.assetNumber();
        QL_REQUIRE(numAssets>0, "there must be some paths");

		//Real notionalAmt;
		//std::vector<Date> autocallDates;
		//std::vector<Date> paymentDates;
		//std::vector<boost::shared_ptr<AutocallCondition> > autocallConditions;
		//std::vector<boost::shared_ptr<BasketPayoff> > autocallPayoffs;
		//std::vector<boost::shared_ptr<AutocallCondition> > KIautocallConditions;
		//std::vector<boost::shared_ptr<BasketPayoff> > KIautocallPayoffs;
		//boost::shared_ptr<BasketPayoff> terminalPayoff, KIPayoff;
		//boost::shared_ptr<AutocallCondition> kibarrier;
		//bool isKI;
		
		Size k;
		Array s(numAssets, 0);
		Real discPayoff;
		bool hasKI = arguments_.kibarrier->getBarrierNumbers() > 0;

		if (arguments_.isKI) {
			for (Size j = 0; j < callIdx_.size(); ++j) {
				for (Size i = 0; i < numAssets; ++i) {
					s[i] = multiPath[i][callIdx_[j]];
				}
				if (j < callIdx_.size() - 1) {
					k = nextCallIdx_ + j;
					if (hasKI) {
						if (arguments_.KIautocallConditions[k]->operator()(s))
							return discCurve_->discount(arguments_.paymentDates[k]) * arguments_.KIautocallPayoffs[k]->operator()(s);
					}
					else {
						if (arguments_.autocallConditions[k]->operator()(s))
							return discCurve_->discount(arguments_.paymentDates[k]) * arguments_.autocallPayoffs[k]->operator()(s);
					}
				}
			}
			if (hasKI)
				discPayoff = discCurve_->discount(arguments_.paymentDates.back()) * arguments_.KIPayoff->operator()(s);
			else
				discPayoff = discCurve_->discount(arguments_.paymentDates.back()) * arguments_.terminalPayoff->operator()(s);
			return discPayoff;
		}
		else { //KI 터치 하지 않은 경우
			bool iski = false;
			for (Size j = 0; j < callIdx_.size(); ++j) {
				if (!iski) {
					Size startIdx = (j == 0) ? 1 : (callIdx_[j - 1] + 1);
					for (Size jj = startIdx; jj <= callIdx_[j]; ++jj) {
						for (Size i = 0; i < numAssets; ++i)
							s[i] = multiPath[i][jj];
						if (arguments_.kibarrier->operator()(s)) {
							iski = true;
							break;
						}
					}
				}
				if (j < callIdx_.size() - 1) {
					for (Size i = 0; i < numAssets; ++i)
						s[i] = multiPath[i][callIdx_[j]];
					k = nextCallIdx_ + j;
					if (iski) {
						if (arguments_.KIautocallConditions[k]->operator()(s)) {
							discPayoff = discCurve_->discount(arguments_.paymentDates[k]) * arguments_.KIautocallPayoffs[k]->operator()(s);
							return discPayoff;
						}
					}
					else {
						if (arguments_.autocallConditions[k]->operator()(s)) {
							discPayoff = discCurve_->discount(arguments_.paymentDates[k]) * arguments_.autocallPayoffs[k]->operator()(s);
							return discPayoff;
						}
					}
				}
			}
			for (Size i = 0; i < numAssets; ++i)
				s[i] = multiPath[i][callIdx_.back()];
			if (iski) {
				discPayoff = discCurve_->discount(arguments_.paymentDates.back()) * arguments_.KIPayoff->operator()(s);
				return discPayoff;
			}
			else {
				discPayoff = discCurve_->discount(arguments_.paymentDates.back()) * arguments_.terminalPayoff->operator()(s);
				return discPayoff;
			}
		}
    }

}

