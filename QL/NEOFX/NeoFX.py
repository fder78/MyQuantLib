# -*- coding: utf-8 -*-
from __future__ import division
import datetime as dt
import xlwings as xw
import numpy as np
import pandas as pd
import time
import QuantLib as ql
import barrieroption as bo
import bdh
import pymysql
from curve_builder import buildCurve

def runPricing():
    # MySQL Connection 연결
    conn = pymysql.connect(host='fdos-mt', user='root', password='3450', #db='ficc_DRvs', 
                           charset='utf8')
     
    # Connection 으로부터 Cursor 생성
    curs = conn.cursor()
    # SQL문 실행
    curs.execute("select max(receivedate) from ficc_drvs.curves where receivedate<=curdate()")
    recentDate = curs.fetchall()[0][0]
    print(recentDate)
    #####################
    ## USD Curve Building
    #####################
    sql1 = 'SELECT * FROM ficc_drvs.curves WHERE receivedate="%s" AND CurveCode = "USD";' % (recentDate.strftime("%Y-%m-%d"))
    curs.execute(sql1)
    #fields = [d[0] for d in curs.description]
    mdataFGN = curs.fetchall()

    pparse = ql.PeriodParser()
    dparse = ql.DateParser()
    numOfDeposit = 4
    numOfFutures = 9
    
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
    swaps["fixedDC"] = ql.Thirty360()
    swaps["freq"] = ql.Quarterly
    swaps["index"] = ql.USDLibor(ql.Period(3,ql.Months))
    
    calendar = ql.SouthKorea()
    todaysDate = ql.Date(recentDate.day, recentDate.month, recentDate.year)
    settlementDate = todaysDate
    dayCounter = ql.Actual365Fixed()

    divCurve = buildCurve(todaysDate, settlementDate, deposits, futures, swaps, calendar, dayCounter)   
    
        
    #####################
    ## KRW CRS Curve Building
    #####################
    sql1 = 'SELECT * FROM ficc_drvs.curves WHERE receivedate="%s" AND CurveCode = "USDCRS";' % (recentDate.strftime("%Y-%m-%d"))
    curs.execute(sql1)
    mdataDOM = curs.fetchall()
    numOfDeposit = 6
    numOfFutures = 0
    
    deposits = {"quote": []}
    for i in range(numOfDeposit):
        deposits["quote"].append( (pparse.parse(mdataDOM[i][3]), ql.SimpleQuote(mdataDOM[i][4])) )
    deposits["dc"] = ql.Actual360()
    deposits["settlementDays"] = 2
    deposits["bdc"] = ql.ModifiedFollowing

    futures = {"quote": []}
    for i in range(numOfDeposit, numOfDeposit+numOfFutures):
        d0 = dparse.parse(mdataDOM[i][3], "%y%b")
        d0 = dt.datetime(d0.year(), d0.month(), d0.dayOfMonth())
        x = (9 - d0.weekday()) % 7 + 15
        d0 = ql.Date(x, d0.month, d0.year)
        futures["quote"].append( (d0, ql.SimpleQuote(mdataDOM[i][4])) )
    futures["maturity"] = 3
    futures["dc"] = ql.Actual360()
    futures["bdc"] = ql.ModifiedFollowing

    swaps = {"quote": []}
    for i in range(numOfDeposit+numOfFutures, len(mdataDOM)):
        swaps["quote"].append( (pparse.parse(mdataDOM[i][3]), ql.SimpleQuote(mdataDOM[i][4])) )
    swaps["fixedDC"] = ql.Thirty360()
    swaps["freq"] = ql.Quarterly
    swaps["index"] = ql.USDLibor(ql.Period(3,ql.Months))
    
    calendar = ql.SouthKorea()
    todaysDate = ql.Date(recentDate.day, recentDate.month, recentDate.year)
    settlementDate = todaysDate
    dayCounter = ql.Actual365Fixed()

    rfCurve = buildCurve(todaysDate, settlementDate, deposits, futures, swaps, calendar, dayCounter)   

    ##
    
    t0 = time.time()
    sht = xw.Book.caller().sheets["SimpleBarrier"]
    evaluationDate = sht.range('evaldate').options(dates=dt.datetime).value
    now = dt.datetime.today()
    sht.range("calctime").value = "평가시각 : %s" % (now.strftime("%Y-%m-%d %H:%M:%S"))
    sht.range("curvedate").value = "데이터날짜 : %s" % (recentDate.strftime("%Y-%m-%d"))
    if evaluationDate==None:
        evaluationDate = now
    qltoday = ql.Date(evaluationDate.day, evaluationDate.month, evaluationDate.year, evaluationDate.hour, evaluationDate.minute, evaluationDate.second)

    fxrate = bdh.blp('USDKRW Curncy', 'last price')
    
    #Data Input
    todaysDate = qltoday
    mkt = sht.range('market').expand().options(pd.DataFrame, index=True, header=False).value
    deal = sht.range('deal').expand().options(pd.DataFrame, index=True, header=False).value
    
    n, m = deal.shape
    for i in range(m):
        md = mkt[i]
        dd = deal[i]
        mat = dd['MaturityDate']
        exerciseDate = ql.Date(mat.day, mat.month, mat.year, 18, 0, 0) #만기일의 6PM으로 설정
        optionType = ql.Option.Call if dd['OptionType'].lower()=="call" else ql.Option.Put
        exercisePrice = dd['Strike']
        btype = dd['BarrierType'].lower()
        if btype=="upout":
            barrierType = ql.Barrier.UpOut
        elif btype=="upin":
            barrierType = ql.Barrier.UpIn
        elif btype=="downout":
            barrierType = ql.Barrier.DownOut
        elif btype=="downin":
            barrierType = ql.Barrier.DownIn
        barrierPrice = dd['Barrier']
        rebate = dd['Rebate']
        notional = dd['Notional']
        participation = dd['Participation']
        rebate /= participation  #참여율 조정
        
        price = md['Underlying']        
        if isinstance(price, str) or price==None:
            price = fxrate
        s0 =  price / dd['BasePrice']        
        vol = md['Volatility']
        rf = md['DomesticRate']
        if isinstance(rf, str) or rf==None:
            rfCurve0 = rfCurve
        else:
            rfCurve0 = ql.FlatForward(todaysDate, ql.QuoteHandle(ql.SimpleQuote(rf)), ql.Actual365Fixed())   
        div = md['ForeignRate']
        if isinstance(div, str) or div==None:
            divCurve0 = divCurve
        else:
            divCurve0 = ql.FlatForward(todaysDate, ql.QuoteHandle(ql.SimpleQuote(div)), ql.Actual365Fixed())   
        hasKnocked = True if dd['HasKnocked'].lower()=='y' else False
    
        temp = bo.pricing(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, s0, rfCurve0, divCurve0, vol)
        unitprice = temp[1]
        temp[1:] = temp[1:] * notional * participation
        temp[0] *= dd['BasePrice']
        temp = np.insert(temp, 1, s0)
        temp = np.insert(temp, 2, unitprice*participation)
        if i==0:
            res = np.zeros((len(temp),m))
            res[:,i] = temp.reshape(len(temp))
        else:
            res[:,i] = temp.reshape(len(temp))        
    
    sht.range("results").value = res

    computationTime = time.time() - t0
    sht.range("computationtime").value = "실행시간 : %0.2f 초" % computationTime

def clearResults():
    sht = xw.Book.caller().sheets["SimpleBarrier"]
    sht.range("results").expand().clear_contents()


if __name__=="__main__":
    xw.Book("NeoFX.xlsm").set_mock_caller()
    runPricing()
