
#ifndef eq_autocallable_i
#define eq_autocallable_i

%include types.i
%include vectors.i
%include instruments.i
%include date.i
%include basketoptions.i

%{
using QuantLib::GeneralPayoff;
using QuantLib::AutocallableNote;
using QuantLib::AutocallCondition;
using QuantLib::MinUpCondition;
typedef boost::shared_ptr<Payoff> GeneralPayoffPtr;
typedef boost::shared_ptr<Instrument> AutocallableNotePtr;
typedef boost::shared_ptr<AutocallCondition> MinUpConditionPtr;
%}

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

%rename(GeneralPayoff) GeneralPayoffPtr;
class GeneralPayoffPtr : public boost::shared_ptr<Payoff> {
  public:
    %extend {
        GeneralPayoffPtr(const std::vector<Real> startPoints, const std::vector<Real> startPayoffs, const std::vector<Real> slopes) {
            return new GeneralPayoffPtr(new GeneralPayoff(startPoints, startPayoffs, slopes));
        }
    }
};

%rename(AutocallableNote) AutocallableNotePtr;
class AutocallableNotePtr : public Instrument {
  public:
    %extend {
        AutocallableNotePtr(const Real notionalAmt,
			const std::vector<Date>& autocallDates,
			const std::vector<Date>& paymentDates,
			const std::vector<boost::shared_ptr<AutocallCondition> >& autocallConditions,
			const std::vector<boost::shared_ptr<BasketPayoff> >& autocallPayoffs,
			const boost::shared_ptr<BasketPayoff> terminalPayoff) {
			
            return new AutocallableNotePtr(new AutocallableNote(
			notionalAmt, autocallDates, paymentDates, autocallConditions, autocallPayoffs, terminalPayoff));
			
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

#endif