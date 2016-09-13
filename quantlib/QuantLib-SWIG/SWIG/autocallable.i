
#ifndef eq_autocallable_i
#define eq_autocallable_i

%include types.i
%include vectors.i
%include instruments.i
%include date.i
%include basketoptions.i
%include scheduler.i

%{
using QuantLib::ArrayPayoff;
using QuantLib::GeneralPayoff;
using QuantLib::GeneralBasketPayoff;
using QuantLib::MinOfPayoffs;
using QuantLib::AutocallableNote;
using QuantLib::AutocallCondition;
using QuantLib::MinUpCondition;
using QuantLib::MinDownCondition;
typedef boost::shared_ptr<Payoff> GeneralPayoffPtr;
typedef boost::shared_ptr<BasketPayoff> GeneralBasketPayoffPtr;
typedef boost::shared_ptr<ArrayPayoff> MinOfPayoffsPtr;
typedef boost::shared_ptr<BasketPayoff> MinBasketPayoffPtr2;
typedef boost::shared_ptr<Instrument> AutocallableNotePtr;
typedef boost::shared_ptr<AutocallCondition> MinUpConditionPtr;
typedef boost::shared_ptr<AutocallCondition> MinDownConditionPtr;
%}

%ignore ArrayPayoff;
class ArrayPayoff {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE) \
     || defined(SWIGCSHARP) || defined(SWIGPERL)
    %rename(call) operator();
    #endif
  public:
    Real operator()(const Array& a);
};
%template(ArrayPayoffPtr) boost::shared_ptr<ArrayPayoff>;

%ignore AutocallCondition;
class AutocallCondition {
    #if defined(SWIGMZSCHEME) || defined(SWIGGUILE) \
     || defined(SWIGCSHARP) || defined(SWIGPERL)
    %rename(call) operator();
    #endif
  public:
    Real operator()(Array& a) const;
};
%template(AutocallCondition) boost::shared_ptr<AutocallCondition>;

%template(PayoffVector) std::vector<boost::shared_ptr<Payoff> >;
%rename(MinOfPayoffs) MinOfPayoffsPtr;
class MinOfPayoffsPtr : public boost::shared_ptr<ArrayPayoff> {
  public:
    %extend {
        MinOfPayoffsPtr(std::vector<boost::shared_ptr<Payoff> > payoffs) {
            return new MinOfPayoffsPtr(new MinOfPayoffs(payoffs));
        }
    }
};

%rename(GeneralPayoff) GeneralPayoffPtr;
class GeneralPayoffPtr : public boost::shared_ptr<Payoff> {
  public:
    %extend {
        GeneralPayoffPtr(const std::vector<Real> startPoints, const std::vector<Real> startPayoffs, const std::vector<Real> slopes) {
            return new GeneralPayoffPtr(new GeneralPayoff(startPoints, startPayoffs, slopes));
        }
    }
};

%template(BasketPayoff2) boost::shared_ptr<BasketPayoff>;
%rename(MinBasketPayoff2) MinBasketPayoffPtr2;
class MinBasketPayoffPtr2 : public boost::shared_ptr<BasketPayoff> {
  public:
    %extend {
        MinBasketPayoffPtr2(const boost::shared_ptr<Payoff> p) {
            return new MinBasketPayoffPtr2(new MinBasketPayoff(p));
        }
    }
};

%rename(GeneralBasketPayoff) GeneralBasketPayoffPtr;
class GeneralBasketPayoffPtr : public boost::shared_ptr<BasketPayoff> {
  public:
    %extend {
        GeneralBasketPayoffPtr(const boost::shared_ptr<ArrayPayoff>& payoff) {
            return new GeneralBasketPayoffPtr(new GeneralBasketPayoff(payoff));
        }
    }
};

