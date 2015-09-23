
#ifndef quantlib_generalized_hull_white_hpp_
#define quantlib_generalized_hull_white_hpp_

#include <ql/models/shortrate/onefactormodels/vasicek.hpp>
#include <ql/experimental/shortrate/generalizedornsteinuhlenbeckprocess.hpp>

namespace QuantLib {

	class Generalized_HullWhite : public Vasicek, public TermStructureConsistentModel {
	public:
		Generalized_HullWhite(const Handle<YieldTermStructure>& termStructure,
			std::vector<Date> dates = std::vector<Date>(1, Date()),
			std::vector<Real> sigma = std::vector<Real>(1, 0.01),
			Real a = 0.1,
			Real fxVol = 0.1,
			Real fxCorr = 0.0);

		boost::shared_ptr<Lattice> tree(const TimeGrid& grid) const;

		boost::shared_ptr<ShortRateDynamics> dynamics() const;

		Real discountBondOption(Option::Type type,
			Real strike,
			Time maturity,
			Time bondMaturity) const;

		
		boost::function<Real (Time)> speed() const;
		boost::function<Real (Time)> vol() const;

		Real fxVol() const {
			return fxVol_;
		}
		Real fxCorr() const {
			return fxCorr_;
		}
		Real x0() {
			return r0_;
		}
		Real expectation(Time s, Time t, Rate x);
		Real stdDeviation(Time s, Time t, Rate x);
		Real pA(Time t, Time T) const {
			return A(t,T);
		}
		Real pB(Time t, Time T) const {
			return B(t,T);
		}

	protected:
		void generateArguments();
		Real a() const {
			return a0_;
		}
		Real A(Time t, Time T) const;
		Real B(Time t, Time T) const;
		Real Vr(Time s, Time t) const;
		Real Vp(Time t, Time Tf, Time Tp) const;

	private:
				
		class Dynamics;
		class FittingParameter;
		
		std::vector<Time> volperiods_;
		Parameter phi_;
		Real a0_;
		Real fxVol_, fxCorr_;
	};

	class Generalized_HullWhite::Dynamics : public OneFactorModel::ShortRateDynamics {
	public:
		Dynamics(const Parameter& fitting,
			const boost::function<Real (Time)>& alpha,
			const boost::function<Real (Time)>& sigma)
			: ShortRateDynamics(boost::shared_ptr<StochasticProcess1D>(new GeneralizedOrnsteinUhlenbeckProcess(alpha, sigma))),
			fitting_(fitting) {}

		Real variable(Time t, Rate r) const {
			return r - fitting_(t);
		}
		Real shortRate(Time t, Real x) const {
			return x + fitting_(t);
		}
	private:
		Parameter fitting_;
	};

	class Generalized_HullWhite::FittingParameter : public TermStructureFittingParameter {
	private:
		class Impl : public Parameter::Impl {
		public:
			Impl(const Handle<YieldTermStructure>& termStructure, Real a, Parameter sigma, std::vector<Time> volperiods)
				: termStructure_(termStructure), a0_(a), sigma_(sigma), volperiods_(volperiods) {}

			Real value(const Array&, Time t) const {
				Rate forwardRate = termStructure_->forwardRate(t, t, Continuous, NoFrequency);
				//Real temp = a_(0) < std::sqrt(QL_EPSILON) ? sigma_(0)*t :	sigma_(0)*(1.0 - std::exp(-a_(0)*t))/a_(0);
				Real temp = 0;
				Time u0 = 0.0 , u1 = 0.0;
				Real a = a0_;

				for (Size i=0; i<volperiods_.size(); ++i) {
					u1 = volperiods_[i];
					if (u1>0 && u0<t) {
						u0 = (u0>0)?u0:0;
						u1 = (u1<t)?u1:t;
						Real s = sigma_(u0);
						temp += s*s*( 2*(std::exp(a*u1) - std::exp(a*u0)) - (std::exp(-a*(t-2*u1)) - std::exp(-a*(t-2*u0))) );
					}
					u0 = u1;
				}
				if (u0<t) {
					u0 = (u0>0)?u0:0;
					Real s = sigma_(u0);
					temp += s*s*( 2*(std::exp(a*t) - std::exp(a*u0)) - (std::exp(-a*(t-2*t)) - std::exp(-a*(t-2*u0))) );
				}
				temp *= std::exp(-a*t) / (2.0*a*a);
				return (forwardRate + temp);
			}

		private:
			Handle<YieldTermStructure> termStructure_;
			Parameter sigma_;
			Real a0_;
			std::vector<Time> volperiods_;
		};
	public:
		FittingParameter(const Handle<YieldTermStructure>& termStructure, Real a, Parameter sigma, std::vector<Time> volperiods)
			: TermStructureFittingParameter(boost::shared_ptr<Parameter::Impl>(
			new FittingParameter::Impl(termStructure, a, sigma, volperiods))) {}
	};


	// inline definitions
	inline boost::shared_ptr<OneFactorModel::ShortRateDynamics>
		Generalized_HullWhite::dynamics() const {
			return boost::shared_ptr<ShortRateDynamics>(new Dynamics(phi_, speed(), vol()));
	}

}


#endif

