from QuantLib import *

def stepdownels(today, notional, cpnRate, barriers, redmpDates, underlyings, vols, divs, correlation, discRate, rf, slopes=[1000]*6):

    Settings.instance().evaluationDate = today
    dates = redmpDates
    autocallConditions = AutocallConditionVector();
    autocallPayoffs = BasketPayoffVector();
    
    for i in range(1,7):
        b = barriers[i-1]
        s = slopes[i-1]
        p = 100*(1+cpnRate*i/2.0)
        condition = MinUpCondition(b)
        autocallConditions.push_back(condition)
        redemptionPayoff = MinBasketPayoff2(GeneralPayoff([0,b-p/s,b],[0,0,p],[0,s,0]))
        autocallPayoffs.push_back(redemptionPayoff)
    
    tp = 100*(1+cpnRate*3)
    x = (slopes[-1]*barriers[-1] - tp) / (slopes[-1] - 1)
    terPayoff = GeneralPayoff([0,x,barriers[-1]], [0,x,tp], [1,slopes[-1],0])
    terminalPayoff = MinBasketPayoff2(terPayoff)
    product = AutocallableNote(notional, dates, dates, autocallConditions, autocallPayoffs, terminalPayoff)
    #product.withKIBarrier(MinDownCondition(55), MinBasketPayoff2(KIPayoff))
    #product.hasKnockedIn()
    
    # market data
    discountCurve = FlatForward(today, discRate, Actual365Fixed())
    riskFreeRate = FlatForward(today, rf, Actual365Fixed())
    underlying1 = SimpleQuote(underlyings[0])
    underlying2 = SimpleQuote(underlyings[1])    
    volatility1 = BlackConstantVol(today, SouthKorea(), vols[0], Actual365Fixed())
    volatility2 = BlackConstantVol(today, SouthKorea(), vols[1], Actual365Fixed())
    dividendYield1 = FlatForward(today, divs[0], Actual365Fixed())
    dividendYield2 = FlatForward(today, divs[1], Actual365Fixed())
    
    process1 = BlackScholesMertonProcess(QuoteHandle(underlying1),
                                        YieldTermStructureHandle(dividendYield1),
                                        YieldTermStructureHandle(riskFreeRate),
                                        BlackVolTermStructureHandle(volatility1))
    
    process2 = BlackScholesMertonProcess(QuoteHandle(underlying2),
                                        YieldTermStructureHandle(dividendYield2),
                                        YieldTermStructureHandle(riskFreeRate),
                                        BlackVolTermStructureHandle(volatility2))
    
    engine = FdAutocallEngine(discountCurve, process1, process2, correlation)
    product.setPricingEngine(engine)
    
    res = {"npv":product.NPV(),
           "delta":product.delta(),
           "gamma":product.gamma(),
           "theta": product.theta(),
           "xgamma":product.xgamma()}
    return res



def couponfinder(today, notional, targetPrice, barriers, redmpDates, underlyings, vols, divs, correlation, discRate, rf, slopes=[1000]*6):
    c0 = 0.04
    c1 = 0.07
    p0 = stepdownels(today, notional, c0, barriers, redmpDates, underlyings, vols, divs, correlation, discRate, rf, slopes)["npv"]
    p1 = stepdownels(today, notional, c1, barriers, redmpDates, underlyings, vols, divs, correlation, discRate, rf, slopes)["npv"]
    return c0 + (targetPrice-p0) / (p1-p0) *(c1-c0)  



def plainvanilla(today, s, k, r, q, matDate, vol, flag):
    Settings.instance().evaluationDate = today
    riskFreeRate = FlatForward(today, r, Actual365Fixed())
    # option parameters
    exercise = EuropeanExercise(matDate)
    if (flag.lower()=="c" or flag.lower()=="call"):
        optionType = Option.Call
    else:
        optionType = Option.Put
    payoff = PlainVanillaPayoff(optionType, k)
    
    underlying = SimpleQuote(s)
    volatility = BlackConstantVol(today, SouthKorea(), vol, Actual365Fixed())
    dividendYield = FlatForward(today, q, Actual365Fixed())
    process = BlackScholesMertonProcess(QuoteHandle(underlying),
                                        YieldTermStructureHandle(dividendYield),
                                        YieldTermStructureHandle(riskFreeRate),
                                        BlackVolTermStructureHandle(volatility))
    option = VanillaOption(payoff, exercise)
    
    # method: analytic
    option.setPricingEngine(AnalyticEuropeanEngine(process))
    res = {"npv":option.NPV(), "delta":option.delta()*0.01*s, "gamma":option.gamma()*((0.01*s)**2), "theta": option.theta()}
    return res
    
    
    
    
if __name__=='__main__':
    print("MAIN")

    today = Date.todaysDate()
    notional = 10000
    cpnRate = 0.06
    stk = [95,95,90,90,85,60]
    redmpDates = Schedule(today, today+Period(3,Years), Period(6,Months), NullCalendar(), Following, Following, DateGeneration.Forward, False)
    underlyings = [100,100]
    vols = [0.2, 0.2]
    divs = [0.01, 0.01]
    correlation = 0.6
    discRate = 0.025
    rf = 0.02
    slopes = [10]*5 + [10]
    
    res = stepdownels(today, notional, cpnRate, stk, redmpDates, underlyings, vols, divs, correlation, discRate, rf, slopes)
    print(res)