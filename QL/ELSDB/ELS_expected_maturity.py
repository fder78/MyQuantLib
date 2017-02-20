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
d = datetime.datetime.today() - rd.relativedelta(days=2) 
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
    
    #조기상환일/행사가격
    sql = """SELECT ParamValue FROM eqt_drvs.issue_param_long 
    WHERE 운용코드='%s' AND Subcode=1 AND ParamName in ('StepDown_조기상환평가일', 'StepDown_행사가')
    """ % (idata['운용코드'][i])
    curs.execute(sql)    
    temp = curs.fetchall()
    temp = tuple([x[0].replace(' ','').replace('\n','').rstrip('/').split('/') for x in temp])
    d1.append(temp)
    
    #기초자산기준가 / 통화
    sql = """SELECT ParamValue FROM eqt_drvs.issue_param_short
    WHERE 운용코드='%s' AND Subcode=1 AND ParamName in ('할인금리', '기초자산1_기준가', '기초자산2_기준가', '기초자산3_기준가')
    """ % (idata['운용코드'][i])
    curs.execute(sql)
    temp = curs.fetchall()
    temp = tuple([x[0] for x in temp])
    d2.append(temp)
    
# Connection 닫기
conn.close()

scenario = [0,0.15,-0.15]
def expectedMaturity(n, s0, vol, corr, base, strike, redDate):
    numSim = 10000
    todaysDate = datetime.datetime.today()
    yf = np.array([(d-todaysDate).days/365.0 for d in redDate])
    stk = np.array(strike)[yf>0]
    yf = yf[yf>0]
    yf = np.r_[[0],yf]
    s = np.ones((numSim, len(s0))) * np.array(s0)
    vol = np.array(vol)
    m = np.zeros(n)
    c = np.ones((n,n))
    corr = np.array(corr)
    #corr[:] = -0.8
    if n>=2:
        c[0,1], c[1,0] = corr[0], corr[0]
    if n==3:
        c[1,2], c[2,1] = corr[1], corr[1]
        c[0,2], c[2,0] = corr[2], corr[2]
    maturity = np.zeros(numSim)
    for j in range(1,len(yf)-1):
        e = np.random.multivariate_normal(m,c,numSim)
        s = s*np.exp(-0.5*vol**2*(yf[j]-yf[j-1]) + vol*np.sqrt(yf[j]-yf[j-1])*e)
        ss = s / np.array(base)
        maturity[(ss.min(1)>=stk[j-1]) * (maturity==0)] = yf[j]    
    maturity[maturity==0] = yf[-1]
    
    #return max(yf)
    return maturity.mean()

res = np.zeros((len(idata), 4))
for i in range(len(idata)):
    print(i,idata['운용코드'][i])
    n = idata['기초자산수'][i]
    s0 = np.array((idata['현재가1'][i], idata['현재가2'][i], idata['현재가3'][i])[:n])
    vol = (idata['변동성1'][i], idata['변동성2'][i], idata['변동성3'][i])[:n]
    corr = (idata['상관계수12'][i], idata['상관계수23'][i], idata['상관계수31'][i])
    base = tuple([float(x) for x in d2[i][:-1]])
    
    ntl = float(idata['액면금액'][i])
    ntl = ntl*fxrate if d2[i][-1]=='USD' else ntl    
    strike = [float(x.replace('%','')) / 100.0 for x in d1[i][1]]
    redDate = [datetime.datetime.strptime(d, "%Y-%m-%d") for d in d1[i][0]]
    
    expMat = expectedMaturity(n, (1+scenario[0])*s0, vol, corr, base, strike, redDate)
    expMatUp = expectedMaturity(n, (1+scenario[1])*s0, vol, corr, base, strike, redDate)
    expMatDn = expectedMaturity(n, (1+scenario[2])*s0, vol, corr, base, strike, redDate)
    
    res[i,0] = ntl
    res[i,1] = expMat
    res[i,2] = expMatUp
    res[i,3] = expMatDn

weightedMaturity = (res[:,0].reshape(len(idata),1)*res[:,1:4]).sum(0)/res.sum(0)[0]
print("weightedMaturity = ", weightedMaturity)


import matplotlib.pyplot as plt
fig, ax = plt.subplots(3,1,figsize=(7,12))

mm = np.linspace(1.0/12,3,36)
sumOfNtl = np.zeros((len(mm),3))
em = res[:,1:4]
for i in range(len(mm)):
    idx = res[:,1:4]<mm[i]
    for j in range(3):
        sumOfNtl[i,j] = res[idx[:,j],0].sum(0)
    
sumOfNtl = np.r_[sumOfNtl[0,:].reshape(1,3),np.diff(sumOfNtl.T).T]
xlabel = np.array(['%dM'%x for x in range(1,37)])

for i in range(3):
    ax[i].bar(mm,sumOfNtl[:,i],width=mm[0], alpha=0.4)
    ax[i].set_title("Expected Maturities ({0:+.2%})".format(scenario[i]))
    ax[i].set_ylim([0,4.5e11])
    ax[i].text(2,3e11,"Exp. Mat = {0:.2f} yrs".format(weightedMaturity[i]),fontsize=13)
    plt.setp(ax[i], xticks=mm[2::3], xticklabels=xlabel[2::3])
fig.show()

#3개월단위 합산
sumOfNtl3 = np.zeros((12,3))
for i in range(12):
    sumOfNtl3[i,:] = sumOfNtl[i*3:(i+1)*3,:].sum(0)
    
pd.DataFrame(sumOfNtl3/100000000).to_excel("Expected_Mat_%s.xlsx"%dstr)