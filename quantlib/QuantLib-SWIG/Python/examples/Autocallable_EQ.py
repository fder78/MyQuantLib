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

terminalPayoff = GeneralPayoff(startPoint, startPayoff, slopes)
redemptionPayoff = GeneralPayoff([0],[105],[0])

#Show the Payoffs
showGraph(redemptionPayoff)
showGraph(terminalPayoff)


###################################################
today = Date.todaysDate()
notional = 10000
cpnRate = 0.05
dates = Schedule(today, today+Period(3,Years), Period(6,Months), SouthKorea(), Following, Following, DateGeneration.Forward, False)
barriers = [90,90,85,85,80,60]

autocallDates = [];
paymentDates = [];
autocallConditions = AutocallConditionVector();
autocallPayoffs = BasketPayoffVector();

for i in range(1,7):
    autocallDates.append(dates[i])
    paymentDates.append(dates[i]+Period(3,Days))
    condition = MinUpCondition(barriers[i-1])
    autocallConditions.push_back(condition)
    redemptionPayoff = MinBasketPayoff(GeneralPayoff([0],[notional*(1+cpnRate*i/2.0)],[0]))
    autocallPayoffs.push_back(redemptionPayoff)

product = AutocallableNote(notional, autocallDates, paymentDates, autocallConditions, autocallPayoffs, terminalPayoff)

