
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
//      gensrc/gensrc/stubs/stub.vo.includes.decl

#ifndef qlo_vo_basketlossmodels_hpp
#define qlo_vo_basketlossmodels_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlBaseCorrelationLossModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBaseCorrelationLossModel() {}
        qlBaseCorrelationLossModel(
            const std::string& ObjectId,
            const std::string& BaseModel,
            const std::string& BaseCorrelationSurface,
            const std::vector<double>& Recoveries,
            const std::vector<double>& InitiTraits,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string BaseModel_;
        std::string BaseCorrelationSurface_;
        std::vector<double> Recoveries_;
        std::vector<double> InitiTraits_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBaseCorrelationLossModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BaseModel", BaseModel_)
                & boost::serialization::make_nvp("BaseCorrelationSurface", BaseCorrelationSurface_)
                & boost::serialization::make_nvp("Recoveries", Recoveries_)
                & boost::serialization::make_nvp("InitiTraits", InitiTraits_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlGBinomialLossmodel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlGBinomialLossmodel() {}
        qlGBinomialLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlGBinomialLossmodel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlGMCLossModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlGMCLossModel() {}
        qlGMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            long NumSimulations,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        long NumSimulations_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlGMCLossModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("NumSimulations", NumSimulations_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlGRandomRRMCLossModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlGRandomRRMCLossModel() {}
        qlGRandomRRMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            double ModelA,
            long NumSimulations,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        double ModelA_;
        long NumSimulations_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlGRandomRRMCLossModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("ModelA", ModelA_)
                & boost::serialization::make_nvp("NumSimulations", NumSimulations_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlGRecursiveLossmodel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlGRecursiveLossmodel() {}
        qlGRecursiveLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlGRecursiveLossmodel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlGSaddlePointLossmodel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlGSaddlePointLossmodel() {}
        qlGSaddlePointLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlGSaddlePointLossmodel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlGaussianLHPLossmodel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlGaussianLHPLossmodel() {}
        qlGaussianLHPLossmodel(
            const std::string& ObjectId,
            double Correlation,
            const std::vector<double>& RecoveyRates,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Correlation_;
        std::vector<double> RecoveyRates_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlGaussianLHPLossmodel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Correlation", Correlation_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlIHGaussPoolLossModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlIHGaussPoolLossModel() {}
        qlIHGaussPoolLossModel(
            const std::string& ObjectId,
            double Correlation,
            const std::vector<double>& RecoveyRates,
            long NumBuckets,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Correlation_;
        std::vector<double> RecoveyRates_;
        long NumBuckets_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlIHGaussPoolLossModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Correlation", Correlation_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("NumBuckets", NumBuckets_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlIHStudentPoolLossModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlIHStudentPoolLossModel() {}
        qlIHStudentPoolLossModel(
            const std::string& ObjectId,
            double Correlation,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            long NumBuckets,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        double Correlation_;
        std::vector<double> RecoveyRates_;
        std::vector<double> Ttraits_;
        long NumBuckets_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlIHStudentPoolLossModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Correlation", Correlation_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Ttraits", Ttraits_)
                & boost::serialization::make_nvp("NumBuckets", NumBuckets_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlTBinomialLossmodel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlTBinomialLossmodel() {}
        qlTBinomialLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        std::vector<double> Ttraits_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlTBinomialLossmodel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Ttraits", Ttraits_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlTMCLossModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlTMCLossModel() {}
        qlTMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            long NumSimulations,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        std::vector<double> Ttraits_;
        long NumSimulations_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlTMCLossModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Ttraits", Ttraits_)
                & boost::serialization::make_nvp("NumSimulations", NumSimulations_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlTRandomRRMCLossModel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlTRandomRRMCLossModel() {}
        qlTRandomRRMCLossModel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            double ModelA,
            long NumSimulations,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        std::vector<double> Ttraits_;
        double ModelA_;
        long NumSimulations_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlTRandomRRMCLossModel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Ttraits", Ttraits_)
                & boost::serialization::make_nvp("ModelA", ModelA_)
                & boost::serialization::make_nvp("NumSimulations", NumSimulations_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlTSaddlePointLossmodel : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlTSaddlePointLossmodel() {}
        qlTSaddlePointLossmodel(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Factors_;
        std::vector<double> RecoveyRates_;
        std::vector<double> Ttraits_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlTSaddlePointLossmodel, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Factors", Factors_)
                & boost::serialization::make_nvp("RecoveyRates", RecoveyRates_)
                & boost::serialization::make_nvp("Ttraits", Ttraits_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

