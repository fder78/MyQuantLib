
from QuantLib import *

# global data
def buildCurve(todaysDate, settlementDate, deposits, futures, swaps, calendar, dc, tenors=[]):
    
    Settings.instance().evaluationDate = todaysDate

    # build rate helpers
    ddc = deposits["dc"]
    settlementDays = deposits["settlementDays"]
    dbdc = deposits["bdc"]
    depositHelpers = [ DepositRateHelper(QuoteHandle(unit),
                                         n, settlementDays,
                                         calendar, dbdc,
                                         False, ddc)
                       for n, unit in deposits["quote"] ]    
    
    months = futures["maturity"]
    fdc = deposits["dc"]
    fbdc = deposits["bdc"]
    futuresHelpers = []
    lastDate = calendar.adjust(todaysDate + deposits["quote"][-1][0], fbdc)
    for n, unit in futures["quote"]:
        if (calendar.adjust(n+Period(months,Months),fbdc)>lastDate+Period(1,Weeks)):
            futuresHelpers.append(FuturesRateHelper(QuoteHandle(unit),
                                                    n, months,
                                                    calendar, fbdc,
                                                    True, fdc,
                                                    QuoteHandle(SimpleQuote(0.0))))
    if len(futures["quote"])>0:
        lastDate = calendar.adjust(futures["quote"][-1][0] + Period(months,Months), fbdc)

    fixedLegAdjustment = Unadjusted
    fixedLegDayCounter = swaps["fixedDC"]
    fixedLegFrequency = swaps["freq"]
    floatingIndex = swaps["index"]
    swapHelpers = []
    for n, unit in swaps["quote"]:
        if (todaysDate+n > lastDate):
            swapHelpers.append(SwapRateHelper(QuoteHandle(unit),
                                              n, calendar,
                                              fixedLegFrequency, fixedLegAdjustment,
                                              fixedLegDayCounter, floatingIndex))
    # term-structure construction    
    helpers = depositHelpers + futuresHelpers + swapHelpers
    rts = PiecewiseLinearZero(settlementDate, helpers, dc)
    if len(tenors)>0:
        zerorates = [rts.zeroRate(i, rts.dayCounter(), Continuous).rate() for i in tenors]
        rts = ZeroCurve(tenors, zerorates, rts.dayCounter())
    return rts
    

if __name__=="__main__":
    calendar = TARGET()
    todaysDate = Date(6,November,2001);
    settlementDate = Date(8,November,2001);
    dayCounter = Actual360()
    
    # market quotes
    deposits = {"quote": [ (Period(1,Weeks), SimpleQuote(0.0382)),
                 (Period(1,Months), SimpleQuote(0.0372)),
                 (Period(3,Months), SimpleQuote(0.0363)),
                 (Period(6,Months), SimpleQuote(0.0353)),
                 (Period(9,Months), SimpleQuote(0.0348)),
                 (Period(1,Years), SimpleQuote(0.0345)) ],
                 "dc": Actual360(),
                 "settlementDays": 2, 
                 "bdc": ModifiedFollowing }
    
    futures = {"quote": [ (Date(19,12,2001), SimpleQuote(96.2875)),
                (Date(20,3,2002), SimpleQuote(96.7875)),
                (Date(19,6,2002), SimpleQuote(96.9875)),
                (Date(18,9,2002), SimpleQuote(96.6875)),
                (Date(18,12,2002), SimpleQuote(96.4875)),
                (Date(19,3,2003), SimpleQuote(96.3875)),
                (Date(18,6,2003), SimpleQuote(96.2875)),
                (Date(17,9,2003), SimpleQuote(96.0875)) ],
                "maturity": 3, "dc": Actual360(), "bdc": ModifiedFollowing }
    
    swaps = {"quote": [ (Period(2,Years), SimpleQuote(0.037125)),
              (Period(3,Years), SimpleQuote(0.0398)),
              (Period(5,Years), SimpleQuote(0.0443)),
              (Period(10,Years), SimpleQuote(0.05165)),
              (Period(15,Years), SimpleQuote(0.055175)) ], 
              "fixedDC": Thirty360(), "freq": Quarterly, "index": USDLibor(Period(3,Months)) }
              
    curve = buildCurve(todaysDate, settlementDate, deposits, futures, swaps, calendar, dayCounter)
    
    import numpy as np
    r = np.zeros(30)
    t = np.linspace(0,15,30)
    for i in range(30):
        r[i] = curve.zeroRate(t[i],Continuous).rate()
    import matplotlib.pyplot as plt
    plt.plot(t, r, 's-')
    plt.show()