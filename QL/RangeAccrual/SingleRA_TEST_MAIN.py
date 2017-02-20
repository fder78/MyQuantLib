
# -*- coding: utf-8 -*-
"""
Created on Wed Jan 25 17:45:30 2017

@author: Daishin
"""
import market_data2curves as md
import datetime as dt
import sys
import pymysql
import dataparser as dp
conn = pymysql.connect(host='fdos-mt', user='root', password='3450', charset='utf8')
curs = conn.cursor()

#FICC RANGE ACCUAL
import QuantLib as ql
import singleRA_greeks as sra
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#todaysDate = ql.Date.todaysDate()
codeID = "DLS630"
codeID = "DLB128"
conn2 = pymysql.connect(host='10.50.20.105', user='neo', password='neo', charset='utf8')
curs2 = conn2.cursor()
curs2.execute("select * from cdra.dls_org where simplename='%s'"%codeID)
temp = curs2.fetchall()
temp = [i for i in temp]
productData = pd.DataFrame(temp, columns = [d[0] for d in curs2.description])

############################################################################################
notional = float(productData.Notional)
couponRate = [float(productData.AccrualRate)]
effDate = productData.EffectiveDate[0]
terDate = productData.TerminationDate[0]
callDate = productData.CallStartDate[0]
startDate = ql.Date(effDate.day,effDate.month,effDate.year)
termDate = ql.Date(terDate.day,terDate.month,terDate.year)
callDate = ql.Date(callDate.day,callDate.month,callDate.year)
callTenor = dp.str2period(productData.CallTenor[0])
couponTenor = dp.str2period(productData.Tenor[0])
bdc = dp.str2bdc(productData.BDC[0])
dayCounter = dp.str2dc(productData.DayCounterAccrual[0])

schedule = ql.Schedule(startDate, termDate, couponTenor, ql.SouthKorea(), bdc, bdc, ql.DateGeneration.Forward, False)
callSchedule = ql.Schedule(callDate, termDate, callTenor, ql.SouthKorea(), bdc, bdc, ql.DateGeneration.Forward, False)
callValue = [float(productData.CallValue)] * len(callSchedule)

lowerBound = [float(productData.Obs1LowerLevel[0])]
upperBound = [float(productData.Obs1UpperLevel[0])]


nullvalue = ql.nullDouble()
invGearing = productData.InvGearing[0]
invGearing = float(invGearing) if invGearing!=None else nullvalue
invCap = productData.InvGearing[0]
invCap = float(invCap) if invCap!=None else nullvalue
invFloor = productData.InvGearing[0]
invFloor = float(invFloor) if invFloor!=None else nullvalue
############################################################################################


steps = 200
a = 0.1
sigma = [0.035, 0.035]

res = []; dbres = []
curvediff = []
dates = []
tDate = dt.datetime(termDate.year(), termDate.month(), termDate.dayOfMonth())


#############################################################################################
#SIMULATION
#############################################################################################
n = 130
sDate = dt.datetime(2016,10,12)
pp = ql.PeriodParser()
hwparams = dict()
tenorPeriod = ['0d'] + [str(i)+'m' for i in [1,2,3,6,9]] + [str(i)+'y' for i in [1,2,3,5,7,10,15,20,25,30]]
calcVega = True

for it in range(n):
    d = sDate + dt.timedelta(it)
    todaysDate = ql.Date(d.day,d.month,d.year)
    tenors = []
    pp = ql.PeriodParser() 
    for i in tenorPeriod:
        tenors.append(todaysDate + pp.parse(i))
        
    try: 
        #market data가 없으면 continue
        if d.weekday()>=5: continue
        rts = md.makeYieldCurve("USD", d)
        discCurve = md.makeYieldCurve("USD", d)
        if calcVega or hwparams=={}:
            hwparams = md.getHWcalibration("USD", d, tDate)
      
        pastAccrual = (todaysDate - schedule[0])
        price = sra.calcSingleRangeAccrual(todaysDate, notional, couponRate, [1.0e-50], schedule, dayCounter, bdc, lowerBound, upperBound, 
                                callSchedule, callValue, pastAccrual, rts, hwparams, discCurve, steps, 
                                0.0065, #inv alpha
                                invGearing, #inv gearing
                                0.005, #inv fixing
                                invCap, #cap
                                invFloor, #floor
                                
                                nullvalue, #alpha
                                nullvalue, #past fixing
                                tenors, calcVega)
        res.append(price)
        print(todaysDate.ISO(), price[0])
        dates.append(todaysDate.ISO())
        
        #yield curves changes
        cdf = []
        for i in tenorPeriod:
            cdf.append(rts.zeroRate(todaysDate+pp.parse(i), rts.dayCounter(), ql.Continuous).rate())        
        for i in tenorPeriod:
            cdf.append(discCurve.zeroRate(todaysDate+pp.parse(i), discCurve.dayCounter(), ql.Continuous).rate())   
        if calcVega:
            for i in hwparams['voldata']:
                cdf.append(i[2])
        curvediff.append(cdf)        
        
        ###DB PRICE
#        sql1 = """SELECT UnitPrice FROM ficc_drvs.callable_price_test WHERE evaldate='%d-%02d-%02d' 
#        """ % (d.year, d.month, d.day) + \
#        r""" AND CODE like '%libor32%' """;
#        curs.execute(sql1)
#        pricedb = curs.fetchall()
#        pricedb = -1.0*pricedb[0][0]
#        dbres.append(pricedb)
        
    except IndexError:
        print(todaysDate.ISO(), sys.exc_info())
        pass


#############################################################################################
#PLOT RESULTS
#############################################################################################
res = np.array(res)
cdiff = np.diff(np.array(curvediff).T).T * 10000
delta = res[:-1,1:]
plgreek = (cdiff*delta).sum(1)
plprice = np.diff(res[:,0])

fig, ax = plt.subplots(3,1,figsize=(10,15))
ax[0].plot(res[:,0])
ax[0].set_title("Price")
ax[1].bar(range(1,len(res[:,0])), np.diff(res[:,0]))
ax[1].set_title("Price Diff")
width = 0.35
ax[2].bar(range(len(plgreek)), plgreek, width, color="r")
ax[2].bar(np.arange(len(plgreek))+width, plprice, width, color="b")
ax[2].set_title("P&L")
ax[2].legend(['Greek','Price'])
fig.show()
