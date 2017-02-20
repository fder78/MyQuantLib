from QuantLib import *
import numpy as np
import matplotlib.pyplot as plt
import time

today = Date.todaysDate()
Settings.instance().evaluationDate = today
notional = 10000
cpnRate = 0.045
dates = Schedule(today, today+Period(3,Years), Period(6,Months), SouthKorea(), Following, Following, DateGeneration.Forward, False)
barriers = [[90,90],[90,90],[85,85],[85,85],[80,80],[80,80]]
kibarrier = [50,50];

rf = 0.02
discRate = 0.025
(s1, v1, div1) = (100, 0.2, 0.01)
(s2, v2, div2) = (100, 0.2, 0.01)


autocallDates = [];
paymentDates = [];
autocallConditions = AutocallConditionVector();
autocallPayoffs = BasketPayoffVector();

for i in range(1,7):
    condition = MinUpCondition(barriers[i-1])
    autocallConditions.push_back(condition)
    redemptionPayoff = MinBasketPayoff2(GeneralPayoff([0],[100*(1+cpnRate*i/2.0)],[0]))
    autocallPayoffs.push_back(redemptionPayoff)

#terminal payoff (Not Knocked in)    
terPayoff1 = GeneralPayoff([0,kibarrier[0]], [0,100*(1+cpnRate*3)], [1,0])
terPayoff2 = GeneralPayoff([0,kibarrier[1]], [0,100*(1+cpnRate*3)], [1,0])
terPayoff = PayoffVector()
terPayoff.push_back(terPayoff1)
terPayoff.push_back(terPayoff2)
mop = MinOfPayoffs(terPayoff)
terminalPayoff = GeneralBasketPayoff(mop)

#terminal payoff (Knocked in)
kip1 = GeneralPayoff([0,barriers[-1][0]], [0,100*(1+cpnRate*3)], [1,0])
kip2 = GeneralPayoff([0,barriers[-1][1]], [0,100*(1+cpnRate*3)], [1,0])
kiPayoff = PayoffVector()
kiPayoff.push_back(kip1)
kiPayoff.push_back(kip2)
mop_ki = MinOfPayoffs(kiPayoff)
KIPayoff = GeneralBasketPayoff(mop_ki)

product = AutocallableNote(notional, dates, dates, autocallConditions, autocallPayoffs, terminalPayoff)
product.withKIBarrier(MinDownCondition(kibarrier), KIPayoff)
#product.hasKnockedIn()

for i in range(10):
    # market data
    underlying1 = SimpleQuote(s1)
    discountCurve = FlatForward(today, discRate, Actual365Fixed())
    riskFreeRate = FlatForward(today, rf+i/1000, Actual365Fixed())
    volatility1 = BlackConstantVol(today, TARGET(), v1, Actual365Fixed())
    dividendYield1 = FlatForward(today, div1, Actual365Fixed())
    underlying2 = SimpleQuote(s2)
    volatility2 = BlackConstantVol(today, TARGET(), v2, Actual365Fixed())
    dividendYield2 = FlatForward(today, div2, Actual365Fixed())
    
    process1 = BlackScholesMertonProcess(QuoteHandle(underlying1),
                                        YieldTermStructureHandle(dividendYield1),
                                        YieldTermStructureHandle(riskFreeRate),
                                        BlackVolTermStructureHandle(volatility1))
    
    process2 = BlackScholesMertonProcess(QuoteHandle(underlying2),
                                        YieldTermStructureHandle(dividendYield2),
                                        YieldTermStructureHandle(riskFreeRate),
                                        BlackVolTermStructureHandle(volatility2))
    correlation = 0.6
    
    engine = FdAutocallEngine(discountCurve, process1, process2, correlation)
    product.setPricingEngine(engine)
    
    print("NPV = ",product.NPV())
    #print("delta = ",product.delta())
    #print("gamma = ",product.gamma())
    #print("theta = ",product.theta())
    #print("XGamma = ",product.xgamma())


###################################
#Prices & Greeks wrt. Underlying
###################################
'''
price = np.linspace(99.5,101.5)
npvs = np.zeros(price.shape)
delta = np.zeros((len(price),2))
gamma = np.zeros((len(price),2))
theta = np.zeros(price.shape)
xgamma = np.zeros(price.shape)

for i, p in enumerate(price):
    t0 = time.time()
    underlying1.setValue(p)
    underlying2.setValue(p)
    product.recalculate()
    npvs[i] = product.NPV()
    delta[i,0] = product.delta()[0]
    gamma[i,0] = product.gamma()[0]
    delta[i,1] = product.delta()[1]
    gamma[i,1] = product.gamma()[1]
    xgamma[i] = product.xgamma()[0][1]
    theta[i] = product.theta()[0]
    t1 = time.time()
    print("time = ", t1-t0)    

print(npvs)

fig, ax = plt.subplots(2,2, figsize=(10,10))
ax[0,0].plot(price,xgamma,'-s')
ax[0,0].set_title("X-Gamma")
ax[0,1].plot(price,delta,'-s')
ax[0,1].set_title("Delta")
ax[0,1].legend(['delta1','delta2'])
ax[1,0].plot(price,theta,'-s')
ax[1,0].set_title("Theta")
ax[1,1].plot(price,gamma,'-s')
ax[1,1].set_title("Gamma")
ax[1,1].legend(['gamma1','gamma2'])
fig.show()


fig1, ax1 = plt.subplots(1,1, figsize=(6,4))
ax1.plot(price,npvs,'-s')
ax1.set_title("NPV")
fig1.show()
'''
