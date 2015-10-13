
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
#include <qlo/credit.hpp>
#include <qlo/valueobjects/vo_credit.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlBaseCorrelationTermStructure::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "InterpolatorType",
        "SettlementDays",
        "Calendar",
        "Convention",
        "Tenors",
        "LossLevel",
        "Correlations",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlBaseCorrelationTermStructure::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBaseCorrelationTermStructure::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBaseCorrelationTermStructure::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBaseCorrelationTermStructure::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORTYPE")==0)
            return InterpolatorType_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            return Convention_;
        else if(strcmp(nameUpper.c_str(), "TENORS")==0)
            return Tenors_;
        else if(strcmp(nameUpper.c_str(), "LOSSLEVEL")==0)
            return LossLevel_;
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            return Correlations_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBaseCorrelationTermStructure::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERPOLATORTYPE")==0)
            InterpolatorType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            Convention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TENORS")==0)
            Tenors_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "LOSSLEVEL")==0)
            LossLevel_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CORRELATIONS")==0)
            Correlations_ = ObjectHandler::matrix::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBaseCorrelationTermStructure::qlBaseCorrelationTermStructure(
            const std::string& ObjectId,
            const std::string& InterpolatorType,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& Convention,
            const std::vector<ObjectHandler::property_t>& Tenors,
            const std::vector<double>& LossLevel,
            const std::vector<std::vector<ObjectHandler::property_t> >& Correlations,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBaseCorrelationTermStructure", Permanent),
        InterpolatorType_(InterpolatorType),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        Convention_(Convention),
        Tenors_(Tenors),
        LossLevel_(LossLevel),
        Correlations_(Correlations),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  
            processVariant(Correlations);
            
    }

    const char* qlBlackCdsOptionEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "DefaultCurve",
        "RecoveryRate",
        "YieldCurve",
        "BlackVol",
        "Permanent"
    };

    std::set<std::string> qlBlackCdsOptionEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlBlackCdsOptionEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlBlackCdsOptionEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlBlackCdsOptionEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            return DefaultCurve_;
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            return RecoveryRate_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "BLACKVOL")==0)
            return BlackVol_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlBlackCdsOptionEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            DefaultCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            RecoveryRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BLACKVOL")==0)
            BlackVol_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlBlackCdsOptionEngine::qlBlackCdsOptionEngine(
            const std::string& ObjectId,
            const std::string& DefaultCurve,
            double RecoveryRate,
            const std::string& YieldCurve,
            const ObjectHandler::property_t& BlackVol,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlBlackCdsOptionEngine", Permanent),
        DefaultCurve_(DefaultCurve),
        RecoveryRate_(RecoveryRate),
        YieldCurve_(YieldCurve),
        BlackVol_(BlackVol),
        Permanent_(Permanent) {
                  
            processPrecedentID(DefaultCurve);
            processPrecedentID(YieldCurve);
            processVariant(BlackVol);
            
    }

    const char* qlCDSOption::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "UnderlyingCDS",
        "Exercise",
        "Permanent"
    };

    std::set<std::string> qlCDSOption::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCDSOption::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCDSOption::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCDSOption::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "UNDERLYINGCDS")==0)
            return UnderlyingCDS_;
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            return Exercise_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCDSOption::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UNDERLYINGCDS")==0)
            UnderlyingCDS_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EXERCISE")==0)
            Exercise_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCDSOption::qlCDSOption(
            const std::string& ObjectId,
            const std::string& UnderlyingCDS,
            const std::string& Exercise,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCDSOption", Permanent),
        UnderlyingCDS_(UnderlyingCDS),
        Exercise_(Exercise),
        Permanent_(Permanent) {
                  
            processPrecedentID(UnderlyingCDS);
            processPrecedentID(Exercise);
            
    }

    const char* qlCreditDefaultSwap::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "BuyerSeller",
        "Notional",
        "Upfront",
        "Spread",
        "PremiumSchedule",
        "PaymentConvention",
        "DayCounter",
        "SettlesAccrual",
        "PayAtDefault",
        "ProtectionStart",
        "UpfrontDate",
        "Permanent"
    };

    std::set<std::string> qlCreditDefaultSwap::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCreditDefaultSwap::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCreditDefaultSwap::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCreditDefaultSwap::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            return BuyerSeller_;
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            return Notional_;
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            return Upfront_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            return PremiumSchedule_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "SETTLESACCRUAL")==0)
            return SettlesAccrual_;
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            return PayAtDefault_;
        else if(strcmp(nameUpper.c_str(), "PROTECTIONSTART")==0)
            return ProtectionStart_;
        else if(strcmp(nameUpper.c_str(), "UPFRONTDATE")==0)
            return UpfrontDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCreditDefaultSwap::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            BuyerSeller_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            Notional_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            Upfront_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            PremiumSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLESACCRUAL")==0)
            SettlesAccrual_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            PayAtDefault_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PROTECTIONSTART")==0)
            ProtectionStart_ = value;
        else if(strcmp(nameUpper.c_str(), "UPFRONTDATE")==0)
            UpfrontDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCreditDefaultSwap::qlCreditDefaultSwap(
            const std::string& ObjectId,
            const std::string& BuyerSeller,
            double Notional,
            double Upfront,
            double Spread,
            const std::string& PremiumSchedule,
            const std::string& PaymentConvention,
            const std::string& DayCounter,
            bool SettlesAccrual,
            bool PayAtDefault,
            const ObjectHandler::property_t& ProtectionStart,
            const ObjectHandler::property_t& UpfrontDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCreditDefaultSwap", Permanent),
        BuyerSeller_(BuyerSeller),
        Notional_(Notional),
        Upfront_(Upfront),
        Spread_(Spread),
        PremiumSchedule_(PremiumSchedule),
        PaymentConvention_(PaymentConvention),
        DayCounter_(DayCounter),
        SettlesAccrual_(SettlesAccrual),
        PayAtDefault_(PayAtDefault),
        ProtectionStart_(ProtectionStart),
        UpfrontDate_(UpfrontDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(PremiumSchedule);
            
    }

    const char* qlDefaultEvent::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "EventType",
        "EventDate",
        "Currency",
        "Seniority",
        "SettlementDate",
        "SettledRecovery",
        "Permanent"
    };

    std::set<std::string> qlDefaultEvent::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlDefaultEvent::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlDefaultEvent::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlDefaultEvent::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EVENTTYPE")==0)
            return EventType_;
        else if(strcmp(nameUpper.c_str(), "EVENTDATE")==0)
            return EventDate_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "SENIORITY")==0)
            return Seniority_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            return SettlementDate_;
        else if(strcmp(nameUpper.c_str(), "SETTLEDRECOVERY")==0)
            return SettledRecovery_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlDefaultEvent::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EVENTTYPE")==0)
            EventType_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EVENTDATE")==0)
            EventDate_ = value;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SENIORITY")==0)
            Seniority_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDATE")==0)
            SettlementDate_ = value;
        else if(strcmp(nameUpper.c_str(), "SETTLEDRECOVERY")==0)
            SettledRecovery_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlDefaultEvent::qlDefaultEvent(
            const std::string& ObjectId,
            const std::string& EventType,
            const ObjectHandler::property_t& EventDate,
            const std::string& Currency,
            const std::string& Seniority,
            const ObjectHandler::property_t& SettlementDate,
            double SettledRecovery,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlDefaultEvent", Permanent),
        EventType_(EventType),
        EventDate_(EventDate),
        Currency_(Currency),
        Seniority_(Seniority),
        SettlementDate_(SettlementDate),
        SettledRecovery_(SettledRecovery),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlHazardRateCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "CurveDates",
        "CurveRates",
        "DayCounter",
        "Permanent"
    };

    std::set<std::string> qlHazardRateCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlHazardRateCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlHazardRateCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlHazardRateCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            return CurveDates_;
        else if(strcmp(nameUpper.c_str(), "CURVERATES")==0)
            return CurveRates_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlHazardRateCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURVEDATES")==0)
            CurveDates_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "CURVERATES")==0)
            CurveRates_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlHazardRateCurve::qlHazardRateCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveRates,
            const std::string& DayCounter,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlHazardRateCurve", Permanent),
        CurveDates_(CurveDates),
        CurveRates_(CurveRates),
        DayCounter_(DayCounter),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlIntegralNtdEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "IntegrationStep",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlIntegralNtdEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlIntegralNtdEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlIntegralNtdEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlIntegralNtdEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "INTEGRATIONSTEP")==0)
            return IntegrationStep_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlIntegralNtdEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTEGRATIONSTEP")==0)
            IntegrationStep_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlIntegralNtdEngine::qlIntegralNtdEngine(
            const std::string& ObjectId,
            const std::string& IntegrationStep,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlIntegralNtdEngine", Permanent),
        IntegrationStep_(IntegrationStep),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlIssuer::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "DefaultCurves",
        "DefaultEvents",
        "Permanent"
    };

    std::set<std::string> qlIssuer::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlIssuer::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlIssuer::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlIssuer::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVES")==0)
            return DefaultCurves_;
        else if(strcmp(nameUpper.c_str(), "DEFAULTEVENTS")==0)
            return DefaultEvents_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlIssuer::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVES")==0)
            DefaultCurves_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DEFAULTEVENTS")==0)
            DefaultEvents_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlIssuer::qlIssuer(
            const std::string& ObjectId,
            const std::string& DefaultCurves,
            const std::string& DefaultEvents,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlIssuer", Permanent),
        DefaultCurves_(DefaultCurves),
        DefaultEvents_(DefaultEvents),
        Permanent_(Permanent) {
                  
            processPrecedentID(DefaultCurves);
            processPrecedentID(DefaultEvents);
            
    }

    const char* qlMidPointCDOEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlMidPointCDOEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMidPointCDOEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMidPointCDOEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMidPointCDOEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMidPointCDOEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMidPointCDOEngine::qlMidPointCDOEngine(
            const std::string& ObjectId,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMidPointCDOEngine", Permanent),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(YieldCurve);
            
    }

    const char* qlMidPointCdsEngine::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "DefaultCurve",
        "RecoveryRate",
        "YieldCurve",
        "Permanent"
    };

    std::set<std::string> qlMidPointCdsEngine::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlMidPointCdsEngine::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlMidPointCdsEngine::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlMidPointCdsEngine::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            return DefaultCurve_;
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            return RecoveryRate_;
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            return YieldCurve_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlMidPointCdsEngine::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            DefaultCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            RecoveryRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "YIELDCURVE")==0)
            YieldCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlMidPointCdsEngine::qlMidPointCdsEngine(
            const std::string& ObjectId,
            const std::string& DefaultCurve,
            double RecoveryRate,
            const std::string& YieldCurve,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlMidPointCdsEngine", Permanent),
        DefaultCurve_(DefaultCurve),
        RecoveryRate_(RecoveryRate),
        YieldCurve_(YieldCurve),
        Permanent_(Permanent) {
                  
            processPrecedentID(DefaultCurve);
            processPrecedentID(YieldCurve);
            
    }

    const char* qlNthToDefault::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Basket",
        "Order",
        "BuyerSeller",
        "PremiumSchedule",
        "Upfront",
        "Spread",
        "DayCounter",
        "Notional",
        "SettlesAccrual",
        "Permanent"
    };

    std::set<std::string> qlNthToDefault::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlNthToDefault::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlNthToDefault::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlNthToDefault::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            return Basket_;
        else if(strcmp(nameUpper.c_str(), "ORDER")==0)
            return Order_;
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            return BuyerSeller_;
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            return PremiumSchedule_;
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            return Upfront_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            return Notional_;
        else if(strcmp(nameUpper.c_str(), "SETTLESACCRUAL")==0)
            return SettlesAccrual_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlNthToDefault::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            Basket_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ORDER")==0)
            Order_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            BuyerSeller_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            PremiumSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            Upfront_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            Notional_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLESACCRUAL")==0)
            SettlesAccrual_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlNthToDefault::qlNthToDefault(
            const std::string& ObjectId,
            const std::string& Basket,
            long Order,
            const std::string& BuyerSeller,
            const std::string& PremiumSchedule,
            double Upfront,
            double Spread,
            const std::string& DayCounter,
            double Notional,
            bool SettlesAccrual,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlNthToDefault", Permanent),
        Basket_(Basket),
        Order_(Order),
        BuyerSeller_(BuyerSeller),
        PremiumSchedule_(PremiumSchedule),
        Upfront_(Upfront),
        Spread_(Spread),
        DayCounter_(DayCounter),
        Notional_(Notional),
        SettlesAccrual_(SettlesAccrual),
        Permanent_(Permanent) {
                  
            processPrecedentID(Basket);
            processPrecedentID(PremiumSchedule);
            
    }

    const char* qlPiecewiseFlatForwardCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "ReferenceDate",
        "RateHelpers",
        "DayCounter",
        "Accuracy",
        "Permanent"
    };

    std::set<std::string> qlPiecewiseFlatForwardCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPiecewiseFlatForwardCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPiecewiseFlatForwardCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPiecewiseFlatForwardCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            return ReferenceDate_;
        else if(strcmp(nameUpper.c_str(), "RATEHELPERS")==0)
            return RateHelpers_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPiecewiseFlatForwardCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "REFERENCEDATE")==0)
            ReferenceDate_ = value;
        else if(strcmp(nameUpper.c_str(), "RATEHELPERS")==0)
            RateHelpers_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPiecewiseFlatForwardCurve::qlPiecewiseFlatForwardCurve(
            const std::string& ObjectId,
            const ObjectHandler::property_t& ReferenceDate,
            const std::vector<std::string>& RateHelpers,
            const std::string& DayCounter,
            double Accuracy,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPiecewiseFlatForwardCurve", Permanent),
        ReferenceDate_(ReferenceDate),
        RateHelpers_(RateHelpers),
        DayCounter_(DayCounter),
        Accuracy_(Accuracy),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = RateHelpers.begin();
                    i != RateHelpers.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlPiecewiseHazardRateCurve::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Helpers",
        "DayCounter",
        "Calendar",
        "Interpolation",
        "Accuracy",
        "Permanent"
    };

    std::set<std::string> qlPiecewiseHazardRateCurve::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlPiecewiseHazardRateCurve::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlPiecewiseHazardRateCurve::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlPiecewiseHazardRateCurve::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "HELPERS")==0)
            return Helpers_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "INTERPOLATION")==0)
            return Interpolation_;
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            return Accuracy_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlPiecewiseHazardRateCurve::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "HELPERS")==0)
            Helpers_ = ObjectHandler::vector::convert2<std::string>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "INTERPOLATION")==0)
            Interpolation_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ACCURACY")==0)
            Accuracy_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlPiecewiseHazardRateCurve::qlPiecewiseHazardRateCurve(
            const std::string& ObjectId,
            const std::vector<std::string>& Helpers,
            const std::string& DayCounter,
            const std::string& Calendar,
            const std::string& Interpolation,
            double Accuracy,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlPiecewiseHazardRateCurve", Permanent),
        Helpers_(Helpers),
        DayCounter_(DayCounter),
        Calendar_(Calendar),
        Interpolation_(Interpolation),
        Accuracy_(Accuracy),
        Permanent_(Permanent) {
                  
            for (std::vector<std::string>::const_iterator i = Helpers.begin();
                    i != Helpers.end(); ++i)
                processPrecedentID(*i);
            
    }

    const char* qlRiskyFixedBond::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Bondname",
        "Currency",
        "Recovery",
        "DefaultCurve",
        "Schedule",
        "Rate",
        "DayCounter",
        "PaymentConvention",
        "Notional",
        "DiscountingCurve",
        "PricingDate",
        "Permanent"
    };

    std::set<std::string> qlRiskyFixedBond::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlRiskyFixedBond::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlRiskyFixedBond::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlRiskyFixedBond::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BONDNAME")==0)
            return Bondname_;
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            return Currency_;
        else if(strcmp(nameUpper.c_str(), "RECOVERY")==0)
            return Recovery_;
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            return DefaultCurve_;
        else if(strcmp(nameUpper.c_str(), "SCHEDULE")==0)
            return Schedule_;
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            return Rate_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            return Notional_;
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            return DiscountingCurve_;
        else if(strcmp(nameUpper.c_str(), "PRICINGDATE")==0)
            return PricingDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlRiskyFixedBond::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BONDNAME")==0)
            Bondname_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CURRENCY")==0)
            Currency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERY")==0)
            Recovery_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DEFAULTCURVE")==0)
            DefaultCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SCHEDULE")==0)
            Schedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RATE")==0)
            Rate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "NOTIONAL")==0)
            Notional_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            DiscountingCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PRICINGDATE")==0)
            PricingDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlRiskyFixedBond::qlRiskyFixedBond(
            const std::string& ObjectId,
            const std::string& Bondname,
            const std::string& Currency,
            double Recovery,
            const std::string& DefaultCurve,
            const std::string& Schedule,
            double Rate,
            const std::string& DayCounter,
            const std::string& PaymentConvention,
            double Notional,
            const std::string& DiscountingCurve,
            const ObjectHandler::property_t& PricingDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlRiskyFixedBond", Permanent),
        Bondname_(Bondname),
        Currency_(Currency),
        Recovery_(Recovery),
        DefaultCurve_(DefaultCurve),
        Schedule_(Schedule),
        Rate_(Rate),
        DayCounter_(DayCounter),
        PaymentConvention_(PaymentConvention),
        Notional_(Notional),
        DiscountingCurve_(DiscountingCurve),
        PricingDate_(PricingDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(DefaultCurve);
            processPrecedentID(Schedule);
            processPrecedentID(DiscountingCurve);
            
    }

    const char* qlSpreadCdsHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "RunningSpread",
        "Tenor",
        "SettlementDays",
        "Calendar",
        "Frequency",
        "PaymentConvention",
        "GenRule",
        "DayCounter",
        "RecoveryRate",
        "DiscountingCurve",
        "SettleAccrual",
        "PayAtDefault",
        "Permanent"
    };

    std::set<std::string> qlSpreadCdsHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSpreadCdsHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSpreadCdsHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSpreadCdsHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            return RunningSpread_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            return Frequency_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            return GenRule_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            return RecoveryRate_;
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            return DiscountingCurve_;
        else if(strcmp(nameUpper.c_str(), "SETTLEACCRUAL")==0)
            return SettleAccrual_;
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            return PayAtDefault_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSpreadCdsHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            RunningSpread_ = value;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            Frequency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            GenRule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECOVERYRATE")==0)
            RecoveryRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DISCOUNTINGCURVE")==0)
            DiscountingCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEACCRUAL")==0)
            SettleAccrual_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            PayAtDefault_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSpreadCdsHelper::qlSpreadCdsHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& RunningSpread,
            const std::string& Tenor,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& Frequency,
            const std::string& PaymentConvention,
            const std::string& GenRule,
            const std::string& DayCounter,
            double RecoveryRate,
            const std::string& DiscountingCurve,
            bool SettleAccrual,
            bool PayAtDefault,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSpreadCdsHelper", Permanent),
        RunningSpread_(RunningSpread),
        Tenor_(Tenor),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        Frequency_(Frequency),
        PaymentConvention_(PaymentConvention),
        GenRule_(GenRule),
        DayCounter_(DayCounter),
        RecoveryRate_(RecoveryRate),
        DiscountingCurve_(DiscountingCurve),
        SettleAccrual_(SettleAccrual),
        PayAtDefault_(PayAtDefault),
        Permanent_(Permanent) {
                  
            processVariant(RunningSpread);
            processPrecedentID(DiscountingCurve);
            
    }

    const char* qlSyntheticCDO::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Basket",
        "BuyerSeller",
        "PremiumSchedule",
        "Upfront",
        "Spread",
        "DayCounter",
        "PaymentConvention",
        "Permanent"
    };

    std::set<std::string> qlSyntheticCDO::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSyntheticCDO::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSyntheticCDO::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSyntheticCDO::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            return Basket_;
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            return BuyerSeller_;
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            return PremiumSchedule_;
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            return Upfront_;
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            return Spread_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSyntheticCDO::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BASKET")==0)
            Basket_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "BUYERSELLER")==0)
            BuyerSeller_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PREMIUMSCHEDULE")==0)
            PremiumSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UPFRONT")==0)
            Upfront_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "SPREAD")==0)
            Spread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSyntheticCDO::qlSyntheticCDO(
            const std::string& ObjectId,
            const std::string& Basket,
            const std::string& BuyerSeller,
            const std::string& PremiumSchedule,
            double Upfront,
            double Spread,
            const std::string& DayCounter,
            const std::string& PaymentConvention,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSyntheticCDO", Permanent),
        Basket_(Basket),
        BuyerSeller_(BuyerSeller),
        PremiumSchedule_(PremiumSchedule),
        Upfront_(Upfront),
        Spread_(Spread),
        DayCounter_(DayCounter),
        PaymentConvention_(PaymentConvention),
        Permanent_(Permanent) {
                  
            processPrecedentID(Basket);
            processPrecedentID(PremiumSchedule);
            
    }

    const char* qlUpfrontCdsHelper::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "UpfrontSpread",
        "RunningSpread",
        "Tenor",
        "SettlementDays",
        "Calendar",
        "Frequency",
        "PaymentConvention",
        "GenRule",
        "DayCounter",
        "RecRate",
        "DiscCurve",
        "UpfSettlDays",
        "SettlAccr",
        "PayAtDefault",
        "Permanent"
    };

    std::set<std::string> qlUpfrontCdsHelper::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlUpfrontCdsHelper::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlUpfrontCdsHelper::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlUpfrontCdsHelper::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "UPFRONTSPREAD")==0)
            return UpfrontSpread_;
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            return RunningSpread_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            return SettlementDays_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            return Frequency_;
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            return PaymentConvention_;
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            return GenRule_;
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            return DayCounter_;
        else if(strcmp(nameUpper.c_str(), "RECRATE")==0)
            return RecRate_;
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            return DiscCurve_;
        else if(strcmp(nameUpper.c_str(), "UPFSETTLDAYS")==0)
            return UpfSettlDays_;
        else if(strcmp(nameUpper.c_str(), "SETTLACCR")==0)
            return SettlAccr_;
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            return PayAtDefault_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlUpfrontCdsHelper::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UPFRONTSPREAD")==0)
            UpfrontSpread_ = value;
        else if(strcmp(nameUpper.c_str(), "RUNNINGSPREAD")==0)
            RunningSpread_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLEMENTDAYS")==0)
            SettlementDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "FREQUENCY")==0)
            Frequency_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PAYMENTCONVENTION")==0)
            PaymentConvention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            GenRule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "DAYCOUNTER")==0)
            DayCounter_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "RECRATE")==0)
            RecRate_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "DISCCURVE")==0)
            DiscCurve_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "UPFSETTLDAYS")==0)
            UpfSettlDays_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "SETTLACCR")==0)
            SettlAccr_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PAYATDEFAULT")==0)
            PayAtDefault_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlUpfrontCdsHelper::qlUpfrontCdsHelper(
            const std::string& ObjectId,
            const ObjectHandler::property_t& UpfrontSpread,
            double RunningSpread,
            const std::string& Tenor,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& Frequency,
            const std::string& PaymentConvention,
            const std::string& GenRule,
            const std::string& DayCounter,
            double RecRate,
            const std::string& DiscCurve,
            long UpfSettlDays,
            bool SettlAccr,
            bool PayAtDefault,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlUpfrontCdsHelper", Permanent),
        UpfrontSpread_(UpfrontSpread),
        RunningSpread_(RunningSpread),
        Tenor_(Tenor),
        SettlementDays_(SettlementDays),
        Calendar_(Calendar),
        Frequency_(Frequency),
        PaymentConvention_(PaymentConvention),
        GenRule_(GenRule),
        DayCounter_(DayCounter),
        RecRate_(RecRate),
        DiscCurve_(DiscCurve),
        UpfSettlDays_(UpfSettlDays),
        SettlAccr_(SettlAccr),
        PayAtDefault_(PayAtDefault),
        Permanent_(Permanent) {
                  
            processVariant(UpfrontSpread);
            processPrecedentID(DiscCurve);
            
    }

 } }
