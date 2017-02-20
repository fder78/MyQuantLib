# -*- coding: utf-8 -*-
import pymysql
import pandas as pd
import numpy as np
import datetime
import dateutil.relativedelta as rd
import pandas.io.data as web
import bdh

fxrate = bdh.blp("USDKRW Curncy", "last price")
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
#############################################################################################
#현재 미상환 발행정보 조회
# SQL문 실행
sql1 = """
SELECT A.운용코드, A.종류, A.발행일, A.상환일, A.최초액면금액, B.액면금액, 
A.기초자산수, A.기초자산코드1, A.기초자산코드2, A.기초자산코드3, B.현재가1, B.현재가2, B.현재가3, B.S1, B.S2, B.S3
FROM els_kjh.issue_info A
LEFT JOIN (SELECT * FROM els_kjh. issue_greeks_neoneo_swap WHERE 일자='%s') B
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
###############################################################################################


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


##########################################################################################################
#주가 별 상환 예정일 구하기
summarys=[]
targetLevels = [0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1]
indexname = ["HSCEI Index", "SX5E Index", "KOSPI2 Index", "SPX Index", "NKY Index"]
cp = np.array([bdh.blp(i, "last price") for i in indexname])

colnames = []

codeidx = {"HSCEI":0, "SX5E":1, "U180":2, "SPX":3, "NKY Index":4, "":-1}
for tl in targetLevels:    
    exDates, exAmts = [], []
    curPrice = cp * tl
    for i in range(len(idata)):    
        ntl = float(idata['액면금액'][i])
        ntl = ntl*fxrate if d2[i][-1]=='USD' else ntl
        
        stkdate = d1[i][0].replace(' ','').replace('\n','').rstrip('/').split('/')
        stkdate = np.array([datetime.datetime.strptime(d, "%Y-%m-%d") for d in stkdate])
        remaindate = stkdate > datetime.datetime.today()
        stkdate = stkdate[remaindate]
    
        stk = d1[i][1].replace(' ','').replace('\n','').rstrip('/').split('/')
        strike = np.array([float(i.replace('%',''))/100.0 for i in stk])
        strike = strike[remaindate]
        
        undercode = [idata['기초자산코드1'][i],idata['기초자산코드2'][i],idata['기초자산코드3'][i]]
        undercode = [codeidx[i] for i in undercode if i!=""]
        
        base = []
        for j in d2[i]:
            if j!="USD" and j!="KRW":
                base.append(float(j))
            else:
                break
        base = np.array(base)
        
        exDate = stkdate[-1]
        exAmt = ntl
        for j in range(len(strike)):
            isExercise = curPrice[undercode] >= base * strike[j]
            if np.prod(isExercise)==1:
                exDate = stkdate[j]
                break
        
        exDates.append(exDate)
        exAmts.append(exAmt)
        
    exDates = np.array(exDates)
    exAmts = np.array(exAmts)
    
    #월별상환예상액
    summary = []
    start = datetime.datetime(todaysDate.year, todaysDate.month, 1)
    while start<exDates.max():    
        end = start + rd.relativedelta(months=1)
        if tl==targetLevels[0]:
            colnames.append((start.year, start.month))
        summary.append(exAmts[(exDates>=start) * (exDates<end)].sum() / 100000000)
        start = end
    summarys.append(summary)

idxname = targetLevels
pd.DataFrame(summarys, index=idxname, columns=colnames).T.to_excel("MonthlyExerciseSchedule_%s.xlsx"%dstr, startrow=2, startcol=1)
print(cp)



##########################################################################################################
#가장 인접한 상환일 구하기
minIndex = []
minIdx = []
for d in zip(idata['기초자산수'],idata['S1'],idata['S2'],idata['S3'],\
            idata['기초자산코드1'],idata['기초자산코드2'],idata['기초자산코드3'],\
            idata['현재가1'],idata['현재가2'],idata['현재가3']):
    idx = d.index(min(d[1:1+d[0]]))
    minIdx.append(idx)
    minIndex.append((d[idx+3],d[idx+6]))
    
redDate = []
strike = []
notional = []
curPrice = []
worstPerformance=[]
for i in range(len(idata)):
    temp = d1[i][0].replace(' ','').replace('\n','')
    stk = d1[i][1].replace(' ','').replace('\n','').split('/')
    ntl = float(idata['액면금액'][i])
    ntl = ntl*fxrate if d2[i][-1]=='USD' else ntl
    for j, d in enumerate(temp.split('/')):
        if datetime.datetime.strptime(d,"%Y-%m-%d") > datetime.datetime.today():
            worstPerformance.append(minIndex[i][0])
            curPrice.append(minIndex[i][1])
            redDate.append(datetime.datetime.strptime(d, "%Y-%m-%d"))
            strike.append(float(d2[i][minIdx[i]-1])*float(stk[j].replace('%',''))/100.0)
            notional.append(float(ntl))
            break
        
idata['WP 지수'] = worstPerformance
idata['행사일'] = redDate
idata['현재가격'] = curPrice
idata['행사가격'] = strike
idata = idata.sort_values('행사일')
idata['액면금액(억원)'] = idata['액면금액'] / 100000000
idata.index = np.arange(1,len(redDate)+1)
sel = idata['액면금액(억원)']>=0
idata[sel].to_excel("schedule_table_%s.xlsx" % (dstr))
##########################################################################################################

