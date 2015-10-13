
/*  
 Copyright (C) 2005, 2006 Plamen Neykov
 Copyright (C) 2007 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.vo.includes.body

#include <oh/ohdefines.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/valueobjects/vo_defaultbasket.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCreditBasket::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "IssuerNames",
        "Issuers",
        "Notionals",
        "ReferenceDate",
        "AttachmentRatio",
        "DettachmentRatio",
        "Amortizing",
        "Permanent"
    };

    std::set<std::string> qlCreditBasket::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCreditBasket::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCreditBasket::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCreditBasket::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ISSUERNAMES")==0)
            return IssuerNames_;
        else if(strcmp(nameUpper.c_str(), "ISSUERS")==0)
            return Issuers_;
        else if(strcmp(nameUpper.c_str(), "NOTIONALS")==0)
            return Notionals_;
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            return ReferenceDate_;
        else if(strcmp(nameUpper.c_str(), "ATTACHMENTRATIO")==0)
            return AttachmentRatio_;
        else if(strcmp(nameUpper.c_str(), "DETTACHMENTRATIO")==0)
            return DettachmentRatio_;
        else if(strcmp(nameUpper.c_str(), "AMORTIZING")==0)
            return Amortizing_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCreditBasket::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ISSUERNAMES")==0)
            IssuerNames_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "ISSUERS")==0)
            Issuers_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NOTIONALS")==0)
            Notionals_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            ReferenceDate_ = value;
        else if(strcmp(nameUpper.c_str(), "ATTACHMENTRATIO")==0)
            AttachmentRatio_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DETTACHMENTRATIO")==0)
            DettachmentRatio_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "AMORTIZING")==0)
            Amortizing_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCreditBasket::qlCreditBasket(
            const std::string& ObjectId,
            const std::vector<std::string>& IssuerNames,
            const std::vector<std::string>& Issuers,
            const std::vector<double>& Notionals,
            const ObjectHandler::property_t& ReferenceDate,
            double AttachmentRatio,
            double DettachmentRatio,
            bool Amortizing,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCreditBasket", Permanent),
        IssuerNames_(IssuerNames),
        Issuers_(Issuers),
        Notionals_(Notionals),
        ReferenceDate_(ReferenceDate),
        AttachmentRatio_(AttachmentRatio),
        DettachmentRatio_(DettachmentRatio),
        Amortizing_(Amortizing),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = Issuers.begin();
                    i != Issuers.end(); ++i)
                processPrecedentID(*i);
            
    }

 } }
