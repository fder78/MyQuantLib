
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

#include <qlo/serialization/create/create_defaultbasket.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <ql/experimental/credit/basket.hpp>
#include <qlo/credit.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/basketlossmodels.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCreditBasket(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::string> IssuerNames =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("IssuerNames"), "IssuerNames");

        std::vector<std::string> Issuers =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("Issuers"), "Issuers");

        std::vector<double> Notionals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Notionals"), "Notionals");

        ObjectHandler::property_t ReferenceDate =
            valueObject->getProperty("ReferenceDate");

        double AttachmentRatio =
            ObjectHandler::convert2<double>(valueObject->getProperty("AttachmentRatio"));

        double DettachmentRatio =
            ObjectHandler::convert2<double>(valueObject->getProperty("DettachmentRatio"));

        bool Amortizing =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Amortizing"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ReferenceDate"), "ReferenceDate", QuantLib::Date());

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::Issuer> > IssuersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::Issuer, QuantLib::Issuer>(Issuers);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = Issuers.begin();
                i != Issuers.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Basket(
                valueObject,
                IssuerNames,
                IssuersLibObjPtr,
                Notionals,
                ReferenceDateLib,
                AttachmentRatio,
                DettachmentRatio,
                Amortizing,
                Permanent));
        return object;
    }

}
