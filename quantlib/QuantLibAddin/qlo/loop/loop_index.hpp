
/*  
 Copyright (C) 2006, 2007 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.loop.file


#include <boost/bind.hpp>

namespace QuantLibAddin {

    // qlIndexAddFixings2

    typedef     boost::_bi::bind_t<
                void,
                boost::_mfi::mf2<
                    void,
                    QuantLib::Index,
                    const QuantLib::TimeSeriesDef&,
                    bool>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::Index> >,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlIndexAddFixings2Bind;

    typedef     void 
                (QuantLib::Index::* qlIndexAddFixings2Signature)(
                    const QuantLib::TimeSeriesDef&,
                    bool);

    // qlIndexFixing

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf2<
                    QuantLib::Real,
                    QuantLib::Index,
                    const QuantLib::Date&,
                    bool>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::Index> >,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlIndexFixingBind;

    typedef     QuantLib::Real 
                (QuantLib::Index::* qlIndexFixingSignature)(
                    const QuantLib::Date&,
                    bool) const;

    // qlIndexIsValidFixingDate

    typedef     boost::_bi::bind_t<
                bool,
                boost::_mfi::cmf1<
                    bool,
                    QuantLib::Index,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::Index> >,
                    boost::arg<1> > >
                qlIndexIsValidFixingDateBind;

    typedef     bool 
                (QuantLib::Index::* qlIndexIsValidFixingDateSignature)(
                    const QuantLib::Date&) const;

    // qlInterestRateIndexFixingDate

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                boost::_mfi::cmf1<
                    QuantLib::Date,
                    QuantLib::InterestRateIndex,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::InterestRateIndex> >,
                    boost::arg<1> > >
                qlInterestRateIndexFixingDateBind;

    typedef     QuantLib::Date 
                (QuantLib::InterestRateIndex::* qlInterestRateIndexFixingDateSignature)(
                    const QuantLib::Date&) const;

    // qlInterestRateIndexMaturity

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                boost::_mfi::cmf1<
                    QuantLib::Date,
                    QuantLib::InterestRateIndex,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::InterestRateIndex> >,
                    boost::arg<1> > >
                qlInterestRateIndexMaturityBind;

    typedef     QuantLib::Date 
                (QuantLib::InterestRateIndex::* qlInterestRateIndexMaturitySignature)(
                    const QuantLib::Date&) const;

    // qlInterestRateIndexValueDate

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                boost::_mfi::cmf1<
                    QuantLib::Date,
                    QuantLib::InterestRateIndex,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::InterestRateIndex> >,
                    boost::arg<1> > >
                qlInterestRateIndexValueDateBind;

    typedef     QuantLib::Date 
                (QuantLib::InterestRateIndex::* qlInterestRateIndexValueDateSignature)(
                    const QuantLib::Date&) const;

}

