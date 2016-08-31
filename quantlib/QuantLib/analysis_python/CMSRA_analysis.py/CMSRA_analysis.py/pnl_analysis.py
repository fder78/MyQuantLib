import numpy as np
import pandas as pd
import subprocess
from xml.etree.ElementTree import parse
from os import listdir
from multiprocessing import Pool

def getPrice(fname):
    print(fname)
    subprocess.call([r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\bin\ficc_cms_spread_v01.exe",
                     "C:\\Users\\Daishin\\Desktop\\20160317xml\\" + fname[0], "pnl\\pnl%s.xml"%fname[1]])    
    tree = parse("pnl\\pnl%s.xml"%fname[1])
    root = tree.getroot()
    res = root.find("results").findtext("npv")
    npv = float(res)
    print("%0.5f" % npv)
    res = root.find("computationTime").findtext("ctime")
    print("time= %s" % res)
    print("-"*20)



mypath = r"C:\Users\Daishin\Desktop\20160317xml"
flist = np.array(listdir(mypath), dtype=np.dtype("U",100))
fullname = []
ydata = pd.DataFrame()

for i, x in enumerate(flist):
    fullname.append(mypath + "\\" + x)
    tree = parse(fullname[i])
    params = tree.find("param_root").find("curve_root").find("curve")
    curve = params.find("CurveData").findall("CurveDataItem")
    yc = []
    for c in curve:
        yc.append(float(c.get("Yield")))
    ydata[fullname[i]] = np.array(yc)

ydata.to_excel(r"E:\MyQuantLib\quantlib\QuantLib\analysis_python\CMSRA_analysis.py\CMSRA_analysis.py\pnl\CurveData.xlsx")

x = np.zeros(ydata.shape)
import matplotlib.pyplot as plt
for j in [32,53]:
#for j in [45]:
#for j in range(len(flist)):
    temp = ydata.ix[:,j]
    for i in range(len(flist)):
        x[:,i] = ydata.ix[:,i] - temp
    plt.figure(j)
    plt.plot(x)
    plt.title(j)
'''
subprocess.call([r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\bin\ficc_cms_spread_v01.exe",
fullname[45],
"Result.xml"])

if __name__=="__main__":
    p = Pool(8)
    num = np.arange(len(flist))    
    params = np.c_[flist, num]
    p.map(getPrice, params)
    
'''


