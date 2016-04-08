#pragma once

#include <ql/instruments/payoffs.hpp>
#include <ql/instruments/basketoption.hpp>
#include <ql/instruments/multiassetoption.hpp>
#include <ql/math/array.hpp>
#include <ql/time/schedule.hpp>

namespace QuantLib {

	class CallableIndexRangeAccrual : public MultiAssetOption {
	public:
		class engine;
		class arguments;
		CallableIndexRangeAccrual(
			const Real& notional,
			const std::vector<Real>& basePrices,
			const std::vector<std::pair<Real, Real> >& rabounds,
			const Schedule& couponDates,
			const Schedule& paymentDates,
			const boost::shared_ptr<Payoff>&,
			const boost::shared_ptr<Exercise>&,
			const Size inRangeCount);
		void setupArguments(PricingEngine::arguments*) const;

	protected:
		Real notional_;
		std::vector<Real> basePrices_;
		std::vector<std::pair<Real, Real> > rabounds_;
		Schedule couponDates_;
		Schedule paymentDates_;
		Size inRangeCount_;
	};

	class CallableIndexRangeAccrual::arguments : public MultiAssetOption::arguments {
	public:
		void validate() const { MultiAssetOption::arguments::validate(); }
		Real notional;
		std::vector<Real> basePrices;
		std::vector<std::pair<Real, Real> > rabounds;
		Schedule couponDates;
		Schedule paymentDates;
		Size inRangeCount;
	};

	//! %Basket-option %engine base class
	class CallableIndexRangeAccrual::engine 
		: public GenericEngine<CallableIndexRangeAccrual::arguments, CallableIndexRangeAccrual::results> {};


}
