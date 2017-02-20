import numpy as np
def getGrossReturn(rf, vol, deltaT, e, participation):
    return (np.exp((rf-0.5*vol*vol)*deltaT + vol*e*np.sqrt(deltaT)) -1.0) + 1.0
    
def getPayoff(r, cumRet, localFloor, localCap, globalFloor, rf, deltaT, participation):
    return np.maximum(participation*(cumRet + np.minimum(np.maximum(r, localFloor), localCap).sum(1)), globalFloor) * np.exp(-rf*deltaT.sum())
    
def cliquet(evaluationDate, basePrice, cumRet, s0, vol, rf, notional, localCap, localFloor, globalFloor, participation, evalDates):
    #만원단위액면
    m = len(evalDates)
    n = 50000
    e = np.random.randn(n,m)    
    e = np.r_[e,-e]
    
    deltaT = np.zeros((1,m))
    for i, d in enumerate(evalDates):
        t0 = evalDates[i-1] if i>0 else evaluationDate
        deltaT[0,i] = ((d - t0).days  + (d - t0).seconds / (3600.0*24)) / 365.0
        
    r0 = getGrossReturn(rf, vol, deltaT, e, participation)
    
    #PRICE,DELTA,GAMMA
    price = np.zeros(3)
    bp = [-0.01, 0.0, +0.01]
    for i in range(3):
        r = r0.copy()
        r[:,0] = r[:,0] * s0*(1.0+bp[i]) / basePrice
        r -= 1.0
        payoff = getPayoff(r, cumRet, localFloor, localCap, globalFloor, rf, deltaT, participation)
        price[i] = notional * payoff.mean()
    
    p0 = price[1]
    delta = (price[2] - price[0]) / 2.0
    gamma = (price[0] + price[2] - 2*price[1]) / 2.0
    
    #VEGA
    vol1 = vol + 0.01
    r1 = getGrossReturn(rf, vol1, deltaT, e, participation)
    r1[:,0] = r1[:,0] * s0 / basePrice
    r1 -= 1.0
    payoff = getPayoff(r1, cumRet, localFloor, localCap, globalFloor, rf, deltaT, participation)
    vegaPrice = notional * payoff.mean()
    vega = vegaPrice - p0
    
    #RHO
    rf1 = rf + 0.01
    r1 = getGrossReturn(rf1, vol, deltaT, e, participation)
    r1[:,0] = r1[:,0] * s0 / basePrice
    r1 -= 1.0
    payoff = getPayoff(r1, cumRet, localFloor, localCap, globalFloor, rf, deltaT, participation)
    rhoPrice = notional * payoff.mean()
    rho = rhoPrice - p0
    
    #THETA
    deltaT1 = deltaT.copy()
    temp = min([deltaT1[0][0], 1.0/365])
    deltaT1[0][0] -= temp
    if len(deltaT1[0])>1:
        deltaT1[0][1] -= (1.0/365 - temp)
    r1 = getGrossReturn(rf, vol, deltaT1, e, participation)
    r1[:,0] = r1[:,0] * s0 / basePrice
    r1 -= 1.0
    payoff = getPayoff(r1, cumRet, localFloor, localCap, globalFloor, rf, deltaT1, participation)
    thetaPrice = notional * payoff.mean()
    theta = thetaPrice - p0

    nFut = delta/(50*s0*0.01);
    return np.array([p0/notional, nFut, delta, gamma, vega, theta, 
            delta/notional/(0.01*s0)*s0, gamma/notional/(0.0001*s0*s0), vega/notional/0.01, theta/notional*365.0, rho/notional/0.01])
    

    
    
if __name__=="__main__":
    import datetime as dt
    evaluationDate = dt.datetime.today()
    basePrice = 100
    cumRet = 0.01
    s0 = 100
    vol = 0.2
    rf = 0.02
    notional = 10000
    localCap = 0.07
    localFloor = -0.04
    globalFloor = 0.0
    participation = 1.0
    evalDates = np.array([dt.datetime(2016,12,31), dt.datetime(2017,1,31), dt.datetime(2017,2,28)])
    res = cliquet(evaluationDate, basePrice, cumRet, s0, vol, rf, notional, localCap, localFloor, globalFloor, participation, evalDates)
    
    print(res)