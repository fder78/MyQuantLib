# -*- coding: utf-8 -*-
"""
Created on Wed Feb 15 13:33:36 2017

@author: 081828
"""
import QuantLib as ql
def str2period(s):
    s = s.lower()
    if s=="annually" or s=="annual" or s=="a":
        return ql.Period(1, ql.Years)
    elif s=="semiannually" or s=="semiannual" or s=="sa":
        return ql.Period(6, ql.Months)
    elif s=="quarterly" or s=="quarter" or s=="q":
        return ql.Period(3, ql.Months)
    elif s=="monthly" or s=="month" or s=="m":
        return ql.Period(1, ql.Months)
    else:
        print("Period String Error")
        
def str2bdc(s):
    s = s.lower()
    if s=="following" or s=="f":
        return ql.Following
    elif s=="modifiedfollowing" or s=="mf":
        return ql.ModifiedFollowing
    elif s=="preceding" or s=="p":
        return ql.Preceding
    elif s=="modifiedpreceding" or s=="mp":
        return ql.ModifiedPreceding
    else:
        print("Period String Error")
    
def str2dc(s):
    s = s.lower()
    if s=="actual365fixed" or s=="act365":
        return ql.Actual365Fixed()
    elif s=="actualactual" or s=="actact":
        return ql.ActualActual()
    elif s=="actual360" or s=="act360":
        return ql.Actual360()
    elif s=="Thirty360" or s=="30360":
        return ql.Thirty360()
    else:
        print("Period String Error")
        