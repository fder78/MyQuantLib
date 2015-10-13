
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

#include <qlo/serialization/create/create_credit.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/credit.hpp>
#include <qlo/creditdefaultswap.hpp>
#include <qlo/cdsoption.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/schedule.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/defaultbasket.hpp>
#include <qlo/exercise.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/defaulttermstructure.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/experimental/credit/basket.hpp>
#include <ql/experimental/credit/cdsoption.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlBaseCorrelationTermStructure(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string InterpolatorType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InterpolatorType"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Convention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Convention"));

        std::vector<ObjectHandler::property_t> Tenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Tenors"), "Tenors");

        std::vector<double> LossLevel =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("LossLevel"), "LossLevel");

        std::vector<std::vector<ObjectHandler::property_t> > Correlations =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("Correlations"), "Correlations");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

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
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > CorrelationsLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Correlations, "Correlations");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Correlations);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BaseCorrelationTermStructure(
                valueObject,
                InterpolatorType,
                SettlementDays,
                CalendarEnum,
                ConventionEnum,
                TenorsLib,
                LossLevelLib,
                CorrelationsLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackCdsOptionEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string DefaultCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DefaultCurve"));

        double RecoveryRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RecoveryRate"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        ObjectHandler::property_t BlackVol =
            valueObject->getProperty("BlackVol");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real RecoveryRateLib = RecoveryRate;

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(DefaultCurve);
        valueObject->processPrecedentID(YieldCurve);
        valueObject->processVariant(BlackVol);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCdsOptionEngine(
                valueObject,
                DefaultCurveLibObj,
                RecoveryRateLib,
                YieldCurveLibObj,
                BlackVolLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCDSOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string UnderlyingCDS =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("UnderlyingCDS"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(UnderlyingCDSLibObjPtr, UnderlyingCDS,
            QuantLibAddin::CreditDefaultSwap, QuantLib::CreditDefaultSwap)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(UnderlyingCDS);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CdsOption(
                valueObject,
                UnderlyingCDSLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCreditDefaultSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BuyerSeller =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BuyerSeller"));

        double Notional =
            ObjectHandler::convert2<double>(valueObject->getProperty("Notional"));

        double Upfront =
            ObjectHandler::convert2<double>(valueObject->getProperty("Upfront"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string PremiumSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PremiumSchedule"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool SettlesAccrual =
            ObjectHandler::convert2<bool>(valueObject->getProperty("SettlesAccrual"));

        bool PayAtDefault =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayAtDefault"));

        ObjectHandler::property_t ProtectionStart =
            valueObject->getProperty("ProtectionStart");

        ObjectHandler::property_t UpfrontDate =
            valueObject->getProperty("UpfrontDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real NotionalLib = Notional;

        QuantLib::Date ProtectionStartLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ProtectionStart"), "ProtectionStart", QuantLib::Date());

        QuantLib::Date UpfrontDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("UpfrontDate"), "UpfrontDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Protection::Side BuyerSellerEnum =
            ObjectHandler::Create<QuantLib::Protection::Side>()(BuyerSeller);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PremiumScheduleLibObjPtr, PremiumSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(PremiumSchedule);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CreditDefaultSwap(
                valueObject,
                BuyerSellerEnum,
                NotionalLib,
                Upfront,
                Spread,
                PremiumScheduleLibObjPtr,
                PaymentConventionEnum,
                DayCounterEnum,
                SettlesAccrual,
                PayAtDefault,
                ProtectionStartLib,
                UpfrontDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDefaultEvent(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string EventType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EventType"));

        ObjectHandler::property_t EventDate =
            valueObject->getProperty("EventDate");

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        std::string Seniority =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Seniority"));

        ObjectHandler::property_t SettlementDate =
            valueObject->getProperty("SettlementDate");

        double SettledRecovery =
            ObjectHandler::convert2<double>(valueObject->getProperty("SettledRecovery"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date EventDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EventDate"), "EventDate", QuantLib::Date());

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("SettlementDate"), "SettlementDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Seniority SeniorityEnum =
            ObjectHandler::Create<QuantLib::Seniority>()(Seniority);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DefaultEventSet(
                valueObject,
                EventType,
                EventDateLib,
                CurrencyEnum,
                SeniorityEnum,
                SettlementDateLib,
                SettledRecovery,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlHazardRateCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> CurveDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("CurveDates"), "CurveDates");

        std::vector<double> CurveRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CurveRates"), "CurveRates");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> CurveDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(CurveDates, "CurveDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HazardRateCurve(
                valueObject,
                CurveDatesLib,
                CurveRates,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlIntegralNtdEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string IntegrationStep =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IntegrationStep"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IntegralNtdEngine(
                valueObject,
                IntegrationStepLib,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlIssuer(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string DefaultCurves =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DefaultCurves"));

        std::string DefaultEvents =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DefaultEvents"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(DefaultCurvesLibObjPtr, DefaultCurves,
            QuantLibAddin::DefaultProbabilityTermStructure, QuantLib::DefaultProbabilityTermStructure)

        OH_GET_REFERENCE(DefaultEventsLibObjPtr, DefaultEvents,
            QuantLibAddin::DefaultEventSet, QuantLib::DefaultEventSet)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(DefaultCurves);
        valueObject->processPrecedentID(DefaultEvents);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Issuer(
                valueObject,
                DefaultCurvesLibObjPtr,
                DefaultEventsLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMidPointCDOEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MidPointCDOEngine(
                valueObject,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMidPointCdsEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string DefaultCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DefaultCurve"));

        double RecoveryRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RecoveryRate"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real RecoveryRateLib = RecoveryRate;

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(DefaultCurve);
        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MidPointCdsEngine(
                valueObject,
                DefaultCurveLibObj,
                RecoveryRateLib,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlNthToDefault(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Basket =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Basket"));

        long Order =
            ObjectHandler::convert2<long>(valueObject->getProperty("Order"));

        std::string BuyerSeller =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BuyerSeller"));

        std::string PremiumSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PremiumSchedule"));

        double Upfront =
            ObjectHandler::convert2<double>(valueObject->getProperty("Upfront"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        double Notional =
            ObjectHandler::convert2<double>(valueObject->getProperty("Notional"));

        bool SettlesAccrual =
            ObjectHandler::convert2<bool>(valueObject->getProperty("SettlesAccrual"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real NotionalLib = Notional;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Protection::Side BuyerSellerEnum =
            ObjectHandler::Create<QuantLib::Protection::Side>()(BuyerSeller);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        OH_GET_REFERENCE(PremiumScheduleLibObjPtr, PremiumSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Basket);
        valueObject->processPrecedentID(PremiumSchedule);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::NthToDefault(
                valueObject,
                BasketLibObjPtr,
                Order,
                BuyerSellerEnum,
                PremiumScheduleLibObjPtr,
                Upfront,
                Spread,
                DayCounterEnum,
                NotionalLib,
                SettlesAccrual,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlPiecewiseFlatForwardCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t ReferenceDate =
            valueObject->getProperty("ReferenceDate");

        std::vector<std::string> RateHelpers =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("RateHelpers"), "RateHelpers");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date ReferenceDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ReferenceDate"), "ReferenceDate", QuantLib::Date());

        QuantLib::Real AccuracyLib = Accuracy;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::RateHelper> > RateHelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::RateHelper, QuantLib::RateHelper>(RateHelpers);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = RateHelpers.begin();
                i != RateHelpers.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseFlatForwardCurve(
                valueObject,
                ReferenceDateLib,
                RateHelpersLibObjPtr,
                DayCounterEnum,
                AccuracyLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlPiecewiseHazardRateCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::string> Helpers =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("Helpers"), "Helpers");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Interpolation =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Interpolation"));

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real AccuracyLib = Accuracy;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::DefaultProbabilityHelper> > HelpersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::DefaultProbabilityHelper, QuantLib::DefaultProbabilityHelper>(Helpers);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = Helpers.begin();
                i != Helpers.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PiecewiseHazardRateCurve(
                valueObject,
                HelpersLibObjPtr,
                DayCounterEnum,
                CalendarEnum,
                Interpolation,
                AccuracyLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRiskyFixedBond(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Bondname =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Bondname"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        double Recovery =
            ObjectHandler::convert2<double>(valueObject->getProperty("Recovery"));

        std::string DefaultCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DefaultCurve"));

        std::string Schedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Schedule"));

        double Rate =
            ObjectHandler::convert2<double>(valueObject->getProperty("Rate"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        double Notional =
            ObjectHandler::convert2<double>(valueObject->getProperty("Notional"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        ObjectHandler::property_t PricingDate =
            valueObject->getProperty("PricingDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date PricingDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("PricingDate"), "PricingDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(DefaultCurve);
        valueObject->processPrecedentID(Schedule);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

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
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSpreadCdsHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t RunningSpread =
            valueObject->getProperty("RunningSpread");

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Frequency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Frequency"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        std::string GenRule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("GenRule"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        double RecoveryRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RecoveryRate"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        bool SettleAccrual =
            ObjectHandler::convert2<bool>(valueObject->getProperty("SettleAccrual"));

        bool PayAtDefault =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayAtDefault"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Real RecoveryRateLib = RecoveryRate;

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

        // update value object precedent IDs (if any)

        valueObject->processVariant(RunningSpread);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadCdsHelper(
                valueObject,
                RunningSpreadLibObj,
                TenorLib,
                SettlementDays,
                CalendarEnum,
                FrequencyEnum,
                PaymentConventionEnum,
                GenRuleEnum,
                DayCounterEnum,
                RecoveryRateLib,
                DiscountingCurveLibObj,
                SettleAccrual,
                PayAtDefault,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSyntheticCDO(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Basket =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Basket"));

        std::string BuyerSeller =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BuyerSeller"));

        std::string PremiumSchedule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PremiumSchedule"));

        double Upfront =
            ObjectHandler::convert2<double>(valueObject->getProperty("Upfront"));

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Protection::Side BuyerSellerEnum =
            ObjectHandler::Create<QuantLib::Protection::Side>()(BuyerSeller);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentConvention);

        // convert object IDs into library objects

        OH_GET_REFERENCE(BasketLibObjPtr, Basket,
            QuantLibAddin::Basket, QuantLib::Basket)

        OH_GET_REFERENCE(PremiumScheduleLibObjPtr, PremiumSchedule,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Basket);
        valueObject->processPrecedentID(PremiumSchedule);

        // construct and return the object

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
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlUpfrontCdsHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t UpfrontSpread =
            valueObject->getProperty("UpfrontSpread");

        double RunningSpread =
            ObjectHandler::convert2<double>(valueObject->getProperty("RunningSpread"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Frequency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Frequency"));

        std::string PaymentConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentConvention"));

        std::string GenRule =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("GenRule"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        double RecRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("RecRate"));

        std::string DiscCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscCurve"));

        long UpfSettlDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("UpfSettlDays"));

        bool SettlAccr =
            ObjectHandler::convert2<bool>(valueObject->getProperty("SettlAccr"));

        bool PayAtDefault =
            ObjectHandler::convert2<bool>(valueObject->getProperty("PayAtDefault"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Real RecRateLib = RecRate;

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

        QuantLib::Handle<QuantLib::Quote> UpfrontSpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                UpfrontSpread, "UpfrontSpread");

        OH_GET_OBJECT(DiscCurveCoerce, DiscCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processVariant(UpfrontSpread);
        valueObject->processPrecedentID(DiscCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::UpfrontCdsHelper(
                valueObject,
                UpfrontSpreadLibObj,
                RunningSpread,
                TenorLib,
                SettlementDays,
                CalendarEnum,
                FrequencyEnum,
                PaymentConventionEnum,
                GenRuleEnum,
                DayCounterEnum,
                RecRateLib,
                DiscCurveLibObj,
                UpfSettlDays,
                SettlAccr,
                PayAtDefault,
                Permanent));
        return object;
    }

}
