# -*- coding: utf-8 -*-
"""
Created on Thu Dec 22 17:04:47 2016

@author: Daishin
"""

# -*- coding: utf-8 -*-

fxrate = 1180
'''
import pandas.io.data as web
fxrate = web.DataReader('DEXKOUS','fred')
fxrate = fxrate['DEXKOUS'][-1]
'''
import pymysql
import pandas as pd
import numpy as np
import datetime
import dateutil.relativedelta as rd
todaysDate = datetime.datetime.today()
d = datetime.datetime.today() - rd.relativedelta(days=1) 
while d.weekday()>4:
    d = d - rd.relativedelta(days=1)
dstr = d.strftime("%Y-%m-%d")

# MySQL Connection 연결
conn = pymysql.connect(host='fdos-mt', user='root', password='3450', #db='ficc_DRvs', 
                       charset='utf8')
 
# Connection 으로부터 Cursor 생성
curs = conn.cursor()
 
# SQL문 실행
sql1 = """
SELECT A.운용코드, A.종류, A.발행일, A.상환일, A.최초액면금액, B.액면금액, 
A.기초자산수, A.기초자산코드1, A.기초자산코드2, A.기초자산코드3, B.현재가1, B.현재가2, B.현재가3, B.S1, B.S2, B.S3, 
B.변동성1, B.변동성2, B.변동성3, B.상관계수12, B.상관계수23, B.상관계수31 
FROM els_kjh.issue_info A
LEFT JOIN (SELECT * FROM els_kjh. issue_greeks_neoneo_swap WHERE 일자='%s') B
ON A.운용코드=B.운용코드
WHERE A.상환일=0 
AND A.종류 in ("StepDown", "MonthlyStepDown", "StepDownNewHeart", "LizardStepDown")
AND B.액면금액>0
""" % (dstr)

curs.execute(sql1)
fields = [d[0] for d in curs.description]
 
# 데이타 Fetch
issue = curs.fetchall()
idata = pd.DataFrame(np.array(issue), columns=fields)

d1, d2 = [], []
for i in range(len(idata)):
    
    #기초자산기준가 / 통화
    sql = """SELECT ParamValue FROM eqt_drvs.issue_param_short
    WHERE 운용코드='%s' AND Subcode=1 
    AND ParamName in ('할인금리', '기초자산1_기준가', '기초자산2_기준가', '기초자산3_기준가','stepdown_haski', 'StepDown_KIB')     
    """ % (idata['운용코드'][i])
    curs.execute(sql)
    temp = curs.fetchall()
    temp = tuple([x[0] for x in temp])
    d2.append(temp)
    
# Connection 닫기
conn.close()

notional = {'U180':[], 'SPX':[], 'HSCEI':[], 'SX5E':[], 'NKY Index':[]}
code = {'U180':[], 'SPX':[], 'HSCEI':[], 'SX5E':[], 'NKY Index':[]}
s0 = {'U180':0, 'SPX':0, 'HSCEI':0, 'SX5E':0, 'NKY Index':0}
for i in range(len(idata)):
    if d2[i][0].strip().lower()=="no" and d2[i][1]!="0":
        x = d2[i][1].replace('%','').replace(' ','').split('/')
        if str(type(x))=="<class 'list'>":
            x = x[0]
        kib = float(x)
        kib = kib/100.0 if kib>1 else kib
        for j in range(idata['기초자산수'][i]):
            notional[idata["기초자산코드%d"%(j+1)][i]].append(\
            (float(idata['액면금액'][i]), kib*float(d2[i][2+j]) / idata["현재가%d"%(j+1)][i]))
            s0[idata["기초자산코드%d"%(j+1)][i]]=idata["현재가%d"%(j+1)][i]
            code[idata["기초자산코드%d"%(j+1)][i]].append(idata["운용코드"][i])

rg = np.arange(1.0,0.0,-0.05)
res = pd.DataFrame(np.zeros((len(rg)-1,len(notional.keys()))), index=rg[1:], columns=notional.keys())
for i in notional.keys():
    x = np.array(notional[i])
    c = np.array(code[i])
    for j in range(len(rg)-1):
        sel = (x[:,1]>rg[j+1]) * (x[:,1]<=rg[j])
        res[i][j] = sum(x[sel,0])
        if i=="HSCEI":
            print(c[sel])

res.loc['tot'] = res.sum()
s0 = pd.DataFrame(s0, index=["Cur.level"],columns=s0.keys())
res = s0.append(res)
res.to_excel("KI_LEVEL_%s.xlsx"%(dstr))

        
        
        
        
        
        
        
        
        
        
        
        