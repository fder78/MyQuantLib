
#include "generalized_hullwhite.hpp"
#include <ql/methods/lattices/trinomialtree.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/math/interpolations/forwardflatinterpolation.hpp>
#include <ql/termstructures/interpolatedcurve.hpp>
#include <ql/math/interpolations/linearinterpolation.hpp>

namespace QuantLib {

	namespace Impl{

		class PiecewiseLinearCurve : public InterpolatedCurve<ForwardFlat> {
		public:
			PiecewiseLinearCurve(const std::vector<Time>& times, const std::vector<Real>& data)
				: InterpolatedCurve<ForwardFlat>(times, data) {
					setupInterpolation();
			}

			Real operator()(Time t) {
				return interpolation_(t, true);
			}
		};

	}

	Generalized_HullWhite::Generalized_HullWhite(const Handle<YieldTermStructure>& termStructure,
		std::vector<Date> dates,
		std::vector<Real> sigma,
		Real a,
		Real fxVol,
		Real fxCorr)
		: Vasicek(termStructure->forwardRate(0.0, 0.0, Continuous, NoFrequency), a, 0.0, sigma[0], 0.0), a0_(a),
		TermStructureConsistentModel(termStructure), fxVol_(fxVol), fxCorr_(fxCorr)
	{
		a_ = NullParameter();
		b_ = NullParameter();
		lambda_ = NullParameter();

		DayCounter dc = termStructure->dayCounter();

		//volperiods_.push_back(0.0);
		for (Size i=0; i<dates.size()-1; i++)
			volperiods_.push_back(dc.yearFraction(Settings::instance().evaluationDate(), dates[i]));
		sigma_ = PiecewiseConstantParameter(volperiods_, PositiveConstraint());

		for (Size i=0; i< sigma_.size(); i++)
			sigma_.setParam(i, sigma[i]);


		generateArguments();
		registerWith(termStructure);
	}



	boost::shared_ptr<Lattice> Generalized_HullWhite::tree(const TimeGrid& grid) const {

		TermStructureFittingParameter phi(termStructure());
		boost::shared_ptr<ShortRateDynamics> numericDynamics(new Dynamics(phi, speed(), vol()));
		boost::shared_ptr<TrinomialTree> trinomial(new TrinomialTree(numericDynamics->process(), grid));
		boost::shared_ptr<ShortRateTree> numericTree(new ShortRateTree(trinomial, numericDynamics, grid));

		typedef TermStructureFittingParameter::NumericalImpl NumericalImpl;
		boost::shared_ptr<NumericalImpl> impl =	boost::dynamic_pointer_cast<NumericalImpl>(phi.implementation());
		impl->reset();
		for (Size i=0; i<(grid.size() - 1); i++) {
			Real discountBond = termStructure()->discount(grid[i+1]);
			const Array& statePrices = numericTree->statePrices(i);
			Size size = numericTree->size(i);
			Time dt = numericTree->timeGrid().dt(i);
			Real dx = trinomial->dx(i);
			Real x = trinomial->underlying(i,0);
			Real value = 0.0;
			for (Size j=0; j<size; j++) {
				value += statePrices[j]*std::exp(-x*dt);
				x += dx;
			}
			value = std::log(value/discountBond)/dt;
			impl->set(grid[i], value);
		}
		return numericTree;
	}

	Real Generalized_HullWhite::A(Time t, Time T) const {
		DiscountFactor discount1 = termStructure()->discount(t);
		DiscountFactor discount2 = termStructure()->discount(T);
		Rate forward = termStructure()->forwardRate(t, t, Continuous, NoFrequency);
		Real temp = B(t,T);
		Real value = B(t,T)*forward - 0.5*temp*temp*Vr(0, t);
		return std::exp(value)*discount2/discount1;
	}
	
	Real Generalized_HullWhite::B(Time t, Time T) const {
		Real _a = a();
		if (_a < std::sqrt(QL_EPSILON))
			return (T - t);
		else
			return (1.0 - std::exp(-_a*(T - t)))/_a;
	}

	Real Generalized_HullWhite::Vr(Time s, Time t) const {
		QL_REQUIRE(s<=t, "s should be less than t");
		Real temp = 0.0;
		Time u0 = 0.0, u1 = 0.0;
		for (Size i=0; i<volperiods_.size(); ++i) {
			u1 = volperiods_[i];
			if (u1>s && u0<t) {
				u0 = (u0>s)?u0:s;
				u1 = (u1<t)?u1:t;
				temp += sigma_(u0)*sigma_(u0) / (2 * a()) * (std::exp(2*a()*u1) - std::exp(2*a()*u0));
			}
			u0 = u1;
		}
		if (u0<t) {
			u0 = (u0>s)?u0:s;
			temp += sigma_(u0)*sigma_(u0) / (2 * a()) * (std::exp(2*a()*t) - std::exp(2*a()*u0));
		}

		return std::exp(-2.0*a()*t) * temp;
	}

	Real Generalized_HullWhite::expectation(Time s, Time t, Rate x) {
		Real temp = ( x - phi_(s) ) * std::exp(- a0_ * (t-s) );
		temp += phi_(t);
		return temp;
	}
	
	Real Generalized_HullWhite::stdDeviation(Time s, Time t, Rate x) {
		return std::sqrt( Vr(s, t) );
	}


	Real Generalized_HullWhite::Vp(Time t, Time Tf, Time Tp) const {
		return Vr(t, Tf) * B(Tf, Tp) * B(Tf, Tp);
	}

	void Generalized_HullWhite::generateArguments() {
		phi_ = FittingParameter(termStructure(), a0_, sigma_, volperiods_);
	}

	Real Generalized_HullWhite::discountBondOption(Option::Type type, Real strike,
		Time maturity,
		Time bondMaturity) const {

			Real _a = a();
			Real v;
			v = std::sqrt(Vp(0, maturity, bondMaturity));
			Real f = termStructure()->discount(bondMaturity);
			Real k = termStructure()->discount(maturity)*strike;

			return blackFormula(type, k, f, v);
	}

	boost::function<Real (Time)> Generalized_HullWhite::speed() const {
		std::vector<Real> speedvals, speedPeriod;
		speedPeriod.push_back(0.0);
		speedPeriod.push_back(50);
		speedvals.push_back(a0_);
		speedvals.push_back(a0_);
		return Impl::PiecewiseLinearCurve(speedPeriod, speedvals);
	}

	boost::function<Real (Time)> Generalized_HullWhite::vol() const {
		std::vector<Real> volvals, volPeriod;
		volvals.push_back(sigma_(0.0));
		volPeriod.push_back(0.0);
		for (Size i=0;i<volperiods_.size();i++) {
			volvals.push_back(sigma_(volperiods_[i]+0.001));
			volPeriod.push_back(volperiods_[i]);
		}
		return Impl::PiecewiseLinearCurve(volPeriod, volvals);
	}

}

