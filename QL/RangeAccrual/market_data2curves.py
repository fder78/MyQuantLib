import bdh
import datetime as dt
import pymysql
import QuantLib as ql
from curve_builder import buildCurve

def makeYieldCurve(code, date, tenors=[]):
#    todaysDate = ql.Date(date.day, date.month, date.year)
#    return ql.FlatForward(todaysDate, 0.021, ql.Actual360())
    
    conn = pymysql.connect(host='fdos-mt', user='root', password='3450', charset='utf8')   
    sql1 = 'SELECT * FROM ficc_drvs.curves WHERE receivedate="%s" AND CurveCode = "%s";' % (dt.datetime.strftime(date,"%Y-%m-%d"), code)
    curs = conn.cursor() 
    curs.execute(sql1)
    mdataFGN = curs.fetchall()

    pparse = ql.PeriodParser()
    dparse = ql.DateParser()
    numOfDeposit = 0
    numOfFutures = 0
    for i in range(len(mdataFGN)):
        if numOfDeposit==0 and len(mdataFGN[i][3])==5:
            numOfDeposit = i
        elif numOfFutures==0 and numOfDeposit!=0 and len(mdataFGN[i][3])!=5:
            numOfFutures = i - numOfDeposit
        
    deposits = {"quote": []}
    for i in range(numOfDeposit):
        deposits["quote"].append( (pparse.parse(mdataFGN[i][3]), ql.SimpleQuote(mdataFGN[i][4])) )
    deposits["dc"] = ql.Actual360()
    deposits["settlementDays"] = 2
    deposits["bdc"] = ql.ModifiedFollowing

    futures = {"quote": []}
    for i in range(numOfDeposit, numOfDeposit+numOfFutures):
        d0 = dparse.parse(mdataFGN[i][3], "%y%b")
        d0 = dt.datetime(d0.year(), d0.month(), d0.dayOfMonth())
        x = (9 - d0.weekday()) % 7 + 15
        d0 = ql.Date(x, d0.month, d0.year)
        futures["quote"].append( (d0, ql.SimpleQuote(mdataFGN[i][4])) )
    futures["maturity"] = 3
    futures["dc"] = ql.Actual360()
    futures["bdc"] = ql.ModifiedFollowing

    swaps = {"quote": []}
    for i in range(numOfDeposit+numOfFutures, len(mdataFGN)):
        swaps["quote"].append( (pparse.parse(mdataFGN[i][3]), ql.SimpleQuote(mdataFGN[i][4])) )
    swaps["fixedDC"] = ql.Actual365Fixed()
    swaps["freq"] = ql.Quarterly
    swaps["index"] = ql.USDLibor(ql.Period(3,ql.Months))
    
    calendar = ql.SouthKorea()
    if code=="USD":
        calendar = ql.UnitedKingdom()
    
    todaysDate = ql.Date(date.day, date.month, date.year)
    settlementDate = todaysDate
    dayCounter = ql.Actual365Fixed()

    curve = buildCurve(todaysDate, settlementDate, deposits, futures, swaps, calendar, dayCounter, tenors)   
    return curve
    
    
def getHWcalibrationWithQuotes(settlementDate, index, termStructure, swaptionVols, a = 0.1):
    
    helpers = [ ql.SwaptionHelper(maturity, length, ql.QuoteHandle(ql.SimpleQuote(vol)), index, index.tenor(), index.dayCounter(), index.dayCounter(), termStructure)
                for maturity, length, vol in swaptionVols ]    
    dates = [ settlementDate+maturity for maturity, length, vol in swaptionVols ]
    sigma = [0.005] * len(dates)
    model = ql.Generalized_HullWhite(termStructure, dates, sigma, a)

    for h in helpers:
        h.setPricingEngine(ql.JamshidianSwaptionEngine(model))
        
    method = ql.LevenbergMarquardt();
    model.calibrate(helpers, method, ql.EndCriteria(1000, 250, 1e-7, 1e-7, 1e-7))
    sigma = list(model.params())
    implied, error, npv = [],[],[]
    for swaption, helper in zip(swaptionVols, helpers):
        maturity, length, vol = swaption
        NPV = helper.modelValue()
        iv = helper.impliedVolatility(NPV, 1.0e-4, 1000, 0.01, 2.50)
        implied.append( iv )
        error.append( iv - vol )
        npv.append(NPV)
        
    return {"curve": termStructure, "index": index, "date": settlementDate, "a": a, "tenor":dates, 
    "sigma":sigma, "voldata":swaptionVols, "modelimplied":implied, "error":error, "npv":npv}


