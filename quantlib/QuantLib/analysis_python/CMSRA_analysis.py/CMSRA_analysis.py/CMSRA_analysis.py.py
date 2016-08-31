import numpy as np
import pandas as pd
import subprocess
from xml.etree.ElementTree import parse
from multiprocessing import Pool
#0<CurveDataItem ChunkIndex="0" Yield="0.00380511" Date="2016-03-16 00:00:00"/>
#1<CurveDataItem ChunkIndex="0" Yield="0.00380511" Date="2016-03-17 23:59:59"/>
#2<CurveDataItem ChunkIndex="0" Yield="0.00402156" Date="2016-03-25 23:59:59"/>
#3<CurveDataItem ChunkIndex="0" Yield="0.00443410" Date="2016-04-18 23:59:59"/>
#4<CurveDataItem ChunkIndex="0" Yield="0.00644756" Date="2016-06-20 23:59:59"/>
#5<CurveDataItem ChunkIndex="0" Yield="0.00635242" Date="2016-07-20 23:59:59"/>
#6<CurveDataItem ChunkIndex="0" Yield="0.00673110" Date="2016-08-18 23:59:59"/>
#7<CurveDataItem ChunkIndex="1" Yield="0.00725112" Date="2016-09-15 23:59:59"/>
#8<CurveDataItem ChunkIndex="0" Yield="0.00730461" Date="2016-10-20 23:59:59"/>
#9<CurveDataItem ChunkIndex="1" Yield="0.00789583" Date="2016-12-21 23:59:59"/>
#0<CurveDataItem ChunkIndex="0" Yield="0.00847526" Date="2017-03-21 23:59:59"/>
#1<CurveDataItem ChunkIndex="0" Yield="0.00896107" Date="2017-06-15 23:59:59"/>
#2<CurveDataItem ChunkIndex="0" Yield="0.00947457" Date="2017-09-21 23:59:59"/>
#3<CurveDataItem ChunkIndex="0" Yield="0.00992643" Date="2017-12-20 23:59:59"/>
#4<CurveDataItem ChunkIndex="1" Yield="0.01303510" Date="2020-03-18 23:59:59"/>
#5<CurveDataItem ChunkIndex="1" Yield="0.01416591" Date="2021-03-18 23:59:59"/>
#6<CurveDataItem ChunkIndex="2" Yield="0.01521747" Date="2022-03-18 23:59:59"/>
#7<CurveDataItem ChunkIndex="2" Yield="0.01613158" Date="2023-03-20 23:59:59"/>
#8<CurveDataItem ChunkIndex="2" Yield="0.01695860" Date="2024-03-18 23:59:59"/>
#9<CurveDataItem ChunkIndex="2" Yield="0.01767249" Date="2025-03-18 23:59:59"/>
#0<CurveDataItem ChunkIndex="2" Yield="0.01835405" Date="2026-03-18 23:59:59"/>
#1<CurveDataItem ChunkIndex="2" Yield="0.01898949" Date="2027-03-18 23:59:59"/>
#2<CurveDataItem ChunkIndex="2" Yield="0.01950475" Date="2028-03-20 23:59:59"/>
#3<CurveDataItem ChunkIndex="2" Yield="0.02076085" Date="2031-03-18 23:59:59"/>
#4<CurveDataItem ChunkIndex="2" Yield="0.02203265" Date="2036-03-18 23:59:59"/>
#5<CurveDataItem ChunkIndex="2" Yield="0.02262565" Date="2041-03-18 23:59:59"/>
#6<CurveDataItem ChunkIndex="2" Yield="0.02298350" Date="2046-03-19 23:59:59"/>
#7<CurveDataItem ChunkIndex="2" Yield="0.02298593" Date="2056-03-20 23:59:59"/>
#8<CurveDataItem ChunkIndex="2" Yield="0.02292559" Date="2061-03-18 23:59:59"/>

def getPrice(d):
    delta = d[0]
    adj = [d[0]]
    npv0 = d[1]
    npvs = []
    
    for k, iter in enumerate(adj):
        years = [0,1,4,5,7,10,12,15,20,25,30,40,45]
        perturbation = [0,11,15,16,18,21,23,24,25,26,27,28,29]
        temp = [iter]
        for (y,pt) in zip(years, perturbation):
            print("( %d, %d )" % (y, iter))            
            #tree = parse('C:\\Users\\Daishin\\Desktop\\20160316xml\\ficc_racmsspread_v01_BDAE5744-111B-49CB-9145-661E271B1CE5.xml')
            tree = parse('C:\\Users\\Daishin\\Desktop\\20160317xml\\ficc_racmsspread_v01_F11E0AF6-0152-4B93-A879-289802296809.xml')
            params = tree.find("param_root").find("curve_root").find("curve")
            curve = params.find("CurveData").findall("CurveDataItem")
            curve.extend(params.find("SwaptionVolCurveData").findall("SwaptionVolCurveDataItem"))
            for i, cdata in enumerate(curve):
                adjustment = 0.0
                if i>=pt-1:
                    adjustment = iter / 10000.0
                y = float(cdata.get("Yield")) + adjustment
                cdata.set("Yield", str(y))
            tree.write("params%d.xml"%delta)
        
            subprocess.call([r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\bin\ficc_cms_spread_v01.exe",
            r"E:\MyQuantLib\quantlib\QuantLib\analysis_python\CMSRA_analysis.py\CMSRA_analysis.py\params%d.xml"%delta,
            "Result%d.xml"%delta])
        
            tree = parse("Result%d.xml"%delta)
            root = tree.getroot()
            res = root.find("results").findtext("npv")
            npv = float(res)
            temp.append(npv - npv0)
            
            #print
            print("%0.5f" % npv)
            res = root.find("computationTime").findtext("ctime")
            print("time= %s" % res)
            print("-"*20)
        
        npvs.append(temp)
    

    rst = np.array(npvs)
    pd.DataFrame(rst).to_csv("results%d.csv"%delta, header=False, index=False)




if __name__=="__main__":

    print("pricing NPV0...")
    inp = 'C:\\Users\\Daishin\\Desktop\\20160316xml\\ficc_racmsspread_v01_BDAE5744-111B-49CB-9145-661E271B1CE5.xml'
    inp = 'C:\\Users\\Daishin\\Desktop\\20160317xml\\ficc_racmsspread_v01_F11E0AF6-0152-4B93-A879-289802296809.xml'
    subprocess.call([r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\bin\ficc_cms_spread_v01.exe", inp,"Result0.xml"])
 
    tree = parse("Result0.xml")
    root = tree.getroot()
    res = root.find("results").findtext("npv")
    npv0 = float(res)
    print("NPV0 = %g" % npv0)

    p = Pool(6)
    parm = [-5,-1,1,5]
    params = []
    for i in parm:
        params.append((i,npv0))
    p.map(getPrice, params)

