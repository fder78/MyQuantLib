
/*  
 Copyright (C) 2010 Roland Lichters
 
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
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/credit.hpp>
#include <qlo/creditdefaultswap.hpp>
#include <qlo/cdsoption.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/exercise.hpp>
#include <ql/termstructures/credit/defaultprobabilityhelpers.hpp>
#include <ql/pricingengines/credit/midpointcdsengine.hpp>
#include <ql/experimental/credit/basket.hpp>
#include <ql/experimental/credit/cdsoption.hpp>
#include <qlo/valueobjects/vo_credit.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlBaseCorrelationTermStructure(
            const std::string &ObjectId,
            const std::string &InterpolatorType,
            const long &SettlementDays,
            const std::string &Calendar,
            const std::string &Convention,
            const std::vector<ObjectHandler::property_t>& Tenors,
            const std::vector<double>& LossLevel,
            const std::vector<std::vector <ObjectHandler::property_t> >& Correlations,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        std::vector<QuantLib::Period> TenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(Tenors, "Tenors");

        std::vector<QuantLib::Real> LossLevelLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(LossLevel);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > CorrelationsLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Correlations, "Correlations");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBaseCorrelationTermStructure(
                ObjectId,
                InterpolatorType,
                SettlementDays,
                Calendar,
                Convention,
                Tenors,
                LossLevel,
                Correlations,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BaseCorrelationTermStructure(
                valueObject,
                InterpolatorType,
                SettlementDaysLib,
                CalendarEnum,
                ConventionEnum,
                TenorsLib,
                LossLevelLib,
                CorrelationsLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBaseCorrelationTermStructure : " << e.what());
        }
    }


    std::string qlBlackCdsOptionEngine(
            const std::string &ObjectId,
            const std::string &DefaultCurve,
            const double &RecoveryRate,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &BlackVol,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(DefaultCurveCoerce, DefaultCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> DefaultCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::DefaultProbabilityTermStructure,
                QuantLib::DefaultProbabilityTermStructure>()(
                    DefaultCurveCoerce);

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        QuantLib::Handle<QuantLib::Quote> BlackVolLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                BlackVol, "BlackVol");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCdsOptionEngine(
                ObjectId,
                DefaultCurve,
                RecoveryRate,
                YieldCurve,
                BlackVol,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCdsOptionEngine(
                valueObject,
                DefaultCurveLibObj,
                RecoveryRate,
                YieldCurveLibObj,
                BlackVolLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackCdsOptionEngine : " << e.what());
        }
    }


    std::string qlDefaultEvent(
            const std::string &ObjectId,
            const ObjectHandler::property_t &EventType,
            const ObjectHandler::property_t &EventDate,
            const ObjectHandler::property_t &Currency,
            const ObjectHandler::property_t &Seniority,
            const ObjectHandler::property_t &SettlementDate,
            const ObjectHandler::property_t &SettledRecovery,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string EventTypeCpp = ObjectHandler::convert2<std::string>(
            EventType, "EventType", "NONE");

        std::string CurrencyCpp = ObjectHandler::convert2<std::string>(
            Currency, "Currency", "Currency");

        std::string SeniorityCpp = ObjectHandler::convert2<std::string>(
            Seniority, "Seniority", "NoSeniority");

        double SettledRecoveryCpp = ObjectHandler::convert2<double>(
            SettledRecovery, "SettledRecovery", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date EventDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EventDate, "EventDate", QuantLib::Date());

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            SettlementDate, "SettlementDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(CurrencyCpp);

        QuantLib::Seniority SeniorityEnum =
            ObjectHandler::Create<QuantLib::Seniority>()(SeniorityCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDefaultEvent(
                ObjectId,
                EventTypeCpp,
                EventDate,
                CurrencyCpp,
                SeniorityCpp,
                SettlementDate,
                SettledRecoveryCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DefaultEventSet(
                valueObject,
                EventTypeCpp,
                EventDateLib,
                CurrencyEnum,
                SeniorityEnum,
                SettlementDateLib,
                SettledRecoveryCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlDefaultEvent : " << e.what());
        }
    }


    std::string qlHazardRateCurve(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveRates,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlHazardRateCurve(
                ObjectId,
                CurveDates,
                CurveRates,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HazardRateCurve(
                valueObject,
                CurveDatesLib,
                CurveRates,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlHazardRateCurve : " << e.what());
        }
    }


    std::string qlIntegralNtdEngine(
            const std::string &ObjectId,
            const std::string &IntegrationStep,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period IntegrationStepLib;
        QuantLibAddin::cppToLibrary(IntegrationStep, IntegrationStepLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIntegralNtdEngine(
                ObjectId,
                IntegrationStep,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IntegralNtdEngine(
                valueObject,
                IntegrationStepLib,
                YieldCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlIntegralNtdEngine : " << e.what());
        }
    }


    std::string qlIssuer(
            const std::string &ObjectId,
            const ObjectHandler::property_t &DefaultCurves,
            const std::string &DefaultEvents,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DefaultCurvesCpp = ObjectHandler::convert2<std::string>(
            DefaultCurves, "DefaultCurves", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(DefaultCurvesLibObjPtr, DefaultCurvesCpp,
            QuantLibAddin::DefaultProbabilityTermStructure, QuantLib::DefaultProbabilityTermStructure)

        OH_GET_REFERENCE(DefaultEventsLibObjPtr, DefaultEvents,
            QuantLibAddin::DefaultEventSet, QuantLib::DefaultEventSet)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIssuer(
                ObjectId,
                DefaultCurvesCpp,
                DefaultEvents,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Issuer(
                valueObject,
                DefaultCurvesLibObjPtr,
                DefaultEventsLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlIssuer : " << e.what());
        }
    }


    std::string qlMidPointCDOEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMidPointCDOEngine(
                ObjectId,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MidPointCDOEngine(
                valueObject,
                YieldCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMidPointCDOEngine : " << e.what());
        }
    }


    std::string qlMidPointCdsEngine(
            const std::string &ObjectId,
            const std::string &DefaultCurve,
            const double &RecoveryRate,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(DefaultCurveCoerce, DefaultCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> DefaultCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::DefaultProbabilityTermStructure,
                QuantLib::DefaultProbabilityTermStructure>()(
                    DefaultCurveCoerce);

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMidPointCdsEngine(
                ObjectId,
                DefaultCurve,
                RecoveryRate,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MidPointCdsEngine(
                valueObject,
                DefaultCurveLibObj,
                RecoveryRate,
                YieldCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMidPointCdsEngine : " << e.what());
        }
    }


    std::string qlNthToDefault(
            const std::string &ObjectId,
            const std::string &Basket,
            const long &Order,
            const ObjectHandler::property_t &BuyerSeller,
            const std::string &PremiumSchedule,
            const double &Upfront,
            const double &Spread,
            const std::string &DayCounter,
            const double &Notional,
            const bool &SettlesAccrual,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string BuyerSellerCpp = ObjectHandler::convert2<std::string>(
            BuyerSeller, "BuyerSeller", "Buyer");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size OrderLib;
        QuantLibAddin::cppToLibrary(Order, OrderLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Protection::Side BuyerSellerEnum =
            ObjectHandler::Create<QuantLib::Protection::Side>()(BuyerSellerCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        OH_GET_REFERENCE(PremiumScheduleLibObjPtr, PremiumSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlNthToDefault(
                ObjectId,
                Basket,
                Order,
                BuyerSellerCpp,
                PremiumSchedule,
                Upfront,
                Spread,
                DayCounter,
                Notional,
                SettlesAccrual,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::NthToDefault(
                valueObject,
                BasketLibObjPtr,
                OrderLib,
                BuyerSellerEnum,
                PremiumScheduleLibObjPtr,
                Upfront,
                Spread,
                DayCounterEnum,
                Notional,
                SettlesAccrual,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlNthToDefault : " << e.what());
        }
    }


    std::string qlPiecewiseFlatForwardCurve(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ReferenceDate,
            const std::vector<std::string>& RateHelpers,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        double AccuracyCpp = ObjectHandler::convert2<double>(
            Accuracy, "Accuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ReferenceDate, "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            Accuracy, "Accuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::RateHelper> > RateHelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::RateHelper, QuantLib::RateHelper>(RateHelpers);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseFlatForwardCurve(
                ObjectId,
                ReferenceDate,
                RateHelpers,
                DayCounterCpp,
                AccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseFlatForwardCurve(
                valueObject,
                ReferenceDateLib,
                RateHelpersLibObjPtr,
                DayCounterEnum,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlPiecewiseFlatForwardCurve : " << e.what());
        }
    }


    std::string qlPiecewiseHazardRateCurve(
            const std::string &ObjectId,
            const std::vector<std::string>& Helpers,
            const ObjectHandler::property_t &DayCounter,
            const std::string &Calendar,
            const std::string &Interpolation,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        double AccuracyCpp = ObjectHandler::convert2<double>(
            Accuracy, "Accuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            Accuracy, "Accuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> > HelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::DefaultProbabilityHelper, QuantLib::DefaultProbabilityHelper>(Helpers);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPiecewiseHazardRateCurve(
                ObjectId,
                Helpers,
                DayCounterCpp,
                Calendar,
                Interpolation,
                AccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseHazardRateCurve(
                valueObject,
                HelpersLibObjPtr,
                DayCounterEnum,
                CalendarEnum,
                Interpolation,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlPiecewiseHazardRateCurve : " << e.what());
        }
    }


    std::string qlRiskyFixedBond(
            const std::string &ObjectId,
            const std::string &Bondname,
            const std::string &Currency,
            const double &Recovery,
            const std::string &DefaultCurve,
            const std::string &Schedule,
            const double &Rate,
            const std::string &DayCounter,
            const ObjectHandler::property_t &PaymentConvention,
            const double &Notional,
            const std::string &DiscountingCurve,
            const ObjectHandler::property_t &PricingDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PaymentConventionCpp = ObjectHandler::convert2<std::string>(
            PaymentConvention, "PaymentConvention", "Following");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date PricingDateLib = ObjectHandler::convert2<QuantLib::Date>(
            PricingDate, "PricingDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConventionCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(DefaultCurveCoerce, DefaultCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::DefaultProbabilityTermStructure> DefaultCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::DefaultProbabilityTermStructure,
                QuantLib::DefaultProbabilityTermStructure>()(
                    DefaultCurveCoerce);

        OH_GET_REFERENCE(ScheduleLibObjPtr, Schedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        OH_GET_OBJECT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRiskyFixedBond(
                ObjectId,
                Bondname,
                Currency,
                Recovery,
                DefaultCurve,
                Schedule,
                Rate,
                DayCounter,
                PaymentConventionCpp,
                Notional,
                DiscountingCurve,
                PricingDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RiskyFixedBond(
                valueObject,
                Bondname,
                CurrencyEnum,
                Recovery,
                DefaultCurveLibObj,
                ScheduleLibObjPtr,
                Rate,
                DayCounterEnum,
                PaymentConventionEnum,
                Notional,
                DiscountingCurveLibObj,
                PricingDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRiskyFixedBond : " << e.what());
        }
    }


    std::string qlSpreadCdsHelper(
            const std::string &ObjectId,
            const ObjectHandler::property_t &RunningSpread,
            const std::string &Tenor,
            const ObjectHandler::property_t &SettlementDays,
            const std::string &Calendar,
            const std::string &Frequency,
            const std::string &PaymentConvention,
            const std::string &GenRule,
            const std::string &DayCounter,
            const double &RecoveryRate,
            const std::string &DiscountingCurve,
            const ObjectHandler::property_t &SettleAccrual,
            const ObjectHandler::property_t &PayAtDefault,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long SettlementDaysCpp = ObjectHandler::convert2<long>(
            SettlementDays, "SettlementDays", 0);

        bool SettleAccrualCpp = ObjectHandler::convert2<bool>(
            SettleAccrual, "SettleAccrual", true);

        bool PayAtDefaultCpp = ObjectHandler::convert2<bool>(
            PayAtDefault, "PayAtDefault", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural SettlementDaysLib = ObjectHandler::convert2<long>(
            SettlementDays, "SettlementDays", 0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(Frequency);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

        QuantLib::DateGeneration::Rule GenRuleEnum =
            ObjectHandler::Create<QuantLib::DateGeneration::Rule>()(GenRule);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RunningSpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                RunningSpread, "RunningSpread");

        OH_GET_OBJECT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSpreadCdsHelper(
                ObjectId,
                RunningSpread,
                Tenor,
                SettlementDaysCpp,
                Calendar,
                Frequency,
                PaymentConvention,
                GenRule,
                DayCounter,
                RecoveryRate,
                DiscountingCurve,
                SettleAccrualCpp,
                PayAtDefaultCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadCdsHelper(
                valueObject,
                RunningSpreadLibObj,
                TenorLib,
                SettlementDaysLib,
                CalendarEnum,
                FrequencyEnum,
                PaymentConventionEnum,
                GenRuleEnum,
                DayCounterEnum,
                RecoveryRate,
                DiscountingCurveLibObj,
                SettleAccrualCpp,
                PayAtDefaultCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSpreadCdsHelper : " << e.what());
        }
    }


    std::string qlSyntheticCDO(
            const std::string &ObjectId,
            const std::string &Basket,
            const ObjectHandler::property_t &BuyerSeller,
            const std::string &PremiumSchedule,
            const double &Upfront,
            const double &Spread,
            const std::string &DayCounter,
            const ObjectHandler::property_t &PaymentConvention,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string BuyerSellerCpp = ObjectHandler::convert2<std::string>(
            BuyerSeller, "BuyerSeller", "Buyer");

        std::string PaymentConventionCpp = ObjectHandler::convert2<std::string>(
            PaymentConvention, "PaymentConvention", "Following");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Protection::Side BuyerSellerEnum =
            ObjectHandler::Create<QuantLib::Protection::Side>()(BuyerSellerCpp);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConventionCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        OH_GET_REFERENCE(PremiumScheduleLibObjPtr, PremiumSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSyntheticCDO(
                ObjectId,
                Basket,
                BuyerSellerCpp,
                PremiumSchedule,
                Upfront,
                Spread,
                DayCounter,
                PaymentConventionCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SyntheticCDO(
                valueObject,
                BasketLibObjPtr,
                BuyerSellerEnum,
                PremiumScheduleLibObjPtr,
                Upfront,
                Spread,
                DayCounterEnum,
                PaymentConventionEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite, valueObject);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSyntheticCDO : " << e.what());
        }
    }

}

