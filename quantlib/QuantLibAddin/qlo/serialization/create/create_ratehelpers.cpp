
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

#include <qlo/serialization/create/create_ratehelpers.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/bonds.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlBondHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Price =
            valueObject->getProperty("Price");

        std::string Bond =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Bond"));

        bool UseCleanPrice =
            ObjectHandler::convert2<bool>(valueObject->getProperty("UseCleanPrice"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        OH_GET_REFERENCE(BondLibObjPtr, Bond,
            QuantLibAddin::Bond, QuantLib::Bond)

        // update value object precedent IDs (if any)

        valueObject->processVariant(Price);
        valueObject->processPrecedentID(Bond);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BondHelper(
                valueObject,
                PriceLibObj,
                BondLibObjPtr,
                UseCleanPrice,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDatedOISRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t EndDate =
            valueObject->getProperty("EndDate");

        ObjectHandler::property_t FixedRate =
            valueObject->getProperty("FixedRate");

        std::string ONIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ONIndex"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EndDate"), "EndDate");

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> FixedRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                FixedRate, "FixedRate");

        OH_GET_REFERENCE(ONIndexLibObjPtr, ONIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processVariant(FixedRate);
        valueObject->processPrecedentID(ONIndex);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DatedOISRateHelper(
                valueObject,
                StartDateLib,
                EndDateLib,
                FixedRateLibObj,
                ONIndexLibObjPtr,
                DiscountingCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDepositRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Rate =
            valueObject->getProperty("Rate");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);
        valueObject->processPrecedentID(IborIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DepositRateHelper(
                valueObject,
                RateLibObj,
                IborIndexLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDepositRateHelper2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Rate =
            valueObject->getProperty("Rate");

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Convention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Convention"));

        bool EndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("EndOfMonth"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DepositRateHelper(
                valueObject,
                RateLibObj,
                TenorLib,
                FixingDays,
                CalendarEnum,
                ConventionEnum,
                EndOfMonth,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFixedRateBondHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Price =
            valueObject->getProperty("Price");

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        double FaceAmount =
            ObjectHandler::convert2<double>(valueObject->getProperty("FaceAmount"));

        std::string ScheduleID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ScheduleID"));

        std::vector<double> Coupons =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Coupons"), "Coupons");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string PaymentBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentBDC"));

        double Redemption =
            ObjectHandler::convert2<double>(valueObject->getProperty("Redemption"));

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        std::string PaymentCalendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PaymentCalendar"));

        std::string ExCouponPeriod =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ExCouponPeriod"));

        std::string ExCouponCalendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ExCouponCalendar"));

        std::string ExCouponBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ExCouponBDC"));

        bool ExCouponEndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("ExCouponEndOfMonth"));

        bool UseCleanPrice =
            ObjectHandler::convert2<bool>(valueObject->getProperty("UseCleanPrice"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        QuantLib::Period ExCouponPeriodLib;
        QuantLibAddin::cppToLibrary(ExCouponPeriod, ExCouponPeriodLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::BusinessDayConvention PaymentBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(PaymentBDC);

        QuantLib::Calendar PaymentCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(PaymentCalendar);

        QuantLib::Calendar ExCouponCalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(ExCouponCalendar);

        QuantLib::BusinessDayConvention ExCouponBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(ExCouponBDC);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        OH_GET_REFERENCE(ScheduleIDLibObjPtr, ScheduleID,
            QuantLibAddin::Schedule, QuantLib::Schedule)

        // update value object precedent IDs (if any)

        valueObject->processVariant(Price);
        valueObject->processPrecedentID(ScheduleID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FixedRateBondHelper(
                valueObject,
                PriceLibObj,
                SettlementDays,
                FaceAmount,
                ScheduleIDLibObjPtr,
                Coupons,
                DayCounterEnum,
                PaymentBDCEnum,
                Redemption,
                IssueDateLib,
                PaymentCalendarEnum,
                ExCouponPeriodLib,
                ExCouponCalendarEnum,
                ExCouponBDCEnum,
                ExCouponEndOfMonth,
                UseCleanPrice,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFraRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Rate =
            valueObject->getProperty("Rate");

        std::string PeriodToStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PeriodToStart"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period PeriodToStartLib;
        QuantLibAddin::cppToLibrary(PeriodToStart, PeriodToStartLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);
        valueObject->processPrecedentID(IborIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FraRateHelper(
                valueObject,
                RateLibObj,
                PeriodToStartLib,
                IborIndexLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFraRateHelper2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Rate =
            valueObject->getProperty("Rate");

        std::string PeriodToStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PeriodToStart"));

        long LengthInMonths =
            ObjectHandler::convert2<long>(valueObject->getProperty("LengthInMonths"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Convention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Convention"));

        bool EndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("EndOfMonth"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period PeriodToStartLib;
        QuantLibAddin::cppToLibrary(PeriodToStart, PeriodToStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FraRateHelper(
                valueObject,
                RateLibObj,
                PeriodToStartLib,
                LengthInMonths,
                FixingDays,
                CalendarEnum,
                ConventionEnum,
                EndOfMonth,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFuturesRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Price =
            valueObject->getProperty("Price");

        std::string FuturesType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FuturesType"));

        ObjectHandler::property_t FuturesDate =
            valueObject->getProperty("FuturesDate");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        ObjectHandler::property_t ConvexityAdjQuote =
            valueObject->getProperty("ConvexityAdjQuote");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FuturesDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("FuturesDate"), "FuturesDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Futures::Type FuturesTypeEnum =
            ObjectHandler::Create<QuantLib::Futures::Type>()(FuturesType);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        OH_GET_REFERENCE_DEFAULT(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ConvexityAdjQuote, "ConvexityAdjQuote");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Price);
        valueObject->processPrecedentID(IborIndex);
        valueObject->processVariant(ConvexityAdjQuote);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                FuturesTypeEnum,
                FuturesDateLib,
                IborIndexLibObjPtr,
                ConvexityAdjQuoteLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFuturesRateHelper2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Price =
            valueObject->getProperty("Price");

        std::string FuturesType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FuturesType"));

        ObjectHandler::property_t FuturesDate =
            valueObject->getProperty("FuturesDate");

        long LengthInMonths =
            ObjectHandler::convert2<long>(valueObject->getProperty("LengthInMonths"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Convention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Convention"));

        bool EndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("EndOfMonth"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t ConvexityAdjQuote =
            valueObject->getProperty("ConvexityAdjQuote");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FuturesDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("FuturesDate"), "FuturesDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Futures::Type FuturesTypeEnum =
            ObjectHandler::Create<QuantLib::Futures::Type>()(FuturesType);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ConvexityAdjQuote, "ConvexityAdjQuote");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Price);
        valueObject->processVariant(ConvexityAdjQuote);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                FuturesTypeEnum,
                FuturesDateLib,
                LengthInMonths,
                CalendarEnum,
                ConventionEnum,
                EndOfMonth,
                DayCounterEnum,
                ConvexityAdjQuoteLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFuturesRateHelper3(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Price =
            valueObject->getProperty("Price");

        std::string FuturesType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FuturesType"));

        ObjectHandler::property_t FuturesDate =
            valueObject->getProperty("FuturesDate");

        ObjectHandler::property_t EndDate =
            valueObject->getProperty("EndDate");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t ConvexityAdjQuote =
            valueObject->getProperty("ConvexityAdjQuote");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FuturesDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("FuturesDate"), "FuturesDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EndDate"), "EndDate", QuantLib::Date());

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Futures::Type FuturesTypeEnum =
            ObjectHandler::Create<QuantLib::Futures::Type>()(FuturesType);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> PriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Price, "Price");

        QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ConvexityAdjQuote, "ConvexityAdjQuote");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Price);
        valueObject->processVariant(ConvexityAdjQuote);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesRateHelper(
                valueObject,
                PriceLibObj,
                FuturesTypeEnum,
                FuturesDateLib,
                EndDateLib,
                DayCounterEnum,
                ConvexityAdjQuoteLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFxSwapRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t FwdPoint =
            valueObject->getProperty("FwdPoint");

        ObjectHandler::property_t SpotFx =
            valueObject->getProperty("SpotFx");

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string Convention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Convention"));

        bool EndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("EndOfMonth"));

        bool IsFxBaseCurrencyCollateralCurrency =
            ObjectHandler::convert2<bool>(valueObject->getProperty("IsFxBaseCurrencyCollateralCurrency"));

        std::string CollateralCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CollateralCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> FwdPointLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                FwdPoint, "FwdPoint");

        QuantLib::Handle<QuantLib::Quote> SpotFxLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                SpotFx, "SpotFx");

        OH_GET_OBJECT(CollateralCurveCoerce, CollateralCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> CollateralCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    CollateralCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processVariant(FwdPoint);
        valueObject->processVariant(SpotFx);
        valueObject->processPrecedentID(CollateralCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FxSwapRateHelper(
                valueObject,
                FwdPointLibObj,
                SpotFxLibObj,
                TenorLib,
                FixingDays,
                CalendarEnum,
                ConventionEnum,
                EndOfMonth,
                IsFxBaseCurrencyCollateralCurrency,
                CollateralCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlOISRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long SettlDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlDays"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        ObjectHandler::property_t FixedRate =
            valueObject->getProperty("FixedRate");

        std::string ONIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ONIndex"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> FixedRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                FixedRate, "FixedRate");

        OH_GET_REFERENCE(ONIndexLibObjPtr, ONIndex,
            QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processVariant(FixedRate);
        valueObject->processPrecedentID(ONIndex);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OISRateHelper(
                valueObject,
                SettlDays,
                TenorLib,
                FixedRateLibObj,
                ONIndexLibObjPtr,
                DiscountingCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwapRateHelper(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Rate =
            valueObject->getProperty("Rate");

        std::string SwapIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndex"));

        ObjectHandler::property_t Spread =
            valueObject->getProperty("Spread");

        std::string ForwardStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardStart"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);
        valueObject->processPrecedentID(SwapIndex);
        valueObject->processVariant(Spread);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapRateHelper(
                valueObject,
                RateLibObj,
                SwapIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                DiscountingCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwapRateHelper2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Rate =
            valueObject->getProperty("Rate");

        long SettlDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlDays"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string FixedLegFrequency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixedLegFrequency"));

        std::string FixedLegConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixedLegConvention"));

        std::string FixedLegDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixedLegDayCounter"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        ObjectHandler::property_t Spread =
            valueObject->getProperty("Spread");

        std::string ForwardStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardStart"));

        std::string DiscountingCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscountingCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::Frequency FixedLegFrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FixedLegFrequency);

        QuantLib::BusinessDayConvention FixedLegConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(FixedLegConvention);

        QuantLib::DayCounter FixedLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixedLegDayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> RateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Rate, "Rate");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        OH_GET_OBJECT_DEFAULT(DiscountingCurveCoerce, DiscountingCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscountingCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processVariant(Rate);
        valueObject->processPrecedentID(IborIndex);
        valueObject->processVariant(Spread);
        valueObject->processPrecedentID(DiscountingCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapRateHelper(
                valueObject,
                RateLibObj,
                SettlDays,
                TenorLib,
                CalendarEnum,
                FixedLegFrequencyEnum,
                FixedLegConventionEnum,
                FixedLegDayCounterEnum,
                IborIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                DiscountingCurveLibObj,
                Permanent));
        return object;
    }

}
