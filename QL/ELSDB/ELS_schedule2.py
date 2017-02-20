# -*- coding: utf-8 -*-
import pymysql
import pandas as pd
import numpy as np
import datetime
import dateutil.relativedelta as rd
import pandas.io.data as web

fxrate = 1180
'''
fxrate = web.DataReader('DEXKOUS','fred')
fxrate = fxrate['DEXKOUS'][-1]
'''

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
A.기초자산수, A.기초자산코드1, A.기초자산코드2, A.기초자산코드3, B.현재가1, B.현재가2, B.현재가3, B.S1, B.S2, B.S3
FROM els_kjh.issue_info A
LEFT JOIN (SELECT * FROM els_kjh.issue_greeks_neoneo_swap WHERE 일자='%s') B
ON A.운용코드=B.운용코드
WHERE A.상환일=0 
AND A.종류 in ("StepDown", "MonthlyStepDown", "StepDownNewHeart", "LizardStepDown")
AND B.액면금액>0
""" % (dstr)

#(SELECT * FROM els_kjh.issue_greeks2_blp WHERE 일자='2016-12-14')

curs.execute(sql1)
fields = [d[0] for d in curs.description]
 
# 데이타 Fetch
issue = curs.fetchall()
idata = pd.DataFrame(np.array(issue), columns=fields)

d1, d2 = [], []
for i in range(len(idata)):
    
    #조기상환일/행사가격
    sql = """SELECT ParamValue FROM eqt_drvs.issue_param_long 
    WHERE 운용코드='%s' AND ParamName in ('StepDown_조기상환평가일', 'StepDown_행사가')
    """ % (idata['운용코드'][i])
    curs.execute(sql)    
    temp = curs.fetchall()
    temp = tuple([x[0] for x in temp])
    d1.append(temp)
    
    #기초자산기준가 / 통화
    sql = """SELECT ParamValue FROM eqt_drvs.issue_param_short
    WHERE 운용코드='%s' AND ParamName in ('할인금리', '기초자산1_기준가', '기초자산2_기준가', '기초자산3_기준가')
    """ % (idata['운용코드'][i])
    curs.execute(sql)
    temp = curs.fetchall()
    temp = tuple([x[0] for x in temp])
    d2.append(temp)
    
# Connection 닫기
conn.close()



#가장 인접한 상환일 구하기
minIndex = []
minIdx = []
for d in zip(idata['기초자산수'],idata['S1'],idata['S2'],idata['S3'],\
            idata['기초자산코드1'],idata['기초자산코드2'],idata['기초자산코드3'],\
            idata['현재가1'],idata['현재가2'],idata['현재가3']):
    idx = d.index(min(d[1:1+d[0]]))
    minIdx.append(idx)
    minIndex.append((d[idx+3],d[idx+6]))
    
redDate = {'U180':[], 'SPX':[], 'HSCEI':[], 'SX5E':[], 'NKY Index':[]}
strike = {'U180':[], 'SPX':[], 'HSCEI':[], 'SX5E':[], 'NKY Index':[]}
notional = {'U180':[], 'SPX':[], 'HSCEI':[], 'SX5E':[], 'NKY Index':[]}
curPrice = {'U180':[], 'SPX':[], 'HSCEI':[], 'SX5E':[], 'NKY Index':[]}

for i in range(len(idata)):
    temp = d1[i][0].replace(' ','').replace('\n','')
    stk = d1[i][1].replace(' ','').replace('\n','').split('/')
    ntl = idata['액면금액'][i]
    ntl = ntl*fxrate if d2[i][-1]=='USD' else ntl
    for j, d in enumerate(temp.split('/')):
        if datetime.datetime.strptime(d,"%Y-%m-%d") > datetime.datetime.today():
            curPrice[minIndex[i][0]].append(minIndex[i][1])
            redDate[minIndex[i][0]].append(datetime.datetime.strptime(d, "%Y-%m-%d"))
            strike[minIndex[i][0]].append(float(d2[i][minIdx[i]-1])*float(stk[j].replace('%',''))/100.0)
            notional[minIndex[i][0]].append(float(ntl))
            break
    

import matplotlib.pyplot as plt
#fig, ax = plt.subplots(1,1,figsize=(12,8))
names = ['HSCEI','SX5E','U180','SPX']
s = {'U180':np.zeros(6), 'SPX':np.zeros(6), 'HSCEI':np.zeros(6), 'SX5E':np.zeros(6), 'NKY Index':np.zeros(6)}
for name in names:    
    fig, ax = plt.subplots(1,1,figsize=(12,8))
    ax.scatter(redDate[name], strike[name], s=np.sqrt(np.array(notional[name]))/400, alpha=0.3)
    ax.plot([min(redDate[name]), max(redDate[name])], [curPrice[name][0]]*2)
    ax.set_title(name)
    ax.set_xlim([min(redDate[name]), max(redDate[name])])
    ax.grid()
    ga1 = ax.scatter([],[],s=np.sqrt(1000000000)/400,alpha=0.3)
    ga2 = ax.scatter([],[],s=np.sqrt(10000000000)/400,alpha=0.3)
    ga3 = ax.scatter([],[],s=np.sqrt(30000000000)/400,alpha=0.3)
    ax.legend([ga1,ga2,ga3],['10','100','300'],scatterpoints=1)
plt.show()

#상환예상금액
mul = [0.9, 0.95, 1.0, 1.05, 1.1]
sumOfRedemp = np.zeros((5,6))
for m in range(1,7):
    targetPeriod = datetime.datetime.today() + rd.relativedelta(months=m)
    targetPeriod = datetime.datetime(2017,m+1,1) - datetime.timedelta(days=1)
    for mu in range(5):
        for name in ['SX5E']: #names:
            for i in range(len(curPrice[name])):
                if curPrice[name][i]*mul[mu]>=strike[name][i] and redDate[name][i]<=targetPeriod:
                    sumOfRedemp[mu][m-1] += notional[name][i]

pd.DataFrame(sumOfRedemp, columns=list(range(1,7)), index=[m-1 for m in mul]).to_excel('Exer_Schedule_%s.xlsx'%(dstr))


ridx = np.array(redDate['HSCEI']) <= datetime.datetime(2017,1,15)
pinSchedule = pd.DataFrame()
pinSchedule['date'] = np.array(redDate['HSCEI'])[ridx]
pinSchedule['stk'] = np.array(strike['HSCEI'])[ridx]
pinSchedule['stk_ratio'] = np.array(strike['HSCEI'])[ridx] / 9394.87 -1.0
pinSchedule['ntl'] = np.array(notional['HSCEI'])[ridx] / 100000000
pinSchedule.sort('date', inplace=True)
pinSchedule.to_excel('pin_schedule.xlsx')

'''

conn = pymysql.connect(host='fdos-mt', user='root', password='3450', #db='ficc_DRvs', 
                       charset='utf8')
curs = conn.cursor()
curs.execute("SELECT * FROM eqt_drvs.issue_param_short")
xf = [d[0] for d in curs.description]
x = pd.DataFrame(np.array(curs.fetchall()), columns=xf)
curs.execute("SELECT * FROM eqt_drvs.issue_param_long")
yf = [d[0] for d in curs.description]
y = pd.DataFrame(np.array(curs.fetchall()), columns=yf)

conn.close()

'''



