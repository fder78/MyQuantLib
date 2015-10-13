
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

// register functions in category Latentmodels with Excel

void registerLatentmodels(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGaussianDefaultProbLM"),
            // parameter codes
            TempStrNoSize("\x08""CCCKPPL#"),
            // function display name
            TempStrNoSize("\x17""qlGaussianDefaultProbLM"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Basket,Factors,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class GaussianDefProbLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""Defaultable positions basket."),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGaussianLMAssetCorrel"),
            // parameter codes
            TempStrNoSize("\x06""PCNNP#"),
            // function display name
            TempStrNoSize("\x17""qlGaussianLMAssetCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::GaussianDefProbLM object"),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x19""qlGaussianLMDefaultCorrel"),
            // parameter codes
            TempStrNoSize("\x07""PCPNNP#"),
            // function display name
            TempStrNoSize("\x19""qlGaussianLMDefaultCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,CorrelationDate,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::GaussianDefProbLM object"),
            TempStrNoSize("\x33""Correlation date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlGaussianLMProbNHits"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x15""qlGaussianLMProbNHits"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,NumDefaults,ProbabilityDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Probability of having a given number of defaults or more."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::GaussianDefProbLM object"),
            TempStrNoSize("\x12""Number of defaults"),
            TempStrNoSize("\x2E""Target date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x10""qlTDefaultProbLM"),
            // parameter codes
            TempStrNoSize("\x09""CCPCKPPL#"),
            // function display name
            TempStrNoSize("\x10""qlTDefaultProbLM"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""ObjectId,Torders,Basket,Factors,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class TDefProbLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x20""Orders of the StudentT variates."),
            TempStrNoSize("\x1D""Defaultable positions basket."),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlTLMAssetCorrel"),
            // parameter codes
            TempStrNoSize("\x06""PCNNP#"),
            // function display name
            TempStrNoSize("\x10""qlTLMAssetCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TDefProbLM object"),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x12""qlTLMDefaultCorrel"),
            // parameter codes
            TempStrNoSize("\x07""PCPNNP#"),
            // function display name
            TempStrNoSize("\x12""qlTLMDefaultCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,CorrelationDate,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TDefProbLM object"),
            TempStrNoSize("\x33""Correlation date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlTLMProbNHits"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x0E""qlTLMProbNHits"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,NumDefaults,ProbabilityDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Probability of having a given number of defaults or more."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TDefProbLM object"),
            TempStrNoSize("\x12""Number of defaults"),
            TempStrNoSize("\x2E""Target date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Latentmodels with Excel

void unregisterLatentmodels(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGaussianDefaultProbLM"),
            // parameter codes
            TempStrNoSize("\x08""CCCKPPL#"),
            // function display name
            TempStrNoSize("\x17""qlGaussianDefaultProbLM"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Basket,Factors,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class GaussianDefProbLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""Defaultable positions basket."),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlGaussianDefaultProbLM"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGaussianLMAssetCorrel"),
            // parameter codes
            TempStrNoSize("\x06""PCNNP#"),
            // function display name
            TempStrNoSize("\x17""qlGaussianLMAssetCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::GaussianDefProbLM object"),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlGaussianLMAssetCorrel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x19""qlGaussianLMDefaultCorrel"),
            // parameter codes
            TempStrNoSize("\x07""PCPNNP#"),
            // function display name
            TempStrNoSize("\x19""qlGaussianLMDefaultCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,CorrelationDate,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::GaussianDefProbLM object"),
            TempStrNoSize("\x33""Correlation date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlGaussianLMDefaultCorrel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlGaussianLMProbNHits"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x15""qlGaussianLMProbNHits"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,NumDefaults,ProbabilityDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Probability of having a given number of defaults or more."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::GaussianDefProbLM object"),
            TempStrNoSize("\x12""Number of defaults"),
            TempStrNoSize("\x2E""Target date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlGaussianLMProbNHits"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x10""qlTDefaultProbLM"),
            // parameter codes
            TempStrNoSize("\x09""CCPCKPPL#"),
            // function display name
            TempStrNoSize("\x10""qlTDefaultProbLM"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3B""ObjectId,Torders,Basket,Factors,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class TDefProbLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x20""Orders of the StudentT variates."),
            TempStrNoSize("\x1D""Defaultable positions basket."),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlTDefaultProbLM"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlTLMAssetCorrel"),
            // parameter codes
            TempStrNoSize("\x06""PCNNP#"),
            // function display name
            TempStrNoSize("\x10""qlTLMAssetCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""ObjectId,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TDefProbLM object"),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlTLMAssetCorrel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x12""qlTLMDefaultCorrel"),
            // parameter codes
            TempStrNoSize("\x07""PCPNNP#"),
            // function display name
            TempStrNoSize("\x12""qlTLMDefaultCorrel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,CorrelationDate,NameindexA,NameindexB,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Default probability correlation."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TDefProbLM object"),
            TempStrNoSize("\x33""Correlation date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x10""First name index"),
            TempStrNoSize("\x11""Second name index"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlTLMDefaultCorrel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlTLMProbNHits"),
            // parameter codes
            TempStrNoSize("\x06""PCNPP#"),
            // function display name
            TempStrNoSize("\x0E""qlTLMProbNHits"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,NumDefaults,ProbabilityDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Probability of having a given number of defaults or more."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::TDefProbLM object"),
            TempStrNoSize("\x12""Number of defaults"),
            TempStrNoSize("\x2E""Target date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlTLMProbNHits"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