def getHWcalibrationWithQuotesNormal(settlementDate, index, termStructure, swaptionVols, a = 0.1):
    
    helpers = [ ql.SwaptionHelper(maturity, length, ql.QuoteHandle(ql.SimpleQuote(vol)), index, index.tenor(), index.dayCounter(),\
                                  index.dayCounter(), termStructure, ql.CalibrationHelper.PriceError, ql.nullDouble(), 1.0, ql.Normal)
                for maturity, length, vol in swaptionVols ]    
    dates = [ settlementDate+maturity for maturity, length, vol in swaptionVols ]
    sigma = [0.005] * len(dates)
    model = ql.Generalized_HullWhite(termStructure, dates, sigma, a)

    for h in helpers:
        h.setPricingEngine(ql.JamshidianSwaptionEngine(model))
        
    method = ql.LevenbergMarquardt();
    model.calibrate(helpers, method, ql.EndCriteria(1000, 250, 1e-7, 1e-7, 1e-7))
    sigma = list(model.params())
    implied, error = [],[]
    for swaption, helper in zip(swaptionVols, helpers):
        maturity, length, vol = swaption
        NPV = helper.modelValue()
        iv = helper.impliedVolatility(NPV, 1.0e-4, 1000, 0.00001, 0.5)
        implied.append( iv )
        error.append( iv - vol )
        
    return {"curve": termStructure, "index": index, "date": settlementDate, "a": a, "tenor":dates, "sigma":sigma, "voldata":swaptionVols, "modelimplied":implied, "error":error}
    

def getHWcalibration(code, date, targetDate, a = 0.1):

    todaysDate = ql.Date(date.day, date.month, date.year)
    tDate = ql.Date(targetDate.day, targetDate.month, targetDate.year)
    ql.Settings.instance().evaluationDate = todaysDate
    settlementDate = todaysDate
    
    termStructure = makeYieldCurve(code, date)
    termStructure = ql.YieldTermStructureHandle(termStructure)
    termStructure.allowsExtrapolation()
    
    index = ql.USDLibor(ql.Period(6, ql.Months), termStructure)
    pp = ql.PeriodParser()
    
    conn = pymysql.connect(host='fdos-mt', user='root', password='3450', charset='utf8')   
    sql1 = 'SELECT Tenor, Value FROM ficc_drvs.curves WHERE receivedate="%s" AND CurveCode = "%s";' % (dt.datetime.strftime(date,"%Y-%m-%d"), code+"_SWTVOL")
    curs = conn.cursor() 
    curs.execute(sql1)
    mvol = curs.fetchall()
    swaptionVols = []
    for d in mvol:
        temp = d[0].split("_")
        p1 = pp.parse(temp[0])
        p2 = pp.parse(temp[1])
        if todaysDate+p1+p2 > tDate and todaysDate+p1<termStructure.maxDate(): ## 상품만기 tDATE를 초과하는 첫번째 스왑
            if len(swaptionVols)==0:
                swaptionVols.append((p1,p2,d[1]))
            elif p1>swaptionVols[-1][0]:
                swaptionVols.append((p1,p2,d[1]))
                
    temp = getHWcalibrationWithQuotes(settlementDate, index, termStructure, swaptionVols, a)
    normalSwaptionVols = []
    for i, sv in enumerate(swaptionVols):
        npv = temp['npv'][i]
        helper = ql.SwaptionHelper(sv[0], sv[1], ql.QuoteHandle(ql.SimpleQuote(0.01)), index, index.tenor(), index.dayCounter(),\
                                  index.dayCounter(), termStructure, ql.CalibrationHelper.PriceError, ql.nullDouble(), 1.0, ql.Normal)
        normalVol = helper.impliedVolatility(npv, 1.0e-4, 1000, 0.00001, 0.5)
        normalSwaptionVols.append((sv[0],sv[1],normalVol))
        
    return getHWcalibrationWithQuotesNormal(settlementDate, index, termStructure, normalSwaptionVols, a)
    
    
    
if __name__=="__main__":
    #res = getHWcalibration("USD", dt.datetime(2017,1,10), dt.datetime(2027,6,30))
    
    c = makeYieldCurve("USD", dt.datetime(2016,12,22))
    for i in range(10):
        print(c.discount(i))
    