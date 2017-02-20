# -*- coding: utf-8 -*-
"""
Created on Tue Jan  3 16:11:31 2017

@author: Daishin
"""

from QuantLib import *
import numpy as np
import dateutil.relativedelta as dr

def barrierprice(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, process):
    
    Settings.instance().evaluationDate = todaysDate
    if (barrierType==Barrier.DownIn or barrierType==Barrier.DownOut) and process.x0()<=barrierPrice:
        hasKnocked = True
    elif (barrierType==Barrier.UpIn or barrierType==Barrier.UpOut) and process.x0()>=barrierPrice:
        hasKnocked = True
    
    exercise = EuropeanExercise(exerciseDate)
    payoff = PlainVanillaPayoff(optionType, exercisePrice)    
    if hasKnocked==True:
        df = process.riskFreeRate().discount(exerciseDate)
        value = rebate * df
    else:
        #############################################################################
        # method: analytic
        option = BarrierOption(barrierType, barrierPrice, rebate, payoff, exercise)
        option.setPricingEngine(AnalyticBarrierEngine(process))
        value = [option.NPV()]

    return np.array(value)
    

def pricing(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, s0, rf, div, vol):
    
    underlying = SimpleQuote(s0)
    volQuote = SimpleQuote(vol)
    volatility = BlackConstantVol(todaysDate, SouthKorea(), QuoteHandle(volQuote), Actual365Fixed())
    
    process = BlackScholesMertonProcess(QuoteHandle(underlying),
                                        YieldTermStructureHandle(div),
                                        YieldTermStructureHandle(rf),
                                        BlackVolTermStructureHandle(volatility))
    
    value = barrierprice(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, process)
    
    #Delta / Gamma
    underlying.setValue(s0*1.01)    
    vup = barrierprice(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, process)
    underlying.setValue(s0*0.99)
    vdn = barrierprice(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, process)
    delta = (vup-vdn) / 2.0
    gamma = 0.5* (vup + vdn - 2*value)
    underlying.setValue(s0)
    
    #vega    
    volQuote.setValue(vol+0.01)
    vvega = barrierprice(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, process)
    vega = vvega-value
    volQuote.setValue(vol)
    
    #rho
    '''
    rfQuote.setValue(rf+0.0001)
    vrho = barrierprice(todaysDate, exerciseDate, optionType, exercisePrice, barrierType, barrierPrice, rebate, process)
    rho = vrho-value
    rfQuote.setValue(rf)
    '''
    #1-day Theta
    e1 = exerciseDate - Period(1,Days)
    if todaysDate > e1:
        vtheta = 0
    else :
        vtheta = barrierprice(todaysDate, e1, optionType, exercisePrice, barrierType, barrierPrice, rebate, hasKnocked, process)    
    theta = (vtheta - value)
    res = np.array([s0, value, delta, gamma, vega, theta])

    return res