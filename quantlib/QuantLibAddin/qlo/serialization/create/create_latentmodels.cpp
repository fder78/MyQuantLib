
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

#include <qlo/serialization/create/create_latentmodels.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <ql/experimental/credit/basket.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/credit.hpp>
#include <qlo/latentmodels.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlGaussianDefaultProbLM(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Basket =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Basket"));

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Basket);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GaussianDefProbLM(
                valueObject,
                BasketLibObjPtr,
                Factors,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlTDefaultProbLM(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<long> Torders =
            ObjectHandler::vector::convert2<long>(valueObject->getProperty("Torders"), "Torders");

        std::string Basket =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Basket"));

        std::vector<std::vector<double> > Factors =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Factors"), "Factors");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Integer> TordersLib = 
            QuantLibAddin::convertVector<long, QuantLib::Integer>(Torders);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Basket);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TDefProbLM(
                valueObject,
                TordersLib,
                BasketLibObjPtr,
                Factors,
                Permanent));
        return object;
    }

}
