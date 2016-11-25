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

#Max issue date
maxDate = d.index[-1]-relativedelta(months=6)

#Market Parameters
v1, v2 = 0.220302, 0.211879
q1, q2 = 0.01, 0.01
corr = 0.6

#ELS Parameters
stk = [95,95,90,90,85,60]
slopes = [4]*5 + [7]
targetPrice = 9750
notional = 10000

today = dt.datetime(2010,1,6)
#today = dt.datetime(2016,4,13)
count = 0
printformat = "  %.6f"
t0 = time.time()

fnames = ["els_price.csv","els_delta1.csv","els_delta2.csv","els_pf_pl1.csv","els_pf_pl2.csv","els_pf_carry.csv","els_pf_nav.csv","els_summary.csv"]
f = [open(fn,'w') for fn in fnames]
ofnames = ["op_price1.csv","op_price2.csv","op_delta1.csv","op_delta2.csv","op_pf_pl1.csv","op_pf_pl2.csv","op_pf_carry1.csv","op_pf_carry2.csv","op_pf_nav1.csv","op_pf_nav2.csv","op_summary1.csv","op_summary2.csv"]
of = [open(fn,'w') for fn in ofnames]

while today<=maxDate:    
    print(count+1,": ",today.strftime("%Y-%m-%d"),end=" ")
    for fn in f:
        fn.write(today.strftime("%Y-%m-%d")+",")
    for fn in of:
        fn.write(today.strftime("%Y-%m-%d")+",")
    todaysDate = Date(today.day, today.month, today.year)
    evaluationDate = todaysDate
    dateidx = d.index.get_loc(today)
    discRate = rf = d.ix[today].CD / 100.0
    spot1 = d.ix[today].K200      #발행기준가
    spot2 = d.ix[today].SE    
    s1, s2 = 100, 100
    redmpDates = Schedule(todaysDate, todaysDate+Period(3,Years), Period(6,Months), NullCalendar(), Following, Following, DateGeneration.Forward, False)
    cpnRate = couponfinder(todaysDate, notional, targetPrice, stk, redmpDates, (s1,s2), (v1,v2), (q1,q2), corr, discRate, rf, slopes)
    
    #ELS valuation    
    res = stepdownels(todaysDate, notional, cpnRate, stk, redmpDates, (s1,s2), (v1,v2), (q1,q2), corr, discRate, rf, slopes)
    print(printformat%cpnRate, printformat%res["npv"])
    f[-1].write(printformat%cpnRate + "," + printformat%res["npv"] + ",")
    deltaAcc = notional  #Delta-Hedge Account
    elsPrice = res["npv"]
    (delta1, delta2) = res["delta"]  #1% delta
    (gamma1, gamma2) = res["gamma"]  #1% gamma
    tradingAmt = delta1 + delta2
    #issue date print
    outvalue = [elsPrice, delta1, delta2, deltaAcc]
    for n, fn in enumerate([f[i] for i in (0,1,2,6)]):
        fn.write("%.4f,"%outvalue[n])    
    
    #Option valuation
    optionMat = redmpDates[1]
    strike = stk[0]
    resOption1 = plainvanilla(todaysDate, s1, strike, rf, q1, optionMat, v1-0.01, "put") #발행보다 1% 낮은 vol 매도
    resOption2 = plainvanilla(todaysDate, s2, strike, rf, q2, optionMat, v2-0.01, "put")
    
    #매도 수량
    optionNum1 = - gamma1 / resOption1["gamma"]
    optionNum2 = - gamma2 / resOption2["gamma"]
    #매도 금액
    optionPrice1 = resOption1["npv"] * optionNum1
    optionPrice2 = resOption2["npv"] * optionNum2
    #Delta
    optionDelta1 = resOption1["delta"] * optionNum1
    optionDelta2 = resOption2["delta"] * optionNum2
    #Option Hedge Account
    optionAcc1 = optionPrice1
    optionAcc2 = optionPrice2
    
    #issue date print
    outvalue = [optionPrice1, optionPrice2, optionDelta1, optionDelta2, optionAcc1, optionAcc2]
    for n, fn in enumerate([of[i] for i in (0,1,2,3,8,9)]):
        fn.write("%.4f,"%outvalue[n]) 
    
    ii = 1
    x1 = x2 = 0
    while True:
        isRed = False
        #아직 상환 또는 종료되지 않은 ELS는 시뮬레이션 중지
        eDate = d.index[dateidx+ii]
        if eDate>=d.index[-1]:
            print("99999")
            isRed = True
            for fn in f:
                fn.write("99999\n")
            for fn in of:
                fn.write("99999\n")
            break
        
        evaluationDate = Date(eDate.day, eDate.month, eDate.year)
        
        R1 = R2 = 0
        s1_temp = d.ix[dateidx+ii].K200 / spot1 * 100
        s2_temp = d.ix[dateidx+ii].SE / spot2 * 100
        carry = (deltaAcc - (delta1*100 + delta2*100)*1.2) * rf / 365
        carry_1 = (optionAcc1 - optionDelta1*100*1.2) * rf / 365
        carry_2 = (optionAcc2 - optionDelta2*100*1.2) * rf / 365
            
        R1 = (s1_temp / s1 - 1.0)
        R2 = (s2_temp / s2 - 1.0)
        pl1, pl2, optionPL1, optionPL2 = delta1*R1*100, delta2*R2*100, optionDelta1*R1*100, optionDelta2*R2*100
        deltaAcc += pl1 + pl2 + carry
        optionAcc1 += optionPL1 + carry_1
        optionAcc2 += optionPL2 + carry_2
        s1, s2 = s1_temp, s2_temp
            
        isRed0 = evaluationDate in redmpDates  #조기행사일인지?
        #상환여부처리               
        if isRed0: #조기상환일이면
            x1 += np.maximum(strike - s1, 0) * optionNum1
            x2 += np.maximum(strike - s2, 0) * optionNum2
            i = [x for x in redmpDates].index(evaluationDate) - 1
            isRed1 = isRed0 and s1>=stk[i] and s2>=stk[i]   #조기상환조건 만족하면 또는
            if (isRed1 or evaluationDate==redmpDates[-1]):  #마지막 상환일이면
                isRed = True
                x = notional * (1+cpnRate/2*(i+1))
                if (evaluationDate==redmpDates[-1]):
                    i = len(redmpDates)-1
                    x = notional*(1+cpnRate*3)  #dummy coupon
                if (not isRed1 and (s1 < stk[-1] or s2 < stk[-1])):
                    x = s1 if s1<s2 else s2
                    x *= notional / 100                        
                #realized vol
                rv = np.log(d[dateidx:dateidx+ii+1]).diff().std()*np.sqrt(365)
                cr = np.log(d[dateidx:dateidx+ii+1]).diff().corr()['K200']['SE']
                print("[",i,"]",eDate.strftime("%Y-%m-%d"), "%.2f  %.2f  %.2f  %.2f  %.2f  %.2f  %.2f"
                %(s1, s2, rv.K200, rv.SE, deltaAcc, x, deltaAcc-x))
                f[-1].write("%d"%(i+1) + "," + eDate.strftime("%Y-%m-%d") + 
                ",%.2f,%.2f,%.4f,%.4f,%.2f,%.2f,%.2f,%.4f" %(s1, s2, rv.K200, rv.SE, deltaAcc, x, deltaAcc-x, cr))                        
                of[-2].write("%d"%(i+1) + "," + eDate.strftime("%Y-%m-%d") + 
                ",%.2f,%.4f,%.2f,%.2f,%.2f" %(s1, rv.K200, optionAcc1, x1, optionAcc1-x1))                      
                of[-1].write("%d"%(i+1) + "," + eDate.strftime("%Y-%m-%d") + 
                ",%.2f,%.4f,%.2f,%.2f,%.2f" %(s2, rv.SE, optionAcc2, x2, optionAcc2-x2))
                
            else:
                #roll-over
                optionMat = redmpDates[i+2]
                strike = stk[i+1]
                res = stepdownels(evaluationDate, notional, cpnRate, stk, redmpDates, (s1,s2), (v1,v2), (q1,q2), corr, discRate, rf, slopes)
                resOption1 = plainvanilla(evaluationDate, s1, strike, rf, q1, optionMat, v1-0.01, "put") #발행보다 1% 낮은 vol 매도
                resOption2 = plainvanilla(evaluationDate, s2, strike, rf, q2, optionMat, v2-0.01, "put")
                (gamma1, gamma2) = res["gamma"]  #1% gamma
                optionNum1 = - gamma1 / resOption1["gamma"]
                optionNum2 = - gamma2 / resOption2["gamma"]
                #매도 금액
                optionPrice1 = resOption1["npv"] * optionNum1
                optionPrice2 = resOption2["npv"] * optionNum2
                #Delta
                optionDelta1 = resOption1["delta"] * optionNum1
                optionDelta2 = resOption2["delta"] * optionNum2
                #Option Hedge Account
                optionAcc1 += optionPrice1
                optionAcc2 += optionPrice2
                    
        #오늘의 greek 계산
        ii += 1
        if (not isRed0):
            res = stepdownels(evaluationDate, notional, cpnRate, stk, redmpDates, (s1,s2), (v1,v2), (q1,q2), corr, discRate, rf, slopes)
            resOption1 = plainvanilla(evaluationDate, s1, strike, rf, q1, optionMat, v1-0.01, "put") #발행보다 1% 낮은 vol 매도
            resOption2 = plainvanilla(evaluationDate, s2, strike, rf, q2, optionMat, v2-0.01, "put")

        delta1_t, delta2_t = res["delta"]
        tradingamt = np.abs(delta1_t-delta1) + np.abs(delta2_t-delta2)
        delta1 = delta1_t
        delta2 = delta2_t
        elsPrice = res["npv"]
        
        outvalue = [elsPrice, delta1, delta2, pl1, pl2, carry, deltaAcc]
        for n, fn in enumerate(f[:-1]):
            fn.write("%.4f,"%outvalue[n])                
            
        #매도 금액
        optionPrice1 = resOption1["npv"] * optionNum1
        optionPrice2 = resOption2["npv"] * optionNum2
        #Delta
        optionDelta1 = resOption1["delta"] * optionNum1
        optionDelta2 = resOption2["delta"] * optionNum2                     
     
        outvalue = [x1+optionPrice1, x2+optionPrice2, optionDelta1, optionDelta2, optionPL1, optionPL2, carry_1, carry_2, optionAcc1, optionAcc2]
        for n, fn in enumerate(of[:-2]):
            fn.write("%.4f,"%outvalue[n])
    
        if isRed:
            for fn in f:
                fn.write("\n")
            for fn in of:
                fn.write("\n")
            break   
    
    #one hedge simulation finished
    count += 1
    today = today + relativedelta(days=7)
    
    #print computation time
    t1 = time.time()
    print("Time = %.1f" % (t1-t0))
    print("-"*50)
    t0 = t1
    
for fn in f:
    fn.close()
for fn in of:
    fn.close()
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    