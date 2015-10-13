
/*  
 Copyright (C) 2014 Jose Aparicio
 
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
//      QuantLibAddin/gensrc/stubs/stub.excel.includes

#include <qlo/qladdindefines.hpp>
#include <ql/experimental/credit/defaultprobabilitylatentmodel.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/credit.hpp>
#include <qlo/latentmodels.hpp>
#include <qlo/valueobjects/vo_latentmodels.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlGaussianDefaultProbLM(
        char *ObjectId,
        char *Basket,
        FP *Factors,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlGaussianDefaultProbLM"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > FactorsCpp =
            ObjectHandler::fpToMatrix<double>(*Factors);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string BasketStrip = ObjectHandler::CallingRange::getStub(Basket);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlGaussianDefaultProbLM(
                ObjectIdStrip,
                BasketStrip,
                FactorsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianDefProbLM(
                valueObject,
                BasketLibObjPtr,
                FactorsCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite, valueObject);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlGaussianLMAssetCorrel(
        char *ObjectId,
        long *NameindexA,
        long *NameindexB,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlGaussianLMAssetCorrel"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NameindexALib;
        QuantLibAddin::cppToLibrary(*NameindexA, NameindexALib);

        QuantLib::Size NameindexBLib;
        QuantLibAddin::cppToLibrary(*NameindexB, NameindexBLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::GaussianDefProbLM, QuantLib::GaussianDefProbLM)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->latentVariableCorrel(
                NameindexALib,
                NameindexBLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlGaussianLMDefaultCorrel(
        char *ObjectId,
        OPER *CorrelationDate,
        long *NameindexA,
        long *NameindexB,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlGaussianLMDefaultCorrel"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t CorrelationDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*CorrelationDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date CorrelationDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*CorrelationDate), "CorrelationDate", QuantLib::Date());

        QuantLib::Size NameindexALib;
        QuantLibAddin::cppToLibrary(*NameindexA, NameindexALib);

        QuantLib::Size NameindexBLib;
        QuantLibAddin::cppToLibrary(*NameindexB, NameindexBLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::GaussianDefProbLM, QuantLib::GaussianDefProbLM)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->defaultCorrelation(
                CorrelationDateLib,
                NameindexALib,
                NameindexBLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlGaussianLMProbNHits(
        char *ObjectId,
        long *NumDefaults,
        OPER *ProbabilityDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlGaussianLMProbNHits"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ProbabilityDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ProbabilityDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NumDefaultsLib;
        QuantLibAddin::cppToLibrary(*NumDefaults, NumDefaultsLib);

        QuantLib::Date ProbabilityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ProbabilityDate), "ProbabilityDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::GaussianDefProbLM, QuantLib::GaussianDefProbLM)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->probAtLeastNEvents(
                NumDefaultsLib,
                ProbabilityDateLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlTDefaultProbLM(
        char *ObjectId,
        OPER *Torders,
        char *Basket,
        FP *Factors,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTDefaultProbLM"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<long> TordersCpp =
            ObjectHandler::operToVector<long>(*Torders, "Torders");

        std::vector<std::vector<double> > FactorsCpp =
            ObjectHandler::fpToMatrix<double>(*Factors);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Integer> TordersLib = 
            QuantLibAddin::convertVector<long, QuantLib::Integer>(TordersCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string BasketStrip = ObjectHandler::CallingRange::getStub(Basket);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlTDefaultProbLM(
                ObjectIdStrip,
                TordersCpp,
                BasketStrip,
                FactorsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TDefProbLM(
                valueObject,
                TordersLib,
                BasketLibObjPtr,
                FactorsCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite, valueObject);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlTLMAssetCorrel(
        char *ObjectId,
        long *NameindexA,
        long *NameindexB,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTLMAssetCorrel"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NameindexALib;
        QuantLibAddin::cppToLibrary(*NameindexA, NameindexALib);

        QuantLib::Size NameindexBLib;
        QuantLibAddin::cppToLibrary(*NameindexB, NameindexBLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::TDefProbLM, QuantLib::TDefProbLM)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->latentVariableCorrel(
                NameindexALib,
                NameindexBLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlTLMDefaultCorrel(
        char *ObjectId,
        OPER *CorrelationDate,
        long *NameindexA,
        long *NameindexB,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTLMDefaultCorrel"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t CorrelationDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*CorrelationDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date CorrelationDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*CorrelationDate), "CorrelationDate", QuantLib::Date());

        QuantLib::Size NameindexALib;
        QuantLibAddin::cppToLibrary(*NameindexA, NameindexALib);

        QuantLib::Size NameindexBLib;
        QuantLibAddin::cppToLibrary(*NameindexB, NameindexBLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::TDefProbLM, QuantLib::TDefProbLM)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->defaultCorrelation(
                CorrelationDateLib,
                NameindexALib,
                NameindexBLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlTLMProbNHits(
        char *ObjectId,
        long *NumDefaults,
        OPER *ProbabilityDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlTLMProbNHits"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ProbabilityDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ProbabilityDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NumDefaultsLib;
        QuantLibAddin::cppToLibrary(*NumDefaults, NumDefaultsLib);

        QuantLib::Date ProbabilityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*ProbabilityDate), "ProbabilityDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::TDefProbLM, QuantLib::TDefProbLM)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->probAtLeastNEvents(
                NumDefaultsLib,
                ProbabilityDateLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
