from QuantLib import *
import numpy as np
import matplotlib.pyplot as plt
import time

def showGraph(f):
    underlyingPrice = np.linspace(0,130,131)
    v_payoff = np.vectorize(f)
    payoffs = v_payoff(underlyingPrice)
    plt.plot(underlyingPrice, payoffs, '-')

startPoint = [0, 60, 100]
startPayoff = [0, 60, 105]
slopes = [1, 0, 0]

KIPayoff = GeneralPayoff(startPoint, startPayoff, slopes)
redemptionPayoff = GeneralPayoff([0],[105],[0])

#Show the Payoffs
showGraph(redemptionPayoff)
showGraph(KIPayoff)


###################################################
today = Date.todaysDate()
Settings.instance().evaluationDate = today
notional = 10000
cpnRate = 0.045
dates = Schedule(today, today+Period(3,Years), Period(6,Months), SouthKorea(), Following, Following, DateGeneration.Forward, False)
barriers = [90,90,85,85,80,60]

autocallDates = [];
paymentDates = [];
autocallConditions = AutocallConditionVector();
autocallPayoffs = BasketPayoffVector();

for i in range(1,7):
    condition = MinUpCondition(barriers[i-1])
    autocallConditions.push_back(condition)
    redemptionPayoff = MinBasketPayoff2(GeneralPayoff([0],[100*(1+cpnRate*i/2.0)],[0]))
    autocallPayoffs.push_back(redemptionPayoff)
terPayoff = GeneralPayoff([0,60], [0,100*(1+cpnRate*3)], [1,0])
terminalPayoff = MinBasketPayoff2(terPayoff)
product = AutocallableNote(notional, dates, dates, autocallConditions, autocallPayoffs, terminalPayoff)
#product.withKIBarrier(MinDownCondition(55), MinBasketPayoff2(KIPayoff))
#product.hasKnockedIn()

# market data
underlying1 = SimpleQuote(100.0)
riskFreeRate = FlatForward(today, 0.02, Actual365Fixed())
volatility1 = BlackConstantVol(today, TARGET(), 0.20, Actual365Fixed())
dividendYield1 = FlatForward(today, 0.01, Actual365Fixed())
underlying2 = SimpleQuote(100.0)
volatility2 = BlackConstantVol(today, TARGET(), 0.20, Actual365Fixed())
dividendYield2 = FlatForward(today, 0.01, Actual365Fixed())

process1 = BlackScholesMertonProcess(QuoteHandle(underlying1),
                                    YieldTermStructureHandle(dividendYield1),
                                    YieldTermStructureHandle(riskFreeRate),
                                    BlackVolTermStructureHandle(volatility1))

process2 = BlackScholesMertonProcess(QuoteHandle(underlying2),
                                    YieldTermStructureHandle(dividendYield2),
                                    YieldTermStructureHandle(riskFreeRate),
                                    BlackVolTermStructureHandle(volatility2))
correlation = 0.6

engine = FdAutocallEngine(process1, process2, correlation)
product.setPricingEngine(engine)

print("NPV = ",product.NPV())
print("delta = ",product.delta())
print("gamma = ",product.gamma())
print("theta = ",product.theta())


###################################
#Prices & Greeks wrt. Underlying
###################################
price = np.linspace(10,150,30)
npvs = np.zeros(price.shape)
delta = np.zeros(price.shape)
gamma = np.zeros(price.shape)
theta = np.zeros(price.shape)
xgamma = np.zeros(price.shape)

for i, p in enumerate(price):
    t0 = time.time()
    underlying1.setValue(p)
    underlying2.setValue(p)
    product.recalculate()
    npvs[i] = product.NPV()
    delta[i] = product.delta()[0]
    gamma[i] = product.gamma()[0]
    xgamma[i] = product.xgamma()[0]
    theta[i] = product.theta()[0]
    t1 = time.time()
    print("time = ", t1-t0)    

print(npvs)

fig, ax = plt.subplots(2,2, figsize=(10,10))
ax[0,0].plot(price,xgamma,'-s')
ax[0,0].set_title("X-Gamma")
ax[0,1].plot(price,delta,'-s')
ax[0,1].set_title("Delta")
ax[1,0].plot(price,theta,'-s')
ax[1,0].set_title("Theta")
ax[1,1].plot(price,gamma,'-s')
ax[1,1].set_title("Gamma")
fig.show()


fig1, ax1 = plt.subplots(1,1, figsize=(6,4))
ax1.plot(price,npvs,'-s')
ax1.set_title("NPV")
fig1.show()

