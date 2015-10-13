
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
#include <qlo/serialization/register/serialization_pricingengines.hpp>
#include <qlo/valueobjects/vo_pricingengines.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>


namespace QuantLibAddin {

    void register_pricingengines(boost::archive::xml_oarchive &ar) {
    
        // class ID 171 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlAnalyticCapFloorEngine>();
        // class ID 172 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBinomialPricingEngine>();
        // class ID 173 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator>();
        // class ID 174 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator2>();
        // class ID 175 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine>();
        // class ID 176 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine2>();
        // class ID 177 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator>();
        // class ID 178 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator2>();
        // class ID 179 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine>();
        // class ID 180 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine2>();
        // class ID 181 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBondEngine>();
        // class ID 182 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlDiscountingSwapEngine>();
        // class ID 183 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPricingEngine>();

    }
    
    void register_pricingengines(boost::archive::xml_iarchive &ar) {
    
        // class ID 171 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlAnalyticCapFloorEngine>();
        // class ID 172 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBinomialPricingEngine>();
        // class ID 173 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator>();
        // class ID 174 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCalculator2>();
        // class ID 175 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine>();
        // class ID 176 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackCapFloorEngine2>();
        // class ID 177 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator>();
        // class ID 178 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackScholesCalculator2>();
        // class ID 179 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine>();
        // class ID 180 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBlackSwaptionEngine2>();
        // class ID 181 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlBondEngine>();
        // class ID 182 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlDiscountingSwapEngine>();
        // class ID 183 in the boost serialization framework
        ar.register_type<QuantLibAddin::ValueObjects::qlPricingEngine>();

    }
    
}

