from QuantLib import *
import numpy as np
import matplotlib.pyplot as plt

def showGraph(f):
    underlyingPrice = np.linspace(0,130,131)
    v_payoff = np.vectorize(f)
    payoffs = v_payoff(underlyingPrice)
    plt.plot(underlyingPrice, payoffs, '-')

startPoint = [0, 60, 100]
startPayoff = [0, 60, 105]
slopes = [1, 0, 0]

terPayoff = GeneralPayoff(startPoint, startPayoff, slopes)
redemptionPayoff = GeneralPayoff([0],[105],[0])

#Show the Payoffs
showGraph(redemptionPayoff)
showGraph(terPayoff)


###################################################
today = Date.todaysDate()
Settings.instance().evaluationDate = today
notional = 10000
cpnRate = 0.05
dates = Schedule(today, today+Period(3,Years), Period(6,Months), SouthKorea(), Following, Following, DateGeneration.Forward, False)
barriers = [90,90,85,85,80,60]

autocallDates = [];
paymentDates = [];
autocallConditions = AutocallConditionVector();
autocallPayoffs = BasketPayoffVector();

for i in range(1,7):
    condition = MinUpCondition(barriers[i-1])
    autocallConditions.push_back(condition)
    redemptionPayoff = MinBasketPayoff2(GeneralPayoff([0],[notional*(1+cpnRate*i/2.0)],[0]))
    autocallPayoffs.push_back(redemptionPayoff)
terminalPayoff = MinBasketPayoff2(terPayoff)

product = AutocallableNote(notional, dates, dates, autocallConditions, autocallPayoffs, terminalPayoff)


# market data
underlying1 = SimpleQuote(100.0)
riskFreeRate = FlatForward(today, 0.05, Actual365Fixed())
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

'''
procs = StochasticProcessVector()
procs.push_back(process1)
procs.push_back(process2)

matrix = Matrix(2,2)
matrix[0][0] = 1.0
matrix[1][1] = 1.0
matrix[0][1] = 0.5
matrix[1][0] = 0.5
process = StochasticProcessArray(procs, matrix)
'''

engine = FdAutocallEngine(process1, process2, correlation)
product.setPricingEngine(engine)

print(product.isExpired())
print("NPV = ",product.NPV())
print("delta = ",product.delta())
print("gamma = ",product.gamma())
print("theta = ",product.theta())




















