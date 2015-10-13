
/*  
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2006 Plamen Neykov
 
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
//      QuantLibAddin/gensrc/stubs/stub.serialization.includes

#include <qlo/serialization/create/create_basketlossmodels.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <ql/experimental/credit/gaussianlhplossmodel.hpp>
#include <ql/experimental/credit/binomiallossmodel.hpp>
#include <ql/experimental/credit/inhomogeneouspooldef.hpp>
#include <ql/experimental/credit/correlationstructure.hpp>
#include <qlo/basketlossmodels.hpp>
#include <qlo/defaulttermstructures.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlBaseCorrelationLossModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BaseModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BaseModel"));

        std::string BaseCorrelationSurface =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BaseCorrelationSurface"));

        std::vector<double> Recoveries =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Recoveries"), "Recoveries");

        std::vector<double> InitiTraits =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("InitiTraits"), "InitiTraits");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> RecoveriesLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Recoveries);

        std::vector<QuantLib::Real> InitiTraitsLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(InitiTraits);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BaseCorrelationSurfaceLibObjPtr, BaseCorrelationSurface,
            QuantLibAddin::CorrelationTermStructure, QuantLib::CorrelationTermStructure)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(BaseCorrelationSurface);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BaseCorrelationLossModel(
                valueObject,
                BaseModel,
                BaseCorrelationSurfaceLibObjPtr,
                RecoveriesLib,
                InitiTraitsLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlGBinomialLossmodel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianBinomialLossModel(
                valueObject,
                Factors,
                RecoveyRates,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlGMCLossModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        long NumSimulations =
            ObjectHandler::convert2<long>(valueObject->getProperty("NumSimulations"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianRandomDefaultLM(
                valueObject,
                Factors,
                RecoveyRates,
                NumSimulations,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlGRandomRRMCLossModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        double ModelA =
            ObjectHandler::convert2<double>(valueObject->getProperty("ModelA"));

        long NumSimulations =
            ObjectHandler::convert2<long>(valueObject->getProperty("NumSimulations"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ModelALib = ModelA;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianRandomLossLM(
                valueObject,
                Factors,
                RecoveyRates,
                ModelALib,
                NumSimulations,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlGRecursiveLossmodel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RecursiveGaussLossModel(
                valueObject,
                Factors,
                RecoveyRates,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlGSaddlePointLossmodel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SaddlePointLossModel(
                valueObject,
                Factors,
                RecoveyRates,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlGaussianLHPLossmodel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Correlation =
            ObjectHandler::convert2<double>(valueObject->getProperty("Correlation"));

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real CorrelationLib = Correlation;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianLHPLossModel(
                valueObject,
                CorrelationLib,
                RecoveyRates,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlIHGaussPoolLossModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Correlation =
            ObjectHandler::convert2<double>(valueObject->getProperty("Correlation"));

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        long NumBuckets =
            ObjectHandler::convert2<long>(valueObject->getProperty("NumBuckets"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real CorrelationLib = Correlation;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IHGaussPoolLossModel(
                valueObject,
                CorrelationLib,
                RecoveyRates,
                NumBuckets,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlIHStudentPoolLossModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Correlation =
            ObjectHandler::convert2<double>(valueObject->getProperty("Correlation"));

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        std::vector<double> Ttraits =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Ttraits"), "Ttraits");

        long NumBuckets =
            ObjectHandler::convert2<long>(valueObject->getProperty("NumBuckets"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real CorrelationLib = Correlation;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IHStudentPoolLossModel(
                valueObject,
                CorrelationLib,
                RecoveyRates,
                Ttraits,
                NumBuckets,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlTBinomialLossmodel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        std::vector<double> Ttraits =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Ttraits"), "Ttraits");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TBinomialLossModel(
                valueObject,
                Factors,
                RecoveyRates,
                Ttraits,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlTMCLossModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        std::vector<double> Ttraits =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Ttraits"), "Ttraits");

        long NumSimulations =
            ObjectHandler::convert2<long>(valueObject->getProperty("NumSimulations"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TRandomDefaultLM(
                valueObject,
                Factors,
                RecoveyRates,
                Ttraits,
                NumSimulations,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlTRandomRRMCLossModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        std::vector<double> Ttraits =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Ttraits"), "Ttraits");

        double ModelA =
            ObjectHandler::convert2<double>(valueObject->getProperty("ModelA"));

        long NumSimulations =
            ObjectHandler::convert2<long>(valueObject->getProperty("NumSimulations"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ModelALib = ModelA;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TRandomLossLM(
                valueObject,
                Factors,
                RecoveyRates,
                Ttraits,
                ModelALib,
                NumSimulations,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlTSaddlePointLossmodel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        std::vector<double> RecoveyRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RecoveyRates"), "RecoveyRates");

        std::vector<double> Ttraits =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Ttraits"), "Ttraits");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TSaddlePointLossModel(
                valueObject,
                Factors,
                RecoveyRates,
                Ttraits,
                Permanent));
        return object;
    }

}
