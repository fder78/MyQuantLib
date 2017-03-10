# -*- coding: utf-8 -*-

import QuantLib as ql
import time
from makeMarketData_EQ import ccy2index, getYieldCurve, getDividendCurveWithQuantoAdjustment

class StepDownELS:
    def __init__(self, today, notional, cpnRates, barriers, kibarrier, redmpDates, slopes, underlyings, discCode, mdata, isKI = False):
        self.today, self.notional, self.cpnRates = today, notional, cpnRates 
        self.barriers, self.redmpDates, self.slopes = barriers, redmpDates, slopes
        self.underlyings, self.discCode, self.mdata, self.isKI = underlyings, discCode, mdata, isKI
        self.kibarrier = kibarrier
        self.lastbarrier = kibarrier if kibarrier>0 else barriers[-1]
        self.tenor = int(12 / round((redmpDates[1] - redmpDates[0]).days / 30)) #num of months        
        self.n = len(self.underlyings[0])
        
    def initProduct(self):
        self.evaldate =  ql.Date(self.today.day, self.today.month, self.today.year)
        ql.Settings.instance().evaluationDate = self.evaldate 
        self.redmpDates = [ql.Date(d.day, d.month, d.year) for d in redmpDates]
        self.dates = ql.Schedule(self.redmpDates, ql.NullCalendar(), ql.Unadjusted)
        self.autocallConditions = ql.AutocallConditionVector()
        self.autocallPayoffs = ql.BasketPayoffVector()        
        
        for i in range(len(self.barriers)):
            b = self.barriers[i]
            s = self.slopes[i]
            p = 100*(1+self.cpnRates[i])
            condition = ql.MinUpCondition(b)
            self.autocallConditions.push_back(condition)
            redemptionPayoff = ql.MinBasketPayoff2(ql.GeneralPayoff([0,b-p/s,b],[0,0,p],[0,s,0]))
            self.autocallPayoffs.push_back(redemptionPayoff)
        
        #terminal payoff (Not Knocked in)
        tp = 100*(1 + self.cpnRates[-1])
        x = (self.slopes[-1]*self.lastbarrier - tp) / (self.slopes[-1] - 1)
        terPayoff = ql.GeneralPayoff([0,x,self.lastbarrier], [0,x,tp], [1,self.slopes[-1],0])
        self.terminalPayoff = ql.MinBasketPayoff2(terPayoff)
        self.product = ql.AutocallableNote(self.notional, self.dates, self.dates, self.autocallConditions, self.autocallPayoffs, self.terminalPayoff)
        
        #terminal payoff (Knocked in)
        if self.kibarrier>0:
            kip = ql.GeneralPayoff([0,self.barriers[-1]], [0,100*(1+self.cpnRates[-1])], [1,0])
            self.KIPayoff = ql.MinBasketPayoff2(kip)
            self.product.withKIBarrier(ql.MinDownCondition(self.kibarrier), self.KIPayoff)
            if self.isKI:
                self.product.hasKnockedIn()
                
    def calc(self, flatVol = [], method = "fd"):   
        self.initProduct()
        if len(flatVol)>0:
            if len(flatVol) != self.n:
                raise Exception("The Number of Flat Volatilities Not Matching")
            else:
                useFlatVol = True
        else:
            useFlatVol = False
        
        # market data
        mdata = self.mdata
        discountCurve = getYieldCurve(mdata, ccy2index(self.discCode))
        procs = ql.StochasticProcessVector()
        underlyingPrices = []
        c = 0
        for code, baseprice in zip(self.underlyings[0], self.underlyings[1]):            
            underlying = ql.SimpleQuote(100) if baseprice==0 else ql.SimpleQuote(100 * mdata['spot'][code] / baseprice)
            underlyingPrices.append(underlying.value())
            exdates = [ql.Date(d.day, d.month, d.year) for d in mdata['dates'][code]]
            vols = ql.Matrix(mdata['vol'][code].shape[0], mdata['vol'][code].shape[1])
            for i in range(mdata['vol'][code].shape[0]):
                for j in range(mdata['vol'][code].shape[1]):
                    vols[i][j] = mdata['vol'][code][i][j]
            bp = mdata['spot'][code] if baseprice==0 else baseprice
            strikes = [100*i/bp for i in mdata['stks'][code]]
            if useFlatVol:                
                volatility = ql.BlackConstantVol(self.evaldate, ql.SouthKorea(), flatVol[c], ql.Actual365Fixed())
                c+=1
            else:
                volatility = ql.BlackVarianceSurface(self.evaldate, ql.SouthKorea(), exdates, strikes, vols, ql.Actual365Fixed())                
            
            #volatility.enableExtrapolation()
            #volatility.setInterpolation("bicubic")
            dividendYield = getDividendCurveWithQuantoAdjustment(mdata, code, self.discCode)
            riskFreeRate = getYieldCurve(mdata, code)
            process = ql.BlackScholesMertonProcess(ql.QuoteHandle(underlying),
                                            ql.YieldTermStructureHandle(dividendYield),
                                            ql.YieldTermStructureHandle(riskFreeRate),
                                            ql.BlackVolTermStructureHandle(volatility))    
            procs.push_back(process)
        
        matrix = ql.Matrix(self.n, self.n, 1.0)
        for i in range(self.n-1):
            for j in range(i+1, self.n):
                matrix[i][j] = matrix[j][i] = mdata['corr'][(self.underlyings[0][i], self.underlyings[0][j])]
    
        process = ql.StochasticProcessArray(procs, matrix)
        if method=="fd":
            engine = ql.FdAutocallEngine(discountCurve, process, 200, 200)
        elif method=="mc":
            engine = ql.MCAutocallEngine(discountCurve, process, 10000)
        self.product.setPricingEngine(engine)
        
        res = {"underlyings": tuple(underlyingPrices),
               "npv": self.product.NPV(),
               "delta": self.product.delta(),
               "gamma": self.product.gamma(),
               "theta": self.product.theta(),
               "xgamma": self.product.xgamma()}
        return res

    def findCoupon(self, targetPrice, flatVol = []):
        temp = self.cpnRates
        c0, c1 = 0.01, 0.08
        self.cpnRates = [c0*(i+1) for i in range(len(temp))]
        p0 = self.calc(flatVol)["npv"]
        self.cpnRates = [c1*(i+1) for i in range(len(temp))]
        p1 = self.calc(flatVol)["npv"]
        self.cpnRates = temp
        print(p0,p1)
        return (c0 + (targetPrice-p0) / (p1-p0) *(c1-c0)) * self.tenor


