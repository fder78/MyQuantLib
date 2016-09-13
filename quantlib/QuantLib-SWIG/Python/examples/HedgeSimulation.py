#Historical Data Loading
import pandas_datareader.data as pdd
if (not "sp" in vars()):
    sp = pdd.DataReader("^GSPC", "yahoo", start="01/01/2010").Close
if (not "fx" in vars()):
    fx = pdd.DataReader("KRW=X", "yahoo", start="01/01/2010").Close
if (not "ko" in vars()):
    ko = pdd.DataReader("KOSPI200", "google", start="01/01/2010").Close
if (not "ss" in vars()):
    ss = pdd.DataReader("KRX:005930", "google", start="01/01/2010").Close

#import packages
import pandas as pd
import numpy as np
import datetime as dt
from dateutil.relativedelta import relativedelta
from QuantLib import *
from StepDownELS import stepdownels, plainvanilla, couponfinder
import time

#Data Processing
temp = pd.read_csv("kospi_samsung.csv", parse_dates=[0],
                   date_parser=lambda x: pd.datetime.strptime(x, '%Y-%m-%d'))
temp.index = temp.pop("Date")
temp.drop(temp.columns[[0, 1]], axis=1, inplace=True)

d = pd.concat([sp,fx,ko,ss,temp], axis=1)
d.columns = ["SPX","USDKRW","K200","SE","CD","KTB"]
d.fillna(method="ffill", inplace=True)
d.dropna(inplace=True)
d["SPXinKRW"] = d.SPX * d.USDKRW / 1000

#Max issue date
maxDate = d.index[-1]-relativedelta(months=6)

#Market Parameters
v1, v2 = 0.220302, 0.211879
q1, q2 = 0.01, 0.01
corr = 0.6
discRate = 0.016
rf = 0.014

#ELS Parameters
stk = [95,95,90,90,85,60]
targetPrice = 9750
notional = 10000

today = dt.datetime(2010,1,6)
count = 0
printformat = "  %.4f"
t0 = time.time()

while today<=maxDate:    
    print(count+1,": ",today.strftime("%Y-%m-%d"),end=" ")
    todaysDate = Date(today.day, today.month, today.year)
    evaluationDate = todaysDate
    dateidx = d.index.get_loc(today)
    discRate = rf = d.ix[today].CD / 100.0
    spot1 = d.ix[today].K200      #발행기준가
    spot2 = d.ix[today].SPXinKRW    
    s1, s2 = 100, 100
    redmpDates = Schedule(todaysDate, todaysDate+Period(3,Years), Period(6,Months), NullCalendar(), Following, Following, DateGeneration.Forward, False)
    cpnRate = couponfinder(todaysDate, notional, targetPrice, stk, redmpDates, (s1,s2), (v1,v2), (q1,q2), corr, discRate, rf)
    
    #ELS valuation    
    res = stepdownels(todaysDate, notional, cpnRate, stk, redmpDates, (s1,s2), (v1,v2), (q1,q2), corr, discRate, rf)
    print(printformat%cpnRate, printformat%res["npv"])
    deltaAcc = notional  #Delta-Hedge Account
    (delta1, delta2) = res["delta"]
    (gamma1, gamma2) = res["gamma"]
    tradingAmt = delta1 + delta2
    #print(today.strftime("%Y-%m-%d"), printformat%res["npv"], (printformat+printformat)%(res["delta"]), (printformat+printformat)%(res["gamma"]))    
    
    #Option valuation
    optionMat = redmpDates[1]
    resOption1 = plainvanilla(todaysDate, s1, stk[0], rf, q1, optionMat, v1-0.01, "put") #발행보다 1% 낮은 vol 매도
    resOption2 = plainvanilla(todaysDate, s2, stk[0], rf, q2, optionMat, v2-0.01, "put")
    
    #매도 수량
    optionNum1 = gamma1 / resOption1["gamma"]
    optionNum2 = gamma2 / resOption2["gamma"]
    #매도 금액
    optionPrice1 = resOption1["npv"] * optionNum1
    optionPrice2 = resOption2["npv"] * optionNum2
    #Delta
    optionDelta1 = resOption1["delta"] * optionNum1
    optionDelta2 = resOption2["delta"] * optionNum2
    #Option Hedge Account
    optionAcc1 = optionPrice1
    optionAcc2 = optionPrice2
    #print(today.strftime("%Y-%m-%d"), printformat%resOption["npv"], printformat%(resOption["delta"]), printformat%(resOption["gamma"]))
    
    ii = 0
    while True:
        isRed = False        
        for it in range(2):
            #it=0 주간 , 1 야간            
            R1 = R2 = 0
            if it==0:
                ii += 1  #날짜 변경
                s1_temp = d.ix[dateidx+ii].K200 / spot1 * 100
                s2_temp = (d.ix[dateidx+ii].SPX * d.ix[dateidx+ii].USDKRW) / 1000 / spot2 * 100
                R1 = (s1_temp / s1 - 1.0)
                carry = (deltaAcc - (delta1*100 + delta2*100)*1.2) * rf / 365;
            else:
                s1_temp = d.ix[dateidx+ii].K200 / spot1 * 100
                s2_temp = d.ix[dateidx+ii].SPXinKRW / spot2 * 100
                R2 = (s2_temp / s2 - 1.0)  
                carry = 0
                
            pl1, pl2 = delta1*R1*100, delta2*R2*100
            deltaAcc = pl1 + pl2 + carry 
            s1, s2 = s1_temp, s2_temp    
            
            
            eDate = d.index[dateidx+ii]
            if eDate>=d.index[-1]:
                print("99999")
                isRed = true
                break
            
            evaluationDate = Date(eDate.day, eDate.month, eDate.year)
            
            '''
            if evaluationDate in redmpDates and it==0:
                evaluationDate = evaluationDate - Period(1,Days)  #중도상환일에 greek이 계산안되는 문제 해결
            '''
            
            if it==1:
                #상환여부처리   
                isRed0 = evaluationDate in redmpDates
                if isRed0:
                    i = [x for x in redmpDates].index(evaluationDate) - 1
                    isRed1 = isRed0 and s1>=stk[i] and s2>=stk[i]
                    if (isRed1 or evaluationDate==redmpDates[-1]):
                        isRed = True
                        x = notional * (1+cpnRate/2*(i+1))
                        if (evaluationDate==redmpDates[-1]):
                            i = redmpDates.size()-1
                            x = notional*(1+cpnRate*3)
                        if (not isRed1 and (s1 < stk[-1] or s2 < stk[-1])):
                            x = s1 if s1<s2 else s2
                            x *= notional / 100
                        print("[",i,"]",eDate.strftime("%Y-%m-%d"), "%.2f  %.2f  %.2f  %.2f"%(s1, s2, deltaAcc, x))
                        break
                    
            #오늘의 greek 계산
            #res = stepdownels(evaluationDate, notional, cpnRate, stk, redmpDates, (s1,s2), (v1,v2), (q1,q2), corr, discRate, rf)
            delta1_t, delta2_t = res["delta"]
            if it==0:
                tradingamt = np.abs(delta1_t-delta1)
                delta1 = delta1_t
            else:
                tradingamt = np.abs(delta2_t-delta2)
                delta2 = delta2_t
            elsPrice = res["npv"]
            
        if isRed:
            break
        
    count += 1
    today = today + relativedelta(days=7)
    
    #print computation time
    t1 = time.time()
    print("Time = %.1f" % (t1-t0))
    print("-"*50)
    t0 = t1
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    