# -*- coding: utf-8 -*-

import pymysql
import pandas as pd
import numpy as np
import datetime
import QuantLib as ql
import matplotlib.pyplot as plt

def ccy2index(code):
    m = {"KRW":"KOSPI2", "USD":"SPX", "HKD":"HSCEI", "EUR":"SX5E"}
    return m[code]

def index2ccy(code):
    m = {"KOSPI2":"KRW", "SPX":"USD", "HSCEI":"HKD", "SX5E":"EUR"}
    return m[code]    

def getYieldCurve(mdata, code):
    dates = [ql.Date(d.day, d.month, d.year) for d in np.r_[[mdata['evaldate']], mdata['dates'][code]]]
    dfs = np.r_[1, mdata['df'][code]]
    yc = ql.DiscountCurve(dates, dfs, ql.Actual365Fixed())
    yc.enableExtrapolation()
    return yc
    
def getDividendCurve(mdata, code):
    dates = [ql.Date(d.day, d.month, d.year) for d in np.r_[[mdata['evaldate']], mdata['dates'][code]]]
    divs = np.r_[mdata['div'][code][0], mdata['div'][code]]
    dc = ql.ZeroCurve(dates, divs, ql.Actual365Fixed())
    dc.enableExtrapolation()
    return dc

def getDividendCurveWithQuantoAdjustment(mdata, code, disccode):
    div = getDividendCurve(mdata, code)
    if index2ccy(code) == disccode:
        return div
    fxcode = index2ccy(code) + disccode
    qapair = (code, fxcode) if (code, fxcode) in mdata['corr'].keys() else (fxcode, code)
    qa = mdata['corr'][qapair] * mdata['quantovol'][fxcode] * mdata['quantovol'][code]
    divqa = ql.ZeroSpreadedTermStructure(ql.YieldTermStructureHandle(div), ql.QuoteHandle(ql.SimpleQuote(qa)))
    divqa.enableExtrapolation()
    return divqa    
    
