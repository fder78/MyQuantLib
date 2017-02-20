# -*- coding: utf-8 -*-

import time
import datetime
from makeMarketData_EQ import getMarketData
from StepDownELS import stepdownels

notional = 10000
cpnRates = [0.03*i for i in range(1,7)]
barriers = [95,95,90,90,85,85]
kibarrier = 60
issueDate = datetime.datetime(2015,4,20)
redmpDates = [datetime.datetime(2015,10,20), datetime.datetime(2016,4,20),
              datetime.datetime(2016,10,20), datetime.datetime(2017,4,20),
              datetime.datetime(2017,10,20), datetime.datetime(2018,4,20)]
slopes = [10]*5 + [10]

underlyings = [("HSCEI", "SX5E"), (13500, 3500)]
discCode = "KOSPI2"

price = []
for i in range(30):    
    t0 = time.time()
    today = datetime.datetime(2016,12,25) + datetime.timedelta(i)
    mdata = getMarketData(today) 
    evaldate = mdata['evaldate']
    res = stepdownels(evaldate, notional, cpnRates, barriers, kibarrier, [issueDate] + redmpDates, slopes,
                      underlyings, discCode, mdata)
    t1 = time.time()
    
    print(res['npv'])
    price.append(res['npv'])
    
    print(t1-t0)
    print('-'*20)