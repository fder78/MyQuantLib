
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

// register functions in category Defaultbasket with Excel

void registerDefaultbasket(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCrediBasketAttachLive"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlCrediBasketAttachLive"),
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
            TempStrNoSize("\x18""Remaining attach amount."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCrediBasketDetachLive"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlCrediBasketDetachLive"),
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
            TempStrNoSize("\x18""Remaining detach amount."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlCreditBasket"),
            // parameter codes
            TempStrNoSize("\x0D""CCPPPPEELPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlCreditBasket"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7C""ObjectId,IssuerNames,Issuers,Notionals,ReferenceDate,AttachmentRatio,DettachmentRatio,Amortizing,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Construct an object of class Basket and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x30""Array containing the issuer names in the basket."),
            TempStrNoSize("\x11""Array of Issuers."),
            TempStrNoSize("\x2E""Notional by which each name enters the basket."),
            TempStrNoSize("\x38""Basket inception date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x31""Attachment ratio for losses affecting the basket."),
            TempStrNoSize("\x32""Dettachment ratio for losses affecting the basket."),
            TempStrNoSize("\x20""Whether is Quarterly amortizing."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCreditBasketDefaulCorrel"),
            // parameter codes
            TempStrNoSize("\x07""PCPNNP#"),
            // function display name
            TempStrNoSize("\x1A""qlCreditBasketDefaulCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,DateCorrel,IndexIssuer1,IndexIssuer2,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""Default correlation between two basket issuers."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x48""Computes the correlation on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x0B""First name."),
            TempStrNoSize("\x0C""Second name."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCreditBasketESF"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x11""qlCreditBasketESF"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,DateForLoss,PercentileValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""Basket loss expected shortfall amount (tranched)."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4C""Computes the loss percentile on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x15""Percentile requested."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCreditBasketLiveNotional"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlCreditBasketLiveNotional"),
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
            TempStrNoSize("\x2D""Non defaulted portfolio outstanding notional."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCreditBasketLoss"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlCreditBasketLoss"),
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
            TempStrNoSize("\x1B""Losses from default events."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCreditBasketNthEventP"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x17""qlCreditBasketNthEventP"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""ObjectId,EventOrder,DateForLoss,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Probability of each basket name to default in the given order."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x3B""The order of default for which the probability is returned."),
            TempStrNoSize("\x4A""Computes the probabilities on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCreditBasketPercentile"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x18""qlCreditBasketPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,DateForLoss,PercentileValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x29""Basket loss percentile amount (tranched)."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4C""Computes the loss percentile on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x15""Percentile requested."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCreditBasketProbLoss"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x16""qlCreditBasketProbLoss"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,DateForLoss,LossFractionValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Probability of basket losses to be over a value at a given date."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4A""Computes the probabilities on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x37""Value of losses as a fraction of initial tanche amount."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCreditBasketSetLossModel"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x1A""qlCreditBasketSetLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""ObjectId,DefaultLossModel,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x63""Assigns a Default Loss Model to a given basket. Subsequent basket computations will use that model."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x0B""Loss Model."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCreditBasketSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x12""qlCreditBasketSize"),
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
            TempStrNoSize("\x26""Number of counterparties at inception."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCreditBasketSplitLoss"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x17""qlCreditBasketSplitLoss"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,DateForLoss,LossValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Splits a loss amount by counterparty contribution."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4A""Computes the probabilities on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x23""Value of losses in absolute amount."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlExpectedTrancheLoss"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x15""qlExpectedTrancheLoss"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,DateForLoss,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Basket expected tranche according to the basket loss model."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4A""Computes the expected loss on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Defaultbasket with Excel

void unregisterDefaultbasket(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCrediBasketAttachLive"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlCrediBasketAttachLive"),
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
            TempStrNoSize("\x18""Remaining attach amount."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCrediBasketAttachLive"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCrediBasketDetachLive"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlCrediBasketDetachLive"),
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
            TempStrNoSize("\x18""Remaining detach amount."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCrediBasketDetachLive"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlCreditBasket"),
            // parameter codes
            TempStrNoSize("\x0D""CCPPPPEELPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlCreditBasket"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7C""ObjectId,IssuerNames,Issuers,Notionals,ReferenceDate,AttachmentRatio,DettachmentRatio,Amortizing,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Construct an object of class Basket and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x30""Array containing the issuer names in the basket."),
            TempStrNoSize("\x11""Array of Issuers."),
            TempStrNoSize("\x2E""Notional by which each name enters the basket."),
            TempStrNoSize("\x38""Basket inception date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x31""Attachment ratio for losses affecting the basket."),
            TempStrNoSize("\x32""Dettachment ratio for losses affecting the basket."),
            TempStrNoSize("\x20""Whether is Quarterly amortizing."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlCreditBasket"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCreditBasketDefaulCorrel"),
            // parameter codes
            TempStrNoSize("\x07""PCPNNP#"),
            // function display name
            TempStrNoSize("\x1A""qlCreditBasketDefaulCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,DateCorrel,IndexIssuer1,IndexIssuer2,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""Default correlation between two basket issuers."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x48""Computes the correlation on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x0B""First name."),
            TempStrNoSize("\x0C""Second name."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlCreditBasketDefaulCorrel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x11""qlCreditBasketESF"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x11""qlCreditBasketESF"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,DateForLoss,PercentileValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""Basket loss expected shortfall amount (tranched)."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4C""Computes the loss percentile on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x15""Percentile requested."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlCreditBasketESF"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCreditBasketLiveNotional"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlCreditBasketLiveNotional"),
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
            TempStrNoSize("\x2D""Non defaulted portfolio outstanding notional."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlCreditBasketLiveNotional"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCreditBasketLoss"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlCreditBasketLoss"),
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
            TempStrNoSize("\x1B""Losses from default events."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlCreditBasketLoss"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCreditBasketNthEventP"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x17""qlCreditBasketNthEventP"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x27""ObjectId,EventOrder,DateForLoss,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Probability of each basket name to default in the given order."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x3B""The order of default for which the probability is returned."),
            TempStrNoSize("\x4A""Computes the probabilities on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCreditBasketNthEventP"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlCreditBasketPercentile"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x18""qlCreditBasketPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,DateForLoss,PercentileValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x29""Basket loss percentile amount (tranched)."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4C""Computes the loss percentile on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x15""Percentile requested."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlCreditBasketPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCreditBasketProbLoss"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x16""qlCreditBasketProbLoss"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,DateForLoss,LossFractionValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Probability of basket losses to be over a value at a given date."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4A""Computes the probabilities on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x37""Value of losses as a fraction of initial tanche amount."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlCreditBasketProbLoss"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlCreditBasketSetLossModel"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x1A""qlCreditBasketSetLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""ObjectId,DefaultLossModel,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x63""Assigns a Default Loss Model to a given basket. Subsequent basket computations will use that model."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x0B""Loss Model."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlCreditBasketSetLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlCreditBasketSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x12""qlCreditBasketSize"),
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
            TempStrNoSize("\x26""Number of counterparties at inception."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlCreditBasketSize"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCreditBasketSplitLoss"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x17""qlCreditBasketSplitLoss"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,DateForLoss,LossValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Splits a loss amount by counterparty contribution."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4A""Computes the probabilities on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x23""Value of losses in absolute amount."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCreditBasketSplitLoss"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlExpectedTrancheLoss"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x15""qlExpectedTrancheLoss"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,DateForLoss,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Basket expected tranche according to the basket loss model."),
            // parameter descriptions
            TempStrNoSize("\x26""id of existing QuantLib::Basket object"),
            TempStrNoSize("\x4A""Computes the expected loss on this date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlExpectedTrancheLoss"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

