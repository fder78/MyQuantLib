# -*- coding: utf-8 -*-
import QuantLib as ql
import market_data2curves as md

def getPrice(params):
    price = ql.single_rangeaccrual(params[0],params[1],params[2],params[3],params[4], \
                            params[5],params[6],params[7],params[8],params[9], \
                            params[10],params[11],params[12],params[13],params[14], \
                            params[15],params[16],params[17],params[18],params[19], \
                            params[20],params[21],params[22],params[23],params[24]) 
    return price
    

def calcSingleRangeAccrual(evaluationDate, notional, couponRate, gearing, schedule, dayCounter, bdc,
              lowerBound, upperBound, callDates, callValues, pastAccrual,	refCurve,  #12
              hwparams, discCurve, #16
              steps, invAlpha, invGearing, invFixing, cap, floor, alpha, pastFixing, tenors, calcVega): 
    
    params = [evaluationDate, notional, couponRate, gearing, schedule, dayCounter, bdc,
              lowerBound, upperBound, callDates, callValues, pastAccrual,	refCurve,  #12
              hwparams['a'], hwparams['tenor'], hwparams['sigma'], discCurve, #16
              steps, invAlpha, invGearing, invFixing, cap, floor, alpha, pastFixing]
              
    price0 = getPrice(params)
    res = [price0]

    bps = 1
    #ref curve Greeks
    for i in range(len(tenors)):
        quotes = []
        for j in range(len(tenors)):
            if i==j:
                quotes.append(ql.QuoteHandle(ql.SimpleQuote(0.0001*bps)))
            else:
                quotes.append(ql.QuoteHandle(ql.SimpleQuote(0.00)))
        #refCurve
        rts2 = ql.SpreadedLinearZeroInterpolatedTermStructure(ql.YieldTermStructureHandle(refCurve), quotes, tenors)
        p = params.copy()
        p[12] = rts2
        price = getPrice(p)
        res.append((price - price0)/bps)
        
    #Disc Curve Greeks
    for i in range(len(tenors)):
        quotes = []
        for j in range(len(tenors)):
            if i==j:
                quotes.append(ql.QuoteHandle(ql.SimpleQuote(0.0001*bps)))
            else:
                quotes.append(ql.QuoteHandle(ql.SimpleQuote(0.00)))        
        disc2 = ql.SpreadedLinearZeroInterpolatedTermStructure(ql.YieldTermStructureHandle(discCurve), quotes, tenors)
        p = params.copy()
        p[16] = disc2
        price = getPrice(p)
        res.append((price - price0)/bps)
    
    #Vegas
    if calcVega:
        swvol = hwparams['voldata']
        temp = []
        for i in range(len(swvol)):
            vol = []
            for j in range(len(swvol)):
                if i<=j:
                    vol.append((swvol[j][0], swvol[j][1], swvol[j][2]+0.0001*bps))
                else:
                    vol.append((swvol[j][0], swvol[j][1], swvol[j][2]))        
            hwparam1 = md.getHWcalibrationWithQuotesNormal(hwparams['date'], hwparams['index'], hwparams['curve'], vol, hwparams['a'])
            p = params.copy()        
            p[14] = hwparam1['tenor'].copy()
            p[15] = hwparam1['sigma'].copy()
            
            price = getPrice(p)
            temp.append((price - price0)/bps)
        for i in range(len(temp)):
            if i==len(temp)-1:
                res.append(temp[i])
            else:
                res.append(temp[i]-temp[i+1])
    
    return res