class LizardStepDownELS(StepDownELS):
    def __init__(self, today, notional, cpnRates, barriers, kibarrier, redmpDates, slopes, underlyings, discCode, mdata, isKI = False):
        StepDownELS.__init__(self, today, notional, cpnRates, barriers, kibarrier, redmpDates, slopes, underlyings, discCode, mdata, isKI)
        self.lizardmuliple = 0.0
        
    def withLizardCouponMultiple(self, lizardmuliple):
        self.lizardmuliple = lizardmuliple
        
    def initProduct(self):
        if self.lizardmuliple==0.0:
            raise Exception("Lizard coupon should be given before calculation")
            
        self.evaldate =  ql.Date(self.today.day, self.today.month, self.today.year)
        ql.Settings.instance().evaluationDate = self.evaldate 
        self.redmpDates = [ql.Date(d.day, d.month, d.year) for d in redmpDates]
        self.dates = ql.Schedule(self.redmpDates, ql.NullCalendar(), ql.Unadjusted)
        self.autocallConditions = ql.AutocallConditionVector()
        self.autocallPayoffs = ql.BasketPayoffVector()        
        
        for i in range(len(self.barriers)):
            b = self.barriers[i]
            s = self.slopes[i]
            p = 100*(1+self.cpnRates[i])
            condition = ql.MinUpCondition(b)
            self.autocallConditions.push_back(condition)
            if i==1: #2번째 상환일에 리자드 payoff
                b = self.kibarrier
                p = 100*(1+self.lizardmuliple*self.cpnRates[i])
                gp = ql.GeneralPayoff([0,b-p/s,b,self.barriers[i]],[0,0,p,100*(1+self.cpnRates[i])],[0,s,0,0])
            else:
                gp = ql.GeneralPayoff([0,b-p/s,b],[0,0,p],[0,s,0])
            redemptionPayoff = ql.MinBasketPayoff2(gp)
            self.autocallPayoffs.push_back(redemptionPayoff)
        
        #terminal payoff (Not Knocked in)
        tp = 100*(1 + self.cpnRates[-1])
        x = (self.slopes[-1]*self.lastbarrier - tp) / (self.slopes[-1] - 1)
        terPayoff = ql.GeneralPayoff([0,x,self.lastbarrier], [0,x,tp], [1,self.slopes[-1],0])
        self.terminalPayoff = ql.MinBasketPayoff2(terPayoff)
        self.product = ql.AutocallableNote(self.notional, self.dates, self.dates, self.autocallConditions, self.autocallPayoffs, self.terminalPayoff)
        
        #terminal payoff (Knocked in)
        if self.kibarrier>0:
            kip = ql.GeneralPayoff([0,self.barriers[-1]], [0,100*(1+self.cpnRates[-1])], [1,0])
            self.KIPayoff = ql.MinBasketPayoff2(kip)
            self.product.withKIBarrier(ql.MinDownCondition(self.kibarrier), self.KIPayoff)
            if self.isKI:
                self.product.hasKnockedIn()
        