%rename(AutocallableNote) AutocallableNotePtr;
class AutocallableNotePtr : public boost::shared_ptr<Instrument> {
  public:
    %extend {
        AutocallableNotePtr(const Real notionalAmt,
			const Schedule autocallDates,
			const Schedule paymentDates,
			const std::vector<boost::shared_ptr<AutocallCondition> >& autocallConditions,
			const std::vector<boost::shared_ptr<BasketPayoff> >& autocallPayoffs,
			const boost::shared_ptr<BasketPayoff> terminalPayoff) {
			
            return new AutocallableNotePtr(new AutocallableNote(
			notionalAmt, autocallDates, paymentDates, autocallConditions, autocallPayoffs, terminalPayoff));			
        }
				
		void withKIBarrier(boost::shared_ptr<AutocallCondition> kibarrier, 
			boost::shared_ptr<BasketPayoff> KIPayoff) {
			boost::dynamic_pointer_cast<AutocallableNote>(*self)->withKI(kibarrier, KIPayoff);
		}

		void hasKnockedIn() {
			boost::dynamic_pointer_cast<AutocallableNote>(*self)->hasKnockedIn();
		}
		
		std::vector<Real> delta() const {
            return boost::dynamic_pointer_cast<AutocallableNote>(*self)->delta();
        }
		std::vector<Real> gamma() const {
            return boost::dynamic_pointer_cast<AutocallableNote>(*self)->gamma();
        }
		std::vector<Real> theta() const {
            return boost::dynamic_pointer_cast<AutocallableNote>(*self)->theta();
        }
		std::vector<std::vector<Real> > xgamma() const {
            return boost::dynamic_pointer_cast<AutocallableNote>(*self)->xgamma();
        }
    }
};

%rename(MinUpCondition) MinUpConditionPtr;
class MinUpConditionPtr : public boost::shared_ptr<AutocallCondition> {
  public:
    %extend {
        MinUpConditionPtr(Real barrier) {
            return new MinUpConditionPtr(new MinUpCondition(barrier));
        }
		MinUpConditionPtr(std::vector<Real> barrier) {
            return new MinUpConditionPtr(new MinUpCondition(barrier));
        }
    }
};

%rename(MinDownCondition) MinDownConditionPtr;
class MinDownConditionPtr : public boost::shared_ptr<AutocallCondition> {
  public:
    %extend {
        MinDownConditionPtr(Real barrier) {
            return new MinDownConditionPtr(new MinDownCondition(barrier));
        }
		MinDownConditionPtr(std::vector<Real> barrier) {
            return new MinDownConditionPtr(new MinDownCondition(barrier));
        }
    }
};

// allow use of diffusion AutocallCondition vectors
#if defined(SWIGCSHARP)
SWIG_STD_VECTOR_ENHANCED( boost::shared_ptr<AutocallCondition> )
#endif
%template(AutocallConditionVector)
std::vector<boost::shared_ptr<AutocallCondition> >;

typedef std::vector<boost::shared_ptr<AutocallCondition> > AutocallConditionVector;

// allow use of diffusion BasketPayoff vectors
#if defined(SWIGCSHARP)
SWIG_STD_VECTOR_ENHANCED( boost::shared_ptr<BasketPayoff> )
#endif
%template(BasketPayoffVector)
std::vector<boost::shared_ptr<BasketPayoff> >;

typedef std::vector<boost::shared_ptr<BasketPayoff> > BasketPayoffVector;





//Pricing Engine
%{
using QuantLib::FdAutocallEngine;
typedef boost::shared_ptr<PricingEngine> FdAutocallEnginePtr;
%}

%rename(FdAutocallEngine) FdAutocallEnginePtr;
class FdAutocallEnginePtr
    : public boost::shared_ptr<PricingEngine> {
  public:
    %extend {
        FdAutocallEnginePtr(
			const boost::shared_ptr<YieldTermStructure>& disc,
			const GeneralizedBlackScholesProcessPtr& process1,
			const GeneralizedBlackScholesProcessPtr& process2,
			Real correlation,
			Size xGrid = 100, Size yGrid = 100,	Size tGrid = 50) {
            boost::shared_ptr<GeneralizedBlackScholesProcess> bsProcess1 =
                 boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process1);
            QL_REQUIRE(bsProcess1, "Black-Scholes process required");
			boost::shared_ptr<GeneralizedBlackScholesProcess> bsProcess2 =
                 boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(process2);
            QL_REQUIRE(bsProcess2, "Black-Scholes process required");
            return new FdAutocallEnginePtr(
                          new FdAutocallEngine(disc, bsProcess1,bsProcess2,correlation,xGrid,yGrid,tGrid));
        }
    }
};






#endif