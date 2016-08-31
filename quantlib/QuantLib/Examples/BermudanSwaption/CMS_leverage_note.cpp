#include "CMS_leverage_note.h"

#include <ir_derivatives\g2_calibration.hpp>
#include <ir_derivatives\pricing_cms_spread_ra.hpp>



double cms_leverage_note(const char* fileName) {

	tinyxml2::XMLDocument doc;
	XMLError e = doc.LoadFile(fileName);

	XMLElement* element = doc.FirstChildElement("root")->FirstChildElement("param_root")->FirstChildElement("eval_time");
	const char* datestr = element->Attribute("value");

	//1. Evaluation Date
	Date evaluationDate = ConvertToDateFromBloomberg(::ToWString(datestr));
	Settings::instance().evaluationDate() = evaluationDate;
	Calendar calendar = SouthKorea();

	element = doc.FirstChildElement("root")->FirstChildElement("param_root")->FirstChildElement("data_root")->FirstChildElement("record");

	//2. notional
	double notional = XMLValue(element, "Notional").GetValue<double>();

	//3. swap type??????
	std::wstring payrec = XMLValue(element, "PayRec").GetValue<std::wstring>();
	VanillaSwap::Type type = VanillaSwap::Receiver;
	if (payrec == L"Pay")
		type = VanillaSwap::Payer;
	
	//4. coupon rate
	double cpnRate = XMLValue(element, "AccrualRate").GetValue<double>();
	std::wstring callput = XMLValue(element, "CallPut").GetValue<std::wstring>();

	//5. CMS Tenors
	Size tenorsInYears;
	std::vector<std::wstring> tenorStr;
	std::wstring tenorMat = XMLValue(element, "TenorMatrix").GetValue<std::wstring>();
	boost::algorithm::split(tenorStr, tenorMat, boost::is_any_of(L","), boost::algorithm::token_compress_on);
	tenorsInYears = boost::lexical_cast<Size>(tenorStr[0]);
	Real Rate0 = boost::lexical_cast<Real>(tenorStr[1]);


	//6. Range
	double lower = XMLValue(element, "Obs1LowerLevel").GetValue<double>();
	double upper = XMLValue(element, "Obs1UpperLevel").GetValue<double>();

	//7. FX Quanto
	double fxvol = XMLValue(element, "Obs1FXVol").GetValue<double>();
	double fxcorr = XMLValue(element, "Obs1FXCorr").GetValue<double>();

	//8. DayCounter
	DayCounter fixedLegDayCounter = Actual365Fixed();
	std::wstring dc = XMLValue(element, "DayCounterAccrual").GetValue<std::wstring>();
	if (dc == L"Actual365Fixed") fixedLegDayCounter = Actual365Fixed();
	else if (dc == L"Actual360") fixedLegDayCounter = Actual360();
	else if (dc == L"ActualActual") fixedLegDayCounter = ActualActual();
	else if (dc == L"30/360") fixedLegDayCounter = Thirty360();
	else throw(std::exception("undefined DayCounter"));

	//9. Schedule
	Date effectiveDate = XMLValue(element, "EffectiveDate").GetValue<Date>();
	Date terminationDate = XMLValue(element, "TerminationDate").GetValue<Date>();

	////10. Freq
	//Frequency fixedLegFrequency;
	//std::wstring tenor = XMLValue(element, "Tenor").GetValue<std::wstring>();
	//if (tenor == L"Annually") fixedLegFrequency = Annual;
	//else if (tenor == L"Quarterly") fixedLegFrequency = Quarterly;
	//else if (tenor == L"Semiannually") fixedLegFrequency = Semiannual;
	//else throw(std::exception("undefined frequency"));

	////11. BDC
	//BusinessDayConvention fixedLegConvention = Following;
	//std::wstring bdc = XMLValue(element, "BDC").GetValue<std::wstring>();
	//if (bdc == L"Following") fixedLegConvention = Following;
	//else if (bdc == L"ModifiedFollowing") fixedLegConvention = ModifiedFollowing;
	//else if (bdc == L"Preceding") fixedLegConvention = Preceding;
	//else if (bdc == L"ModifiedPreceding") fixedLegConvention = ModifiedPreceding;
	//else if (bdc == L"Unadjust") fixedLegConvention = Unadjusted;
	//else throw(std::exception("undefined BDC"));
	//Schedule fixedSchedule(effectiveDate, terminationDate, Period(fixedLegFrequency), calendar, fixedLegConvention, fixedLegConvention, DateGeneration::Backward, false);

	////12. Floating leg
	//double alpha = XMLValue(element, "PayerPaymentSpread").GetValue<double>();
	//double pastFixing = XMLValue(element, "PayerPastFixing").GetValue<double>();


	///////////////////////////////////////////////////////////////////////////////////////////////
	//13. CURVE BUILDING
	//Discount Curve
	XMLElement* element0 = doc.FirstChildElement("root")->FirstChildElement("param_root")->FirstChildElement("curve_root")->FirstChildElement("curve");
	element = element0->FirstChildElement("CurveData");
	std::wstring curveDC = ::ToWString(element->Attribute("DayCounter"));
	DayCounter curveDayCounter = Actual365Fixed();
	if (curveDC == L"Actual/365 (Fixed)") curveDayCounter = Actual365Fixed();
	else if (curveDC == L"Actual/360") curveDayCounter = Actual360();
	else if (curveDC == L"Actual/Actual") curveDayCounter = ActualActual();
	else if (curveDC == L"30/360") curveDayCounter = Thirty360();
	else throw(std::exception("undefined DayCounter"));
	std::vector<Date> dates;	std::vector<Rate> rates;
	XMLElement* cdata = element->FirstChildElement("CurveDataItem");
	while (1) {
		std::wstring yield = ::ToWString(cdata->Attribute("Yield"));
		std::wstring date = ::ToWString(cdata->Attribute("Date"));
		rates.push_back(std::stod(yield));
		dates.push_back(ConvertToDate(date));
		if (cdata == element->LastChildElement("CurveDataItem")) break;
		cdata = cdata->NextSiblingElement();
	}
	Handle<YieldTermStructure> discTermStructure(boost::shared_ptr<YieldTermStructure>(new InterpolatedZeroCurve<Linear>(dates, rates, curveDayCounter)));
	boost::shared_ptr<IborIndex> index(new Euribor3M(discTermStructure));

	//CMS Curve
	XMLElement* element1 = element0->NextSiblingElement();
	if (!element1)
		element1 = element0;
	
	element = element1->FirstChildElement("CurveData");
	curveDC = ::ToWString(element->Attribute("DayCounter"));
	curveDayCounter = Actual365Fixed();
	if (curveDC == L"Actual/365 (Fixed)") curveDayCounter = Actual365Fixed();
	else if (curveDC == L"Actual/360") curveDayCounter = Actual360();
	else if (curveDC == L"Actual/Actual") curveDayCounter = ActualActual();
	else if (curveDC == L"30/360") curveDayCounter = Thirty360();
	else throw(std::exception("undefined DayCounter"));
	dates.resize(0);	rates.resize(0);
	cdata = element->FirstChildElement("CurveDataItem");
	while (1) {
		std::wstring yield = ::ToWString(cdata->Attribute("Yield"));
		std::wstring date = ::ToWString(cdata->Attribute("Date"));
		rates.push_back(std::stod(yield));
		dates.push_back(ConvertToDate(date));
		if (cdata == element->LastChildElement("CurveDataItem")) break;
		cdata = cdata->NextSiblingElement();
	}
	Handle<YieldTermStructure> cmsTermStructure(boost::shared_ptr<YieldTermStructure>(new InterpolatedZeroCurve<Linear>(dates, rates, curveDayCounter)));
	boost::shared_ptr<IborIndex> cmsIndex(new Euribor3M(cmsTermStructure));


	//Schedule floatingSchedule(effectiveDate, terminationDate, index->tenor(), calendar, index->businessDayConvention(), index->businessDayConvention(), DateGeneration::Backward, false);

	//14. SWAPTION VOL
	element = element1->FirstChildElement("SwaptionVolData");

	SwaptionVolData swaptionVolData;
	XMLElement* vdata = element->FirstChildElement("SwaptionVolDataItem");
	Period length = Period();
	Period maturity = Period();
	while (1) {
		std::wstring vol = ::ToWString(vdata->Attribute("Vol"));
		std::wstring len = ::ToWString(vdata->Attribute("Length"));
		std::wstring mat = ::ToWString(vdata->Attribute("Maturity"));

		length = PeriodParser::parse(::ToString(len));
		maturity = PeriodParser::parse(::ToString(mat));

		Date terminal = evaluationDate + length + maturity;
		//unsigned int n = std::abs(terminal - terminationDate);
		swaptionVolData.vols.push_back(std::stod(vol));
		swaptionVolData.lengths.push_back(length);swaptionVolData.maturities.push_back(maturity);
		if (vdata == element->LastChildElement("SwaptionVolDataItem")) break;
		vdata = vdata->NextSiblingElement();
	}
	swaptionVolData.fixedFreq = index->tenor().frequency();
	swaptionVolData.fixedDC = index->dayCounter();
	swaptionVolData.floatingDC = index->dayCounter();
	swaptionVolData.index = index;

	// global data
	RelinkableHandle<YieldTermStructure> termStructure;
	boost::shared_ptr<IborIndex> iborIndex;
	Handle<SwaptionVolatilityStructure> atmVol;
	Handle<SwaptionVolatilityStructure> SabrVolCube1;
	GFunctionFactory::YieldCurveModel yieldCurveModels;
	boost::shared_ptr<CmsCouponPricer> numericalPricers;
	boost::shared_ptr<CmsCouponPricer> analyticPricers;	

	termStructure.linkTo(cmsTermStructure.currentLink());
	iborIndex = boost::shared_ptr<IborIndex>(new Euribor6M(termStructure));

	// ATM Volatility structure
	Size n = swaptionVolData.vols.size();
	std::vector<Period> v(swaptionVolData.maturities.begin(), swaptionVolData.maturities.end());
	std::sort(v.begin(), v.end());
	Size nm = std::unique(v.begin(), v.end()) - v.begin();

	std::vector<Period> v1(swaptionVolData.lengths.begin(), swaptionVolData.lengths.end());
	std::sort(v1.begin(), v1.end());
	Size nl = std::unique(v1.begin(), v1.end()) - v1.begin();

	std::vector<Period> atmOptionTenors;
	std::vector<Period> atmSwapTenors;
	Matrix m(nm, nl);
	for (Size i = 0; i < nm; ++i) {
		atmOptionTenors.push_back(v[i]);
		for (Size j = 0; j < nl; ++j) {
			if (i==0)
				atmSwapTenors.push_back(v1[j]);
			m[i][j] = swaptionVolData.vols[i*nl + j];
		}
	}
	atmVol = Handle<SwaptionVolatilityStructure>(boost::shared_ptr<SwaptionVolatilityStructure>(new
		SwaptionVolatilityMatrix(calendar,
			Following,
			atmOptionTenors,
			atmSwapTenors,
			m,
			Actual365Fixed(),
			true //flat extrapolation
			)));

	yieldCurveModels = GFunctionFactory::Standard;
	Handle<Quote> zeroMeanRev(boost::shared_ptr<Quote>(new SimpleQuote(0.0)));
	numericalPricers = boost::shared_ptr<CmsCouponPricer>(new NumericHaganPricer(atmVol, yieldCurveModels, zeroMeanRev));
	analyticPricers  = boost::shared_ptr<CmsCouponPricer>(new AnalyticHaganPricer(atmVol, yieldCurveModels, zeroMeanRev));

	boost::shared_ptr<SwapIndex> swapIndex(new SwapIndex("EuriborSwapIsdaFixA",
		tenorsInYears * Years,  // Tenor
		iborIndex->fixingDays(),
		iborIndex->currency(),
		iborIndex->fixingCalendar(),
		6 * Months,  // fixed leg tenor
		Unadjusted,
		iborIndex->dayCounter(),//??
		iborIndex));

	//Quanto
	Real ratevol = atmVol->volatility(terminationDate, tenorsInYears, Rate0);
	Real qadj = std::exp(-fxcorr * fxvol * ratevol * Actual365Fixed().yearFraction(evaluationDate, terminationDate));

	//Input Parameters
	Date startDate = effectiveDate;
	Date endDate = terminationDate;
	
	Real ttm = ActualActual(ActualActual::ISMA).yearFraction(startDate, endDate);
	Date paymentDate = endDate + 2 * Days;	
	Real nominal = notional;

	Real R0 = Rate0 / qadj;
	Real strike1 = lower*R0, strike2 = upper*R0;
	Real couponRate = cpnRate;
	
	Real p1 = (1.0 / ttm + couponRate) / qadj, p2 = 0.0;
	if (callput == L"Put") {
		p2 = p1;
		p1 = 0.0;
	}

	Real gearing = (p1 - p2) / (strike1 - strike2);
	Spread spread = p1 - gearing * strike1;
	Rate infiniteCap = (1.0 / ttm + couponRate) / qadj;
	Rate infiniteFloor = 0.0;

	CappedFlooredCmsCoupon coupon(paymentDate, nominal,
		startDate, endDate,
		swapIndex->fixingDays(), swapIndex,
		gearing, spread,
		infiniteCap, infiniteFloor,
		startDate, endDate,
		ActualActual(ActualActual::ISMA),
		true);

	boost::shared_ptr<YieldTermStructure> disc(discTermStructure.currentLink());

	analyticPricers->setSwaptionVolatility(atmVol);
	coupon.setPricer(analyticPricers);
	Rate rate = coupon.rate();
	Rate NPV = coupon.amount() * disc->discount(coupon.date()) * qadj;
	return NPV;
}