def plainvanilla(today, s, k, r, q, matDate, vol, flag):
    ql.Settings.instance().evaluationDate = ql.Date(today.day, today.month, today.year)
    riskFreeRate = ql.FlatForward(today, r, ql.Actual365Fixed())
    # option parameters
    exercise = ql.EuropeanExercise(matDate)
    if (flag.lower()=="c" or flag.lower()=="call"):
        optionType = ql.Option.Call
    else:
        optionType = ql.Option.Put
    payoff = ql.PlainVanillaPayoff(optionType, k)
    
    underlying = ql.SimpleQuote(s)
    volatility = ql.BlackConstantVol(today, ql.SouthKorea(), vol, ql.Actual365Fixed())
    dividendYield = ql.FlatForward(today, q, ql.Actual365Fixed())
    process = ql.BlackScholesMertonProcess(ql.QuoteHandle(underlying),
                                        ql.YieldTermStructureHandle(dividendYield),
                                        ql.YieldTermStructureHandle(riskFreeRate),
                                        ql.BlackVolTermStructureHandle(volatility))
    option = ql.VanillaOption(payoff, exercise)
    
    # method: analytic
    option.setPricingEngine(ql.AnalyticEuropeanEngine(process))
    res = {"npv":option.NPV(), "delta":option.delta()*0.01*s, "gamma":option.gamma()*((0.01*s)**2), "theta": option.theta()}
    return res
    
    
    
    
if __name__=='__main__':
    
    import datetime
    import dateutil.relativedelta as rd
    from makeMarketData_EQ import getMarketData
    today = datetime.datetime(2017,1,31)
    mdata = getMarketData(today)

    notional = 10000
    coupon = 0.04
    cpnRates = [coupon/2*i for i in range(1,7)]
    barriers = [90,90,85,85,80,70]
    kibarrier = 55
    issueDate = today    
    redmpDates = [issueDate] + [today + (i+1)*rd.relativedelta(months=6) for i in range(6)]
    slopes = [10000]*5 + [10000]
    underlyings = [("KOSPI2", "SX5E", "SPX"), (0, 0, 0)]
    underlyings = [("KOSPI2", "SX5E"), (0, 0)]
    discCode = "KRW"
    
    t0 = time.time()
    els = LizardStepDownELS(today, notional, cpnRates, barriers, kibarrier, redmpDates, slopes,
                      underlyings, discCode, mdata)
    els.withLizardCouponMultiple(2)
    
    
    els = StepDownELS(today, notional, cpnRates, barriers, kibarrier, redmpDates, slopes,
          underlyings, discCode, mdata, True)
    
    flatvol = [0.22, 0.22, 0.22]
    flatvol = [0.22, 0.22]
    #res = els.calc(flatvol)
    #print(res)
    
    cpn = 0.06#els.findCoupon(9850, flatvol)
    for i in range(10):
        els.cpnRates = [cpn/2*(i+1) for i in range(len(els.cpnRates))]
        flatvol = [0.25+i/100]*2
        flatvol = []
        #res = els.calc(flatvol)
        res2 = els.calc(flatvol, "mc")
        #print(res2)
        vol = 0 if len(flatvol)==0 else flatvol[0]
        print("vol = {0:0.2%}   price = {1:0.1f}, {2:0.1f}".format(vol, res2['npv'], res2['npv']*100))
    t1 = time.time()
    print("time = ", t1-t0)