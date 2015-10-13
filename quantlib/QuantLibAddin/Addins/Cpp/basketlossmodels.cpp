
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <ql/experimental/credit/gaussianlhplossmodel.hpp>
#include <ql/experimental/credit/binomiallossmodel.hpp>
#include <ql/experimental/credit/inhomogeneouspooldef.hpp>
#include <ql/experimental/credit/correlationstructure.hpp>
#include <qlo/basketlossmodels.hpp>
#include <qlo/defaulttermstructures.hpp>
#include <qlo/valueobjects/vo_basketlossmodels.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlBaseCorrelationLossModel(
            const std::string &ObjectId,
            const std::string &BaseModel,
            const std::string &BaseCorrelationSurface,
            const std::vector<double>& Recoveries,
            const std::vector<double>& InitiTraits,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> RecoveriesLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Recoveries);

        std::vector<QuantLib::Real> InitiTraitsLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(InitiTraits);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BaseCorrelationSurfaceLibObjPtr, BaseCorrelationSurface,
            QuantLibAddin::CorrelationTermStructure, QuantLib::CorrelationTermStructure)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBaseCorrelationLossModel(
                ObjectId,
                BaseModel,
                BaseCorrelationSurface,
                Recoveries,
                InitiTraits,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BaseCorrelationLossModel(
                valueObject,
                BaseModel,
                BaseCorrelationSurfaceLibObjPtr,
                RecoveriesLib,
                InitiTraitsLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBaseCorrelationLossModel : " << e.what());
        }
    }


    std::string qlGMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NumSimulationsLib;
        QuantLibAddin::cppToLibrary(NumSimulations, NumSimulationsLib);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlGMCLossModel(
                ObjectId,
                Factors,
                RecoveyRates,
                NumSimulations,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianRandomDefaultLM(
                valueObject,
                Factors,
                RecoveyRates,
                NumSimulationsLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlGMCLossModel : " << e.what());
        }
    }


    std::string qlGRandomRRMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const double &ModelA,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NumSimulationsLib;
        QuantLibAddin::cppToLibrary(NumSimulations, NumSimulationsLib);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlGRandomRRMCLossModel(
                ObjectId,
                Factors,
                RecoveyRates,
                ModelA,
                NumSimulations,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianRandomLossLM(
                valueObject,
                Factors,
                RecoveyRates,
                ModelA,
                NumSimulationsLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlGRandomRRMCLossModel : " << e.what());
        }
    }


    std::string qlTMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NumSimulationsLib;
        QuantLibAddin::cppToLibrary(NumSimulations, NumSimulationsLib);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlTMCLossModel(
                ObjectId,
                Factors,
                RecoveyRates,
                Ttraits,
                NumSimulations,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TRandomDefaultLM(
                valueObject,
                Factors,
                RecoveyRates,
                Ttraits,
                NumSimulationsLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlTMCLossModel : " << e.what());
        }
    }


    std::string qlTRandomRRMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            const double &ModelA,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NumSimulationsLib;
        QuantLibAddin::cppToLibrary(NumSimulations, NumSimulationsLib);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlTRandomRRMCLossModel(
                ObjectId,
                Factors,
                RecoveyRates,
                Ttraits,
                ModelA,
                NumSimulations,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TRandomLossLM(
                valueObject,
                Factors,
                RecoveyRates,
                Ttraits,
                ModelA,
                NumSimulationsLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlTRandomRRMCLossModel : " << e.what());
        }
    }

}

