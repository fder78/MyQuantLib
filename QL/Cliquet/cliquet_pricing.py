
# -*- coding: utf-8 -*-
from __future__ import division
import datetime as dt
import xlwings as xw
import numpy as np
import pandas as pd
import cliquet_function
import time

#import pp

def foo(args):
    import cliquet_function
    import numpy as np
    import dateutil.relativedelta as dr
    (evaluationDate, INFOSTART, data, i) = args
    (basePrice, cumRet, s0, vol, rf) = \
        [data[j+INFOSTART][i] for j in range(5)]
    (notional, localCap, localFloor, globalFloor, participation) = \
        [data[j+INFOSTART+5][i] for j in range(5)]          
    evalDates = []
    for j in range(13): 
        d = data[j+INFOSTART+10][i]
        if type(d)!=pd.tslib.NaTType:
            evalDates.append(d + dr.relativedelta(hours=15, minutes=45))
        else:
            break
    evalDates = np.array(evalDates)
    evalDates = evalDates[evalDates>evaluationDate]
    
    p = cliquet_function.cliquet(evaluationDate, basePrice, cumRet, s0, vol, rf, \
                    notional/10000, localCap, localFloor, globalFloor, participation, evalDates)
    return p

    
def main():
    t0 = time.time() 
    sht = xw.Book.caller().sheets[0]    
    evaluationDate = sht.range('EvalDate').options(dates=dt.datetime).value
    data = sht.range('START').expand().options(pd.DataFrame, index=False, header=False).value
    (n,m) = data.shape
    
    INFOSTART = 0   
    
    res = np.zeros((n,11))
    inputs = [(evaluationDate, INFOSTART, data, i) for i in range(n)]
    '''
    job_server = pp.Server(8)
    jobs = [job_server.submit(foo, (d,), (), ("cliquet_function","numpy")) for d in inputs]
    for i, j in enumerate(jobs):
        p = j()
        res[i,:] = p
    '''
    for i, d in enumerate(inputs):
        p = foo(d)
        res[i,:] = p

        
    sht.range('B8').value = res 
    sht.range('B7').value = res.sum(0)
    sht.range('E3').value = "Comutation Time = {0:0.2f}".format(time.time() - t0)
    if __name__=="__main__":
        print(res)
    
if __name__=="__main__":
    sht = xw.Book.caller().sheets[0]    
    data = sht.range('START').expand().options(pd.DataFrame, index=False, header=False).value
    xw.Book('cliquet_new_161215.xlsm').set_mock_caller()
    main()