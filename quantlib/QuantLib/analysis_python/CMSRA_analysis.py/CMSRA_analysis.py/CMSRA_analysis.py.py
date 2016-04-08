import numpy as np
import pandas as pd
import subprocess
from xml.etree.ElementTree import parse
#from xml.etree.ElementTree import Element, dump

from multiprocessing import Pool

def getPrice(delta):
    adj = [delta]#np.linspace(-10,10,9)
    npvs = []
    npv0 = 137718.79750825412339

    for k, iter in enumerate(adj):
        temp = [iter]
        tree = parse(r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\ficc_racmsspread_v01_E193C08E-861B-4BCB-A33B-57A3E94F4205.xml")
        curves = tree.find("param_root").find("curve_root").find("curve").find("CurveData").findall("CurveDataItem")
        n = len(curves)
        for j in range(n):
            tree = parse(r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\ficc_racmsspread_v01_E193C08E-861B-4BCB-A33B-57A3E94F4205.xml")
            params = tree.find("param_root").find("curve_root").find("curve")    
            curve = params.find("CurveData").findall("CurveDataItem")
            curve.extend(params.find("SwaptionVolCurveData").findall("SwaptionVolCurveDataItem"))

            print("( %d, %d )" % (iter,j))
            for i, cdata in enumerate(curve):
                adjustment = 0.0
                if i%n>=j:
                    adjustment = iter / 100000.0
                y = float(cdata.get("Yield")) + adjustment
                cdata.set("Yield", str(y))
            tree.write("params%d.xml"%delta)
        
            subprocess.call([r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\bin\ficc_cms_spread_v01.exe",
            r"E:\MyQuantLib\quantlib\QuantLib\analysis_python\CMSRA_analysis.py\CMSRA_analysis.py\params%d.xml"%delta,
            #r"E:\MyQuantLib\quantlib\QuantLib\Examples\BermudanSwaption\ficc_racmsspread_v01_E193C08E-861B-4BCB-A33B-57A3E94F4205.xml",
            "Result%d.xml"%delta])
        
            tree = parse("Result%d.xml"%delta)
            root = tree.getroot()
            res = root.find("results").findtext("npv")
            npv = float(res)
            print("%0.5f" % npv)
            res = root.find("computationTime").findtext("ctime")
            print("time= %s" % res)
            print("-"*20)
            temp.append(npv - npv0)
        
        npvs.append(temp)
    

    rst = np.array(npvs)
    pd.DataFrame(rst).to_csv("results%d.csv"%delta, header=False, index=False)


if __name__=="__main__":
    p = Pool(8)
    parm = [-100,-75,-50,-25,-10,10,25,50,75,100]
    p.map(getPrice, parm)

