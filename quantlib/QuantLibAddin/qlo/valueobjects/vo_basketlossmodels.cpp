
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
#include <qlo/basketlossmodels.hpp>
#include <qlo/valueobjects/vo_basketlossmodels.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlBaseCorrelationLossModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BaseModel",
        "BaseCorrelationSurface",
        "Recoveries",
        "InitiTraits",
        "Permanent"
    };

    std::set<std::string> qlBaseCorrelationLossModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBaseCorrelationLossModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBaseCorrelationLossModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBaseCorrelationLossModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BASEMODEL")==0)
            return BaseModel_;
        else if(strcmp(nameUpper.c_str(), "BASECORRELATIONSURFACE")==0)
            return BaseCorrelationSurface_;
        else if(strcmp(nameUpper.c_str(), "RECOVERIES")==0)
            return Recoveries_;
        else if(strcmp(nameUpper.c_str(), "INITITRAITS")==0)
            return InitiTraits_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBaseCorrelationLossModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASEMODEL")==0)
            BaseModel_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASECORRELATIONSURFACE")==0)
            BaseCorrelationSurface_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERIES")==0)
            Recoveries_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "INITITRAITS")==0)
            InitiTraits_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBaseCorrelationLossModel::qlBaseCorrelationLossModel(
            const std::string& ObjectId,
            const std::string& BaseModel,
            const std::string& BaseCorrelationSurface,
            const std::vector<double>& Recoveries,
            const std::vector<double>& InitiTraits,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBaseCorrelationLossModel", Permanent),
        BaseModel_(BaseModel),
        BaseCorrelationSurface_(BaseCorrelationSurface),
        Recoveries_(Recoveries),
        InitiTraits_(InitiTraits),
        Permanent_(Permanent) {
                  
            processPrecedentID(BaseCorrelationSurface);
            
    }

    const char* qlGBinomialLossmodel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "Permanent"
    };

    std::set<std::string> qlGBinomialLossmodel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGBinomialLossmodel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGBinomialLossmodel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGBinomialLossmodel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGBinomialLossmodel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGBinomialLossmodel::qlGBinomialLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGBinomialLossmodel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlGMCLossModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "NumSimulations",
        "Permanent"
    };

    std::set<std::string> qlGMCLossModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGMCLossModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGMCLossModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGMCLossModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            return NumSimulations_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGMCLossModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            NumSimulations_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGMCLossModel::qlGMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            long NumSimulations,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGMCLossModel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        NumSimulations_(NumSimulations),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlGRandomRRMCLossModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "ModelA",
        "NumSimulations",
        "Permanent"
    };

    std::set<std::string> qlGRandomRRMCLossModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGRandomRRMCLossModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGRandomRRMCLossModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGRandomRRMCLossModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "MODELA")==0)
            return ModelA_;
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            return NumSimulations_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGRandomRRMCLossModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "MODELA")==0)
            ModelA_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            NumSimulations_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGRandomRRMCLossModel::qlGRandomRRMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            double ModelA,
            long NumSimulations,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGRandomRRMCLossModel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        ModelA_(ModelA),
        NumSimulations_(NumSimulations),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlGRecursiveLossmodel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "Permanent"
    };

    std::set<std::string> qlGRecursiveLossmodel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGRecursiveLossmodel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGRecursiveLossmodel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGRecursiveLossmodel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGRecursiveLossmodel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGRecursiveLossmodel::qlGRecursiveLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGRecursiveLossmodel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlGSaddlePointLossmodel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "Permanent"
    };

    std::set<std::string> qlGSaddlePointLossmodel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGSaddlePointLossmodel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGSaddlePointLossmodel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGSaddlePointLossmodel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGSaddlePointLossmodel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGSaddlePointLossmodel::qlGSaddlePointLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGSaddlePointLossmodel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlGaussianLHPLossmodel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Correlation",
        "RecoveyRates",
        "Permanent"
    };

    std::set<std::string> qlGaussianLHPLossmodel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlGaussianLHPLossmodel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlGaussianLHPLossmodel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlGaussianLHPLossmodel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            return Correlation_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlGaussianLHPLossmodel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            Correlation_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlGaussianLHPLossmodel::qlGaussianLHPLossmodel(
            const std::string& ObjectId,
            double Correlation,
            const std::vector<double>& RecoveyRates,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlGaussianLHPLossmodel", Permanent),
        Correlation_(Correlation),
        RecoveyRates_(RecoveyRates),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlIHGaussPoolLossModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Correlation",
        "RecoveyRates",
        "NumBuckets",
        "Permanent"
    };

    std::set<std::string> qlIHGaussPoolLossModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlIHGaussPoolLossModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlIHGaussPoolLossModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlIHGaussPoolLossModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            return Correlation_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "NUMBUCKETS")==0)
            return NumBuckets_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlIHGaussPoolLossModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            Correlation_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMBUCKETS")==0)
            NumBuckets_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlIHGaussPoolLossModel::qlIHGaussPoolLossModel(
            const std::string& ObjectId,
            double Correlation,
            const std::vector<double>& RecoveyRates,
            long NumBuckets,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlIHGaussPoolLossModel", Permanent),
        Correlation_(Correlation),
        RecoveyRates_(RecoveyRates),
        NumBuckets_(NumBuckets),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlIHStudentPoolLossModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Correlation",
        "RecoveyRates",
        "Ttraits",
        "NumBuckets",
        "Permanent"
    };

    std::set<std::string> qlIHStudentPoolLossModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlIHStudentPoolLossModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlIHStudentPoolLossModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlIHStudentPoolLossModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            return Correlation_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            return Ttraits_;
        else if(strcmp(nameUpper.c_str(), "NUMBUCKETS")==0)
            return NumBuckets_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlIHStudentPoolLossModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CORRELATION")==0)
            Correlation_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            Ttraits_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMBUCKETS")==0)
            NumBuckets_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlIHStudentPoolLossModel::qlIHStudentPoolLossModel(
            const std::string& ObjectId,
            double Correlation,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            long NumBuckets,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlIHStudentPoolLossModel", Permanent),
        Correlation_(Correlation),
        RecoveyRates_(RecoveyRates),
        Ttraits_(Ttraits),
        NumBuckets_(NumBuckets),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlTBinomialLossmodel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "Ttraits",
        "Permanent"
    };

    std::set<std::string> qlTBinomialLossmodel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlTBinomialLossmodel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlTBinomialLossmodel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlTBinomialLossmodel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            return Ttraits_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlTBinomialLossmodel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            Ttraits_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlTBinomialLossmodel::qlTBinomialLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlTBinomialLossmodel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        Ttraits_(Ttraits),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlTMCLossModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "Ttraits",
        "NumSimulations",
        "Permanent"
    };

    std::set<std::string> qlTMCLossModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlTMCLossModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlTMCLossModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlTMCLossModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            return Ttraits_;
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            return NumSimulations_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlTMCLossModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            Ttraits_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            NumSimulations_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlTMCLossModel::qlTMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            long NumSimulations,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlTMCLossModel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        Ttraits_(Ttraits),
        NumSimulations_(NumSimulations),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlTRandomRRMCLossModel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "Ttraits",
        "ModelA",
        "NumSimulations",
        "Permanent"
    };

    std::set<std::string> qlTRandomRRMCLossModel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlTRandomRRMCLossModel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlTRandomRRMCLossModel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlTRandomRRMCLossModel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            return Ttraits_;
        else if(strcmp(nameUpper.c_str(), "MODELA")==0)
            return ModelA_;
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            return NumSimulations_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlTRandomRRMCLossModel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            Ttraits_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "MODELA")==0)
            ModelA_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "NUMSIMULATIONS")==0)
            NumSimulations_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlTRandomRRMCLossModel::qlTRandomRRMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            double ModelA,
            long NumSimulations,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlTRandomRRMCLossModel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        Ttraits_(Ttraits),
        ModelA_(ModelA),
        NumSimulations_(NumSimulations),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlTSaddlePointLossmodel::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Factors",
        "RecoveyRates",
        "Ttraits",
        "Permanent"
    };

    std::set<std::string> qlTSaddlePointLossmodel::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlTSaddlePointLossmodel::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlTSaddlePointLossmodel::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlTSaddlePointLossmodel::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            return Factors_;
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            return RecoveyRates_;
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            return Ttraits_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlTSaddlePointLossmodel::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FACTORS")==0)
            Factors_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "RECOVEYRATES")==0)
            RecoveyRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TTRAITS")==0)
            Ttraits_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlTSaddlePointLossmodel::qlTSaddlePointLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlTSaddlePointLossmodel", Permanent),
        Factors_(Factors),
        RecoveyRates_(RecoveyRates),
        Ttraits_(Ttraits),
        Permanent_(Permanent) {
                  

            
    }

 } }
