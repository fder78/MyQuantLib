
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
#include <qlo/latentmodels.hpp>
#include <qlo/valueobjects/vo_latentmodels.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlGaussianDefaultProbLM::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Basket",
        "Factors",
        "Permanent"
    };

    std::set<std::string> qlGaussianDefaultProbLM::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGaussianDefaultProbLM::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGaussianDefaultProbLM::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGaussianDefaultProbLM::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            return Basket_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGaussianDefaultProbLM::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            Basket_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGaussianDefaultProbLM::qlGaussianDefaultProbLM(
            const std::string& ObjectId,
            const std::string& Basket,
            const std::vector<std::vector<double> >& Factors,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGaussianDefaultProbLM", Permanent),
        Basket_(Basket),
        Factors_(Factors),
        Permanent_(Permanent) {
                  
            processPrecedentID(Basket);
            
    }

    const char* qlTDefaultProbLM::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Torders",
        "Basket",
        "Factors",
        "Permanent"
    };

    std::set<std::string> qlTDefaultProbLM::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlTDefaultProbLM::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlTDefaultProbLM::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlTDefaultProbLM::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "TORDERS")==0)
            return Torders_;
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            return Basket_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlTDefaultProbLM::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TORDERS")==0)
            Torders_ = ObjectHandler::vector::convert2<long>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            Basket_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlTDefaultProbLM::qlTDefaultProbLM(
            const std::string& ObjectId,
            const std::vector<long>& Torders,
            const std::string& Basket,
            const std::vector<std::vector<double> >& Factors,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlTDefaultProbLM", Permanent),
        Torders_(Torders),
        Basket_(Basket),
        Factors_(Factors),
        Permanent_(Permanent) {
                  
            processPrecedentID(Basket);
            
    }

 } }
