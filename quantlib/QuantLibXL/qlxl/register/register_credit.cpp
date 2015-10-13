
/*  
 Copyright (C) 2004, 2005, 2006, 2007, 2008 Eric Ehlers
 
 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// This file was generated automatically by gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      gensrc/gensrc/stubs/stub.excel.register.file

#include <xlsdk/xlsdkdefines.hpp>

// register functions in category Credit with Excel

void registerCredit(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBaseCorrelationTermStructure"),
            // parameter codes
            TempStrNoSize("\x0E""CCCNCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlBaseCorrelationTermStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,InterpolatorType,SettlementDays,Calendar,Convention,Tenors,LossLevel,Correlations,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class BaseCorrelationTermStructure and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x44""The bidimensional interpolation policy over the correlation surface."),
            TempStrNoSize("\x1A""Numebr of settlement days."),
            TempStrNoSize("\x09""Calendar."),
            TempStrNoSize("\x10""Time convention."),
            TempStrNoSize("\x0E""Surface tenors"),
            TempStrNoSize("\x3E""Surface loss levels as a fraction of the underlying portfolio."),
            TempStrNoSize("\x13""Correlation quotes."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBaseCorrelationValue"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x16""qlBaseCorrelationValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,Date,LossLevel,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the interpolated base correlation value."),
            // parameter descriptions
            TempStrNoSize("\x41""id of existing QuantLibAddin::BaseCorrelationTermStructure object"),
            TempStrNoSize("\x13""Interpolation date."),
            TempStrNoSize("\x19""Interpolation loss level."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCdsOptionEngine"),
            // parameter codes
            TempStrNoSize("\x0A""CCCECPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCdsOptionEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,DefaultCurve,RecoveryRate,YieldCurve,BlackVol,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class BlackCdsOptionEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x11""Black Volatility."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlCDSOption"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlCDSOption"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""ObjectId,UnderlyingCDS,Exercise,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class CdsOption and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""The CDS underlying the option."),
            TempStrNoSize("\x13""Exercise object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCdsCouponLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlCdsCouponLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x13""Returns the CL NPV."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCdsDefaultLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlCdsDefaultLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x13""Returns the DL NPV."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlCdsFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlCdsFairSpread"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns the running spread that, given the quoted recovery rate, will make the running-only CDS have an NPV of 0."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlCdsFairUpfront"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x10""qlCdsFairUpfront"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x82""Returns the upfront spread that, given the running spread and the quoted recovery rate, will make the instrument have an NPV of 0."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCdsOptionImpliedVol"),
            // parameter codes
            TempStrNoSize("\x08""ECECCEP#"),
            // function display name
            TempStrNoSize("\x15""qlCdsOptionImpliedVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""ObjectId,Price,YieldCurve,DefaultCurve,RecoveryRate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""Implied black CDS option volatility."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::CdsOption object"),
            TempStrNoSize("\x0D""Market price."),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // parameter codes
            TempStrNoSize("\x11""CCPEEECPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAD""ObjectId,BuyerSeller,Notional,Upfront,Spread,PremiumSchedule,PaymentConvention,DayCounter,SettlesAccrual,PayAtDefault,ProtectionStart,UpfrontDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class CreditDefaultSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x0E""Nominal amount"),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x38""protection start date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x2F""upfront date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlDefaultEvent"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlDefaultEvent"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6A""ObjectId,EventType,EventDate,Currency,Seniority,SettlementDate,SettledRecovery,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class DefaultEventSet and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x30""The type of default event. Default value = NONE."),
            TempStrNoSize("\x2D""Event date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x41""Curency of the reference bond affected. Default value = Currency."),
            TempStrNoSize("\x3C""Seniority of the bond affected. Default value = NoSeniority."),
            TempStrNoSize("\x38""Event settlement date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x34""Event settlement recovery rate. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x09""qlHRDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x09""qlHRDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Dates on which the hazard rate interpolation is performed."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::PiecewiseHazardRateCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x08""qlHRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x08""qlHRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Dates on which the hazard rate interpolation is performed."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::PiecewiseHazardRateCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x45""ObjectId,CurveDates,CurveRates,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class HazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4C""dates of the curve. First date corresponds to a survival probability of one."),
            TempStrNoSize("\x21""hazard rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlIntegralNtdEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x13""qlIntegralNtdEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,IntegrationStep,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class IntegralNtdEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""Integration step period."),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x08""qlIssuer"),
            // parameter codes
            TempStrNoSize("\x08""CCPCPPL#"),
            // function display name
            TempStrNoSize("\x08""qlIssuer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""ObjectId,DefaultCurves,DefaultEvents,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Construct an object of class Issuer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x75""Default probability curve. By now it is associated to SeniorSec, EUR and NorthAmericaCorpDefaultKey Default value = ."),
            TempStrNoSize("\x24""Credit events affecting this issuer."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x13""qlMidPointCDOEngine"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x13""qlMidPointCDOEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class MidPointCDOEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // parameter codes
            TempStrNoSize("\x09""CCCECPPL#"),
            // function display name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,DefaultCurve,RecoveryRate,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class MidPointCdsEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlNthToDefault"),
            // parameter codes
            TempStrNoSize("\x0F""CCCNPCEECELPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlNthToDefault"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7F""ObjectId,Basket,Order,BuyerSeller,PremiumSchedule,Upfront,Spread,DayCounter,Notional,SettlesAccrual,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class NthToDefault and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Underlying tranched portfolio."),
            TempStrNoSize("\x17""Contract default order."),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0E""Nominal amount"),
            TempStrNoSize("\x1B""Accrual settled at default."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,ReferenceDate,RateHelpers,DayCounter,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class PiecewiseFlatForwardCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x40""term structure reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x17""vector of rate-helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlPiecewiseHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPCCPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlPiecewiseHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x57""ObjectId,Helpers,DayCounter,Calendar,Interpolation,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class PiecewiseHazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x26""vector of default probability helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x22""The interpolator for hazard rates."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x10""qlRiskyFixedBond"),
            // parameter codes
            TempStrNoSize("\x11""CCCCECCECPECPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlRiskyFixedBond"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9D""ObjectId,Bondname,Currency,Recovery,DefaultCurve,Schedule,Rate,DayCounter,PaymentConvention,Notional,DiscountingCurve,PricingDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class RiskyFixedBond and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x09""Bonds id."),
            TempStrNoSize("\x27""Curency of the reference bond affected."),
            TempStrNoSize("\x0E""Recovery Rate."),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x09""Schedule."),
            TempStrNoSize("\x05""Rate."),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x09""Notional."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x11""desired npv date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 26, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // parameter codes
            TempStrNoSize("\x12""CCPCPCCCCCECPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB8""ObjectId,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecoveryRate,DiscountingCurve,SettleAccrual,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class SpreadCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlSyntheticCDO"),
            // parameter codes
            TempStrNoSize("\x0D""CCCPCEECPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlSyntheticCDO"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x73""ObjectId,Basket,BuyerSeller,PremiumSchedule,Upfront,Spread,DayCounter,PaymentConvention,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class SyntheticCDO and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Underlying tranched portfolio."),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // parameter codes
            TempStrNoSize("\x14""CCPECPCCCCCECNPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xC3""ObjectId,UpfrontSpread,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecRate,DiscCurve,UpfSettlDays,SettlAccr,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class UpfrontCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""upfront spread quote."),
            TempStrNoSize("\x0F""running spread."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x17""upfront settlement days"),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Credit with Excel

void unregisterCredit(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBaseCorrelationTermStructure"),
            // parameter codes
            TempStrNoSize("\x0E""CCCNCCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlBaseCorrelationTermStructure"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x81""ObjectId,InterpolatorType,SettlementDays,Calendar,Convention,Tenors,LossLevel,Correlations,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class BaseCorrelationTermStructure and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x44""The bidimensional interpolation policy over the correlation surface."),
            TempStrNoSize("\x1A""Numebr of settlement days."),
            TempStrNoSize("\x09""Calendar."),
            TempStrNoSize("\x10""Time convention."),
            TempStrNoSize("\x0E""Surface tenors"),
            TempStrNoSize("\x3E""Surface loss levels as a fraction of the underlying portfolio."),
            TempStrNoSize("\x13""Correlation quotes."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlBaseCorrelationTermStructure"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBaseCorrelationValue"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x16""qlBaseCorrelationValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,Date,LossLevel,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the interpolated base correlation value."),
            // parameter descriptions
            TempStrNoSize("\x41""id of existing QuantLibAddin::BaseCorrelationTermStructure object"),
            TempStrNoSize("\x13""Interpolation date."),
            TempStrNoSize("\x19""Interpolation loss level."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBaseCorrelationValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackCdsOptionEngine"),
            // parameter codes
            TempStrNoSize("\x0A""CCCECPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackCdsOptionEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,DefaultCurve,RecoveryRate,YieldCurve,BlackVol,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class BlackCdsOptionEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x11""Black Volatility."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackCdsOptionEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlCDSOption"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlCDSOption"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""ObjectId,UnderlyingCDS,Exercise,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class CdsOption and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""The CDS underlying the option."),
            TempStrNoSize("\x13""Exercise object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlCDSOption"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCdsCouponLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x11""qlCdsCouponLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x13""Returns the CL NPV."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlCdsCouponLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCdsDefaultLegNPV"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlCdsDefaultLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x13""Returns the DL NPV."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlCdsDefaultLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlCdsFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlCdsFairSpread"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns the running spread that, given the quoted recovery rate, will make the running-only CDS have an NPV of 0."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlCdsFairSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlCdsFairUpfront"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x10""qlCdsFairUpfront"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x82""Returns the upfront spread that, given the running spread and the quoted recovery rate, will make the instrument have an NPV of 0."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::CreditDefaultSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlCdsFairUpfront"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlCdsOptionImpliedVol"),
            // parameter codes
            TempStrNoSize("\x08""ECECCEP#"),
            // function display name
            TempStrNoSize("\x15""qlCdsOptionImpliedVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""ObjectId,Price,YieldCurve,DefaultCurve,RecoveryRate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""Implied black CDS option volatility."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::CdsOption object"),
            TempStrNoSize("\x0D""Market price."),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlCdsOptionImpliedVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // parameter codes
            TempStrNoSize("\x11""CCPEEECPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAD""ObjectId,BuyerSeller,Notional,Upfront,Spread,PremiumSchedule,PaymentConvention,DayCounter,SettlesAccrual,PayAtDefault,ProtectionStart,UpfrontDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class CreditDefaultSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x0E""Nominal amount"),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x38""protection start date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x2F""upfront date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlCreditDefaultSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlDefaultEvent"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlDefaultEvent"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6A""ObjectId,EventType,EventDate,Currency,Seniority,SettlementDate,SettledRecovery,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class DefaultEventSet and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x30""The type of default event. Default value = NONE."),
            TempStrNoSize("\x2D""Event date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x41""Curency of the reference bond affected. Default value = Currency."),
            TempStrNoSize("\x3C""Seniority of the bond affected. Default value = NoSeniority."),
            TempStrNoSize("\x38""Event settlement date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x34""Event settlement recovery rate. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlDefaultEvent"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x09""qlHRDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x09""qlHRDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Dates on which the hazard rate interpolation is performed."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::PiecewiseHazardRateCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlHRDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x08""qlHRates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x08""qlHRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Dates on which the hazard rate interpolation is performed."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::PiecewiseHazardRateCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x08""qlHRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x45""ObjectId,CurveDates,CurveRates,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class HazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4C""dates of the curve. First date corresponds to a survival probability of one."),
            TempStrNoSize("\x21""hazard rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlHazardRateCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x13""qlIntegralNtdEngine"),
            // parameter codes
            TempStrNoSize("\x08""CCCCPPL#"),
            // function display name
            TempStrNoSize("\x13""qlIntegralNtdEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3F""ObjectId,IntegrationStep,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class IntegralNtdEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x18""Integration step period."),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlIntegralNtdEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x08""qlIssuer"),
            // parameter codes
            TempStrNoSize("\x08""CCPCPPL#"),
            // function display name
            TempStrNoSize("\x08""qlIssuer"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x40""ObjectId,DefaultCurves,DefaultEvents,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Construct an object of class Issuer and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x75""Default probability curve. By now it is associated to SeniorSec, EUR and NorthAmericaCorpDefaultKey Default value = ."),
            TempStrNoSize("\x24""Credit events affecting this issuer."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x08""qlIssuer"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x13""qlMidPointCDOEngine"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x13""qlMidPointCDOEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class MidPointCDOEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlMidPointCDOEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // parameter codes
            TempStrNoSize("\x09""CCCECPPL#"),
            // function display name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,DefaultCurve,RecoveryRate,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class MidPointCdsEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlMidPointCdsEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlNthToDefault"),
            // parameter codes
            TempStrNoSize("\x0F""CCCNPCEECELPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlNthToDefault"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7F""ObjectId,Basket,Order,BuyerSeller,PremiumSchedule,Upfront,Spread,DayCounter,Notional,SettlesAccrual,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class NthToDefault and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Underlying tranched portfolio."),
            TempStrNoSize("\x17""Contract default order."),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0E""Nominal amount"),
            TempStrNoSize("\x1B""Accrual settled at default."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlNthToDefault"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,ReferenceDate,RateHelpers,DayCounter,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class PiecewiseFlatForwardCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x40""term structure reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x17""vector of rate-helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlPiecewiseHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPCCPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlPiecewiseHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x57""ObjectId,Helpers,DayCounter,Calendar,Interpolation,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class PiecewiseHazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x26""vector of default probability helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x22""The interpolator for hazard rates."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlPiecewiseHazardRateCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x10""qlRiskyFixedBond"),
            // parameter codes
            TempStrNoSize("\x11""CCCCECCECPECPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlRiskyFixedBond"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9D""ObjectId,Bondname,Currency,Recovery,DefaultCurve,Schedule,Rate,DayCounter,PaymentConvention,Notional,DiscountingCurve,PricingDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class RiskyFixedBond and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x09""Bonds id."),
            TempStrNoSize("\x27""Curency of the reference bond affected."),
            TempStrNoSize("\x0E""Recovery Rate."),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x09""Schedule."),
            TempStrNoSize("\x05""Rate."),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x09""Notional."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x11""desired npv date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlRiskyFixedBond"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 26, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // parameter codes
            TempStrNoSize("\x12""CCPCPCCCCCECPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB8""ObjectId,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecoveryRate,DiscountingCurve,SettleAccrual,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class SpreadCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlSpreadCdsHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlSyntheticCDO"),
            // parameter codes
            TempStrNoSize("\x0D""CCCPCEECPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlSyntheticCDO"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x73""ObjectId,Basket,BuyerSeller,PremiumSchedule,Upfront,Spread,DayCounter,PaymentConvention,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class SyntheticCDO and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Underlying tranched portfolio."),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlSyntheticCDO"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // parameter codes
            TempStrNoSize("\x14""CCPECPCCCCCECNPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xC3""ObjectId,UpfrontSpread,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecRate,DiscCurve,UpfSettlDays,SettlAccr,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class UpfrontCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""upfront spread quote."),
            TempStrNoSize("\x0F""running spread."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x17""upfront settlement days"),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlUpfrontCdsHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

