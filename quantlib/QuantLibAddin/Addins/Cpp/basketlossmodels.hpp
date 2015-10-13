
/*  
 Copyright (C) 2014 Jose Aparicio
 
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
//      gensrc/gensrc/stubs/stub.cpp.header

#ifndef qlcpp_basketlossmodels_hpp
#define qlcpp_basketlossmodels_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlBaseCorrelationLossModel(
            const std::string &ObjectId,
            const std::string &BaseModel,
            const std::string &BaseCorrelationSurface,
            const std::vector<double>& Recoveries,
            const std::vector<double>& InitiTraits,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlGMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlGRandomRRMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const double &ModelA,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlTMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlTRandomRRMCLossModel(
            const std::string &ObjectId,
            const std::vector<std::vector<double> >& Factors,
            const std::vector<double>& RecoveyRates,
            const std::vector<double>& Ttraits,
            const double &ModelA,
            const long &NumSimulations,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

