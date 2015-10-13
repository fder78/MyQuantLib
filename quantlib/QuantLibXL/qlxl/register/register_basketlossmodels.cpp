
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

// register functions in category Basketlossmodels with Excel

void registerBasketlossmodels(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlBaseCorrelationLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCPPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlBaseCorrelationLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5C""ObjectId,BaseModel,BaseCorrelationSurface,Recoveries,InitiTraits,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class BaseCorrelationLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4F""The base algorithm on which the EL is to be computed at different correlations."),
            TempStrNoSize("\x19""Base correlation surface."),
            TempStrNoSize("\x2D""Quoted recoveries for each name in the model."),
            TempStrNoSize("\x41""Copula initialization traits are defined in terms of this vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlGBinomialLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlGBinomialLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,Factors,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class GaussianBinomialLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlGMCLossModel"),
            // parameter codes
            TempStrNoSize("\x09""CCKPNPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlGMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,Factors,RecoveyRates,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class GaussianRandomDefaultLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x16""qlGRandomRRMCLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCKPENPPL#"),
            // function display name
            TempStrNoSize("\x16""qlGRandomRRMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4F""ObjectId,Factors,RecoveyRates,ModelA,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class GaussianRandomLossLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""Recovery deviation parameter."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlGRecursiveLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlGRecursiveLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,Factors,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class RecursiveGaussLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGSaddlePointLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlGSaddlePointLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,Factors,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class SaddlePointLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlGaussianLHPLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCEPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlGaussianLHPLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Correlation,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class GaussianLHPLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Gaussian model single correlation."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x16""qlIHGaussPoolLossModel"),
            // parameter codes
            TempStrNoSize("\x09""CCEPNPPL#"),
            // function display name
            TempStrNoSize("\x16""qlIHGaussPoolLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,Correlation,RecoveyRates,NumBuckets,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class IHGaussPoolLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""Model single correlation."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x24""Number of distribution loss buckets."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x18""qlIHStudentPoolLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCEPPNPPL#"),
            // function display name
            TempStrNoSize("\x18""qlIHStudentPoolLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,Correlation,RecoveyRates,Ttraits,NumBuckets,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class IHStudentPoolLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""Model single correlation."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x24""Number of distribution loss buckets."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x14""qlTBinomialLossmodel"),
            // parameter codes
            TempStrNoSize("\x09""CCKPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlTBinomialLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,Factors,RecoveyRates,Ttraits,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class TBinomialLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlTMCLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCKPPNPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlTMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,Factors,RecoveyRates,Ttraits,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class TRandomDefaultLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x16""qlTRandomRRMCLossModel"),
            // parameter codes
            TempStrNoSize("\x0B""CCKPPENPPL#"),
            // function display name
            TempStrNoSize("\x16""qlTRandomRRMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x57""ObjectId,Factors,RecoveyRates,Ttraits,ModelA,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class TRandomLossLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x1D""Recovery deviation parameter."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x17""qlTSaddlePointLossmodel"),
            // parameter codes
            TempStrNoSize("\x09""CCKPPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlTSaddlePointLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,Factors,RecoveyRates,Ttraits,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class TSaddlePointLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Basketlossmodels with Excel

void unregisterBasketlossmodels(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlBaseCorrelationLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCCCPPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlBaseCorrelationLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5C""ObjectId,BaseModel,BaseCorrelationSurface,Recoveries,InitiTraits,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class BaseCorrelationLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4F""The base algorithm on which the EL is to be computed at different correlations."),
            TempStrNoSize("\x19""Base correlation surface."),
            TempStrNoSize("\x2D""Quoted recoveries for each name in the model."),
            TempStrNoSize("\x41""Copula initialization traits are defined in terms of this vector."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlBaseCorrelationLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x14""qlGBinomialLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlGBinomialLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,Factors,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class GaussianBinomialLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlGBinomialLossmodel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlGMCLossModel"),
            // parameter codes
            TempStrNoSize("\x09""CCKPNPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlGMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,Factors,RecoveyRates,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class GaussianRandomDefaultLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlGMCLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x16""qlGRandomRRMCLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCKPENPPL#"),
            // function display name
            TempStrNoSize("\x16""qlGRandomRRMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4F""ObjectId,Factors,RecoveyRates,ModelA,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class GaussianRandomLossLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""Recovery deviation parameter."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlGRandomRRMCLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x15""qlGRecursiveLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlGRecursiveLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,Factors,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class RecursiveGaussLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlGRecursiveLossmodel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGSaddlePointLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlGSaddlePointLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x39""ObjectId,Factors,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class SaddlePointLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlGSaddlePointLossmodel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x16""qlGaussianLHPLossmodel"),
            // parameter codes
            TempStrNoSize("\x08""CCEPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlGaussianLHPLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Correlation,RecoveyRates,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class GaussianLHPLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Gaussian model single correlation."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlGaussianLHPLossmodel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x16""qlIHGaussPoolLossModel"),
            // parameter codes
            TempStrNoSize("\x09""CCEPNPPL#"),
            // function display name
            TempStrNoSize("\x16""qlIHGaussPoolLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x48""ObjectId,Correlation,RecoveyRates,NumBuckets,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class IHGaussPoolLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""Model single correlation."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x24""Number of distribution loss buckets."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlIHGaussPoolLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x18""qlIHStudentPoolLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCEPPNPPL#"),
            // function display name
            TempStrNoSize("\x18""qlIHStudentPoolLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,Correlation,RecoveyRates,Ttraits,NumBuckets,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Construct an object of class IHStudentPoolLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""Model single correlation."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x24""Number of distribution loss buckets."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlIHStudentPoolLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x14""qlTBinomialLossmodel"),
            // parameter codes
            TempStrNoSize("\x09""CCKPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlTBinomialLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,Factors,RecoveyRates,Ttraits,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class TBinomialLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlTBinomialLossmodel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlTMCLossModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCKPPNPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlTMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x50""ObjectId,Factors,RecoveyRates,Ttraits,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class TRandomDefaultLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlTMCLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x16""qlTRandomRRMCLossModel"),
            // parameter codes
            TempStrNoSize("\x0B""CCKPPENPPL#"),
            // function display name
            TempStrNoSize("\x16""qlTRandomRRMCLossModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x57""ObjectId,Factors,RecoveyRates,Ttraits,ModelA,NumSimulations,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class TRandomLossLM and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x1D""Recovery deviation parameter."),
            TempStrNoSize("\x0F""MC simulations."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlTRandomRRMCLossModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x17""qlTSaddlePointLossmodel"),
            // parameter codes
            TempStrNoSize("\x09""CCKPPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlTSaddlePointLossmodel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,Factors,RecoveyRates,Ttraits,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x11""QuantLib - Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class TSaddlePointLossModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""Systemic model factors."),
            TempStrNoSize("\x32""Recovery rates of each live name in the portfolio."),
            TempStrNoSize("\x18""T orders on each factor."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlTSaddlePointLossmodel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