def getMarketData(today):
    '''
    conn = pymysql.connect(host='10.50.20.105', user='neo', password='neo', charset='utf8')
    cur = conn.cursor()
    
    underlyings = ["S&P 500", "EURO STOXX 50", "KOSPI 200", "HSCEI"]
    udlcode = ['SPX','SX5E','KOSPI2','HSCEI']
    dates, spot, discFactor, fwdPrice, divYield, stks, vols, corr, quantovol = {}, {}, {}, {}, {}, {}, {}, {}, {}
    
    for udl, code in zip(underlyings, udlcode):
        temp = ()
        d = today
        numoftry = 0
        while len(temp) == 0:
            numoftry += 1
            if numoftry>30: raise Exception("WE HAVE NO VOL DATA @ %s" % today.isoformat())
            d = d - datetime.timedelta(1)            
            sql = """select * from market.markitvoldata 
            where valuationdate='{date}' and underlying='{ud}'"""\
            .format(date=d.strftime("%Y-%m-%d"), ud=udl)            
            cur.execute(sql)    
            temp = cur.fetchall()
            
        if __name__=="__main__":
            print(d.strftime("%Y-%m-%d"), udl)
        temp = [i for i in temp]
        vdata = pd.DataFrame(temp, columns = [des[0] for des in cur.description])
        idx = np.where(vdata['Relative_Strike']==100)[0]
        dates[code] = np.array(vdata['Expiration_Date'][idx])
        discFactor[code] = np.array(vdata['Discount_Factor'][idx])
        fwdPrice[code] = np.array(vdata['Forward_Price'][idx])
        divYield[code] = np.array(vdata['Dividend_Yield'][idx])
        spot[code] = vdata['Spot_Price'][0]

        idx = np.where(vdata['Expiration_Date']==vdata['Expiration_Date'][0])[0]
        stks[code] = np.array(vdata['Strike_Price'][idx])
        
        vols[code] = []
        for i in stks[code]:
            idx =  np.where(vdata['Strike_Price']==i)[0]
            vols[code].append(np.array(vdata['Volatility'][idx]))
        vols[code] = np.array(vols[code])
        
        ##TEMP
        sql = """SELECT * FROM market.correlation 
        WHERE date IN (SELECT MAX(date) FROM market.correlation);"""           
        cur.execute(sql)
        temp = cur.fetchall()
        for d0, i1, i2, c in temp:
            corr[(i1,i2)] = c

        sql = """SELECT * FROM market.quantovol
        WHERE date IN (SELECT MAX(date) FROM market.quantovol);"""           
        cur.execute(sql)
        temp = cur.fetchall()
        for d0, i, c in temp:
            quantovol[i] = c
    '''
    d = today    
    
    underlyings = ['KSE_EQVol_Index_Exchange_20170131.csv',
                 'SPUS_EQVol_Index_Exchange_20170131.csv',
                 'STOXX_EQVol_Index_Exchange_20170131.csv']
    udlcode = ['KOSPI2','SPX','SX5E']
    dates, spot, discFactor, fwdPrice, divYield, stks, vols, corr, quantovol = {}, {}, {}, {}, {}, {}, {}, {}, {}
    
    for udl, code in zip(underlyings, udlcode):
        '''
        temp = ()
        d = today
        numoftry = 0
        while len(temp) == 0:
            numoftry += 1
            if numoftry>30: raise Exception("WE HAVE NO VOL DATA @ %s" % today.isoformat())
            d = d - datetime.timedelta(1)            
            sql = """select * from market.markitvoldata 
            where valuationdate='{date}' and underlying='{ud}'"""\
            .format(date=d.strftime("%Y-%m-%d"), ud=udl)            
            cur.execute(sql)    
            temp = cur.fetchall()
            
        if __name__=="__main__":
            print(d.strftime("%Y-%m-%d"), udl)
        temp = [i for i in temp]
        vdata = pd.DataFrame(temp, columns = [des[0] for des in cur.description])
        '''
        vdata = pd.read_csv(udl)
        idx = np.where(vdata['Relative Strike']==100)[0]
        dates[code] = np.array([datetime.datetime.strptime(i, "%Y/%m/%d") for i in vdata['Expiration Date'][idx]])
        discFactor[code] = np.array(vdata['Discount Factor'][idx])
        fwdPrice[code] = np.array(vdata['Forward Price'][idx])
        divYield[code] = np.array(vdata['Dividend Yield'][idx])
        spot[code] = vdata['Spot Price'][0]

        idx = np.where(vdata['Expiration Date']==vdata['Expiration Date'][0])[0]
        stks[code] = np.array(vdata['Strike Price'][idx])
        
        vols[code] = []
        for i in stks[code]:
            idx =  np.where(vdata['Strike Price']==i)[0]
            vols[code].append(np.array(vdata['Volatility'][idx]))
        vols[code] = np.array(vols[code])

    #TEMP
    corr[("HKDKRW","HSCEI")] = -0.3
    corr[("EURKRW","SX5E")] = -0.3
    corr[("USDKRW","SPX")] = -0.3
    corr[("KOSPI2","SX5E")], corr[("KOSPI2","SPX")], corr[("SX5E","SPX")] = 0.6, 0.6, 0.6
    quantovol = {"USDKRW":0.1, "HKDKRW":0.1, "EURKRW":0.1, "SPX":0.2, "SX5E":0.2, "HSCEI":0.2}

    mktData = {"evaldate":datetime.datetime(d.year,d.month,d.day),
               "dates": dates,
               "spot": spot,
               "stks": stks,
               "df": discFactor,
               "fwd": fwdPrice,
               "div": divYield,
               "vol": vols,
               "corr": corr,
               "quantovol": quantovol}
    return mktData
    
#PLOT SURFACE
if __name__=="__main__":
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    fig = plt.figure(figsize=(10,10))
    underlyings = ['SPX','SX5E','KOSPI2']
    today = datetime.datetime.today()
    data = getMarketData(today)
    for i, udl in enumerate(underlyings):
        dnum = []
        for j in data['dates'][udl]:
            dnum.append((j.date()-today.date()).days)
        x, y = np.meshgrid(dnum, data['stks'][udl])
        ax = fig.add_subplot(2,2,i+1,projection='3d')
        ax.plot_wireframe(x,y,data['vol'][udl])
        ax.set_title(udl)
    
    f, ax = plt.subplots(2,2)
    for i in range(2):
        for j in range(2):
            code = underlyings[2*i+j]
            ax[i][j].plot(data['dates'][code], data['div'][code], 's-')
            ax[i][j].set_title(code)                
    f.show()