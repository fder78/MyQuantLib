
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
//      gensrc/gensrc/stubs/stub.serialization.body

#include <oh/ohdefines.hpp>
#include <qlo/serialization/register/serialization_credit.hpp>
#include <qlo/valueobjects/vo_credit.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>


namespace QuantLibAddin {

    void register_credit(boost::archive::xml_oarchive &ar) {
    
        // class ID 69 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBaseCorrelationTermStructure>();
        // class ID 70 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCdsOptionEngine>();
        // class ID 71 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlCDSOption>();
        // class ID 72 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlCreditDefaultSwap>();
        // class ID 73 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlDefaultEvent>();
        // class ID 74 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlHazardRateCurve>();
        // class ID 75 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlIntegralNtdEngine>();
        // class ID 76 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlIssuer>();
        // class ID 77 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlMidPointCDOEngine>();
        // class ID 78 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlMidPointCdsEngine>();
        // class ID 79 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlNthToDefault>();
        // class ID 80 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPiecewiseFlatForwardCurve>();
        // class ID 81 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPiecewiseHazardRateCurve>();
        // class ID 82 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlRiskyFixedBond>();
        // class ID 83 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlSpreadCdsHelper>();
        // class ID 84 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlSyntheticCDO>();
        // class ID 85 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlUpfrontCdsHelper>();

    }
    
    void register_credit(boost::archive::xml_iarchive &ar) {
    
        // class ID 69 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBaseCorrelationTermStructure>();
        // class ID 70 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCdsOptionEngine>();
        // class ID 71 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlCDSOption>();
        // class ID 72 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlCreditDefaultSwap>();
        // class ID 73 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlDefaultEvent>();
        // class ID 74 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlHazardRateCurve>();
        // class ID 75 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlIntegralNtdEngine>();
        // class ID 76 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlIssuer>();
        // class ID 77 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlMidPointCDOEngine>();
        // class ID 78 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlMidPointCdsEngine>();
        // class ID 79 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlNthToDefault>();
        // class ID 80 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPiecewiseFlatForwardCurve>();
        // class ID 81 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPiecewiseHazardRateCurve>();
        // class ID 82 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlRiskyFixedBond>();
        // class ID 83 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlSpreadCdsHelper>();
        // class ID 84 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlSyntheticCDO>();
        // class ID 85 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlUpfrontCdsHelper>();

    }
    
}

