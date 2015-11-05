
#pragma warning(disable:4819)

#include <tchar.h>
#include <windows.h>
#include <oleauto.h>
#include <assert.h>

#include "StringUtil.h"
#include "XMLValue.h"
#include <ql/quantlib.hpp>
#include <ir_derivatives\g2_calibration.hpp>
#include <ir_derivatives\pricing_cms_spread_ra.hpp>

#define QL_ENABLE_SESSIONS

#ifdef BOOST_MSVC
/* Uncomment the following lines to unmask floating-point
   exceptions. Warning: unpredictable results can arise...

   See http://www.wilmott.com/messageview.cfm?catid=10&threadid=9481
   Is there anyone with a definitive word about this?
   */
// #include <float.h>
// namespace { unsigned int u = _controlfp(_EM_INEXACT, _MCW_EM); }
#endif

#include <boost/timer.hpp>
#include <iostream>
#include <iomanip>

using namespace QuantLib;
using namespace tinyxml2;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {
	Integer sessionId() { return 0; }
}
#endif


int _tmain(int argc, _TCHAR* argv[]) {

	try{

		if (argc > 1) {

			const char* fileName = argv[1];
			tinyxml2::XMLDocument doc;
			XMLError e = doc.LoadFile(fileName);
			if (e == XML_SUCCESS) {

				XMLElement* element = doc.FirstChildElement("root")->FirstChildElement("param_root")->FirstChildElement("eval_time");
				const char* datestr = element->Attribute("value");
				Date evaluationDate = ConvertToDateFromBloomberg(::ToWString(datestr));
				Settings::instance().evaluationDate() = evaluationDate;
				
				element = doc.FirstChildElement("root")->FirstChildElement("param_root")->FirstChildElement("data_root")->FirstChildElement("record");
				//pastAccrual
				double pastAccrual = 0.0;

				std::wstring grid = XMLValue(element, "NumOfSimul").GetValue<std::wstring>();
				std::vector<Size> gridnum;
				std::vector<std::wstring> gridStr;
				boost::algorithm::split(gridStr, grid, boost::is_any_of(L"/"), boost::algorithm::token_compress_on);
				gridnum.push_back(boost::lexical_cast<Size>(gridStr[0]));
				gridnum.push_back(boost::lexical_cast<Size>(gridStr[1]));

				//notional
				double notional = XMLValue(element, "Notional").GetValue<double>();
				//swap type
				std::wstring payrec = XMLValue(element, "PayRec").GetValue<std::wstring>();
				VanillaSwap::Type type = VanillaSwap::Receiver;
				if (payrec==L"Pay")
					type = VanillaSwap::Payer;
				//coupon rate
				double cpnRate = XMLValue(element, "AccrualRate").GetValue<double>();
				Calendar calendar = SouthKorea();
				//Spread Tenors
				std::vector<Size> tenorsInYears;
				std::vector<std::wstring> tenorStr;
				std::wstring tenorMat = XMLValue(element, "TenorMatrix").GetValue<std::wstring>();
				boost::algorithm::split(tenorStr, tenorMat, boost::is_any_of(L","), boost::algorithm::token_compress_on);
				tenorsInYears.push_back(boost::lexical_cast<Size>(tenorStr[0]));
				tenorsInYears.push_back(boost::lexical_cast<Size>(tenorStr[1]));
				//Range
				double lower = XMLValue(element, "Obs1LowerLevel").GetValue<double>();
				double upper = XMLValue(element, "Obs1UpperLevel").GetValue<double>();

				//FirstCallDate
				Date firstCallDate = XMLValue(element, "CallStartDate").GetValue<Date>();

				//DayCounter
				DayCounter fixedLegDayCounter = Actual365Fixed();
				std::wstring dc = XMLValue(element, "DayCounterAccrual").GetValue<std::wstring>();
				if (dc == L"Actual365Fixed") fixedLegDayCounter = Actual365Fixed();
				else if (dc == L"Actual360") fixedLegDayCounter = Actual360();
				else if (dc == L"ActualActual") fixedLegDayCounter = ActualActual();
				else if (dc == L"30/360") fixedLegDayCounter = Thirty360();
				else throw(std::exception("undefined DayCounter"));

				//Schedule
				Date effectiveDate = XMLValue(element, "EffectiveDate").GetValue<Date>();
				Date terminationDate = XMLValue(element, "TerminationDate").GetValue<Date>();
				
				Frequency fixedLegFrequency;
				std::wstring tenor = XMLValue(element, "Tenor").GetValue<std::wstring>();				
				if (tenor == L"Annually") fixedLegFrequency = Annual;
				else if (tenor == L"Quarterly") fixedLegFrequency = Quarterly;
				else if (tenor == L"Semiannually") fixedLegFrequency = Semiannual;
				else throw(std::exception("undefined frequency"));

				BusinessDayConvention fixedLegConvention = Following;
				std::wstring bdc = XMLValue(element, "BDC").GetValue<std::wstring>();
				if (bdc == L"Following") fixedLegConvention = Following;
				else if (bdc == L"ModifiedFollowing") fixedLegConvention = ModifiedFollowing;
				else if (bdc == L"Preceding") fixedLegConvention = Preceding;
				else if (bdc == L"ModifiedPreceding") fixedLegConvention = ModifiedPreceding;
				else if (bdc == L"Unadjust") fixedLegConvention = Unadjusted;
				else throw(std::exception("undefined BDC"));
				Schedule fixedSchedule(effectiveDate, terminationDate, Period(fixedLegFrequency), calendar, fixedLegConvention, fixedLegConvention, DateGeneration::Backward, false);

				//floating leg
				double alpha = XMLValue(element, "PayerPaymentSpread").GetValue<double>();
				double pastFixing = XMLValue(element, "PayerPastFixing").GetValue<double>();

				///////////////////////////////////////////////////////////////////////////////////////////////			
				element = doc.FirstChildElement("root")->FirstChildElement("param_root")->FirstChildElement("curve_root")->FirstChildElement("curve")->FirstChildElement("CurveData");
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
				Handle<YieldTermStructure> rhTermStructure(boost::shared_ptr<YieldTermStructure>(new InterpolatedZeroCurve<Linear>(dates, rates, curveDayCounter)));
				boost::shared_ptr<IborIndex> index(new Euribor3M(rhTermStructure));

				element = doc.FirstChildElement("root")->FirstChildElement("param_root")->FirstChildElement("curve_root")->FirstChildElement("curve")->FirstChildElement("SwaptionVolData");
				//parameters calibration
				SwaptionVolData swaptionVolData;
				XMLElement* vdata = element->FirstChildElement("SwaptionVolDataItem");
				while (1) {
					std::wstring vol = ::ToWString(vdata->Attribute("Vol"));
					std::wstring len = ::ToWString(vdata->Attribute("Length"));
					std::wstring mat = ::ToWString(vdata->Attribute("Maturity"));
					swaptionVolData.vols.push_back(std::stod(vol));
					swaptionVolData.lengths.push_back(PeriodParser::parse(::ToString(len)));
					swaptionVolData.maturities.push_back(PeriodParser::parse(::ToString(mat)));
					if (vdata == element->LastChildElement("SwaptionVolDataItem")) break;
					vdata = vdata->NextSiblingElement();
				}
				swaptionVolData.fixedFreq = index->tenor().frequency();
				swaptionVolData.fixedDC = index->dayCounter();
				swaptionVolData.floatingDC = index->dayCounter();
				swaptionVolData.index = index;

				// defining the models
				boost::shared_ptr<G2> modelG2(new G2(rhTermStructure));
				G2Parameters param = calibration_g2(evaluationDate, swaptionVolData);				
				///////////////////////////////////////////////////////////////////////////////////////////////

				
				std::vector<Real> rst = cms_spread_rangeaccrual_fdm(
					evaluationDate,
					type,
					notional,
					std::vector<Rate>(1, cpnRate),		//std::vector<Rate> couponRate,
					std::vector<Rate>(1, 0.0),		//std::vector<Real> gearing,
					fixedSchedule,					//	Schedule schedule,
					fixedLegDayCounter,				//	DayCounter dayCounter,
					fixedLegConvention,				//	BusinessDayConvention bdc,
					tenorsInYears,					//  CMS spread tenors,
					std::vector<Real>(1, lower),		//	std::vector<Real> lowerBound,
					std::vector<Real>(1, upper),		//	std::vector<Real> upperBound,
					firstCallDate,				//	Date firstCallDate,
					pastAccrual,							//	Real pastAccrual,
					rhTermStructure.currentLink(),	//	boost::shared_ptr<YieldTermStructure> obs1Curve,
					param,							//	const G2Parameters& obs1G2Params,
					0.0, 0.0,						//	Real obs1FXVol, Real obs1FXCorr,
					rhTermStructure,				//	Handle<YieldTermStructure>& discTS,
					gridnum[0], gridnum[1],							//	Size tGrid, Size rGrid,
					alpha,							//	Real alpha,
					pastFixing								//	Real pastFixing,
				);

				double price = rst[0];
				std::cout.precision(20);
				std::cout << "OK" << price << std::endl;
			}
			else
				throw(std::exception("Cannot open the XML file"));
		}
		else {
			throw(std::exception("Need a XML file argument"));
		}
		return 0;

	}
	catch (std::exception& e) {
		std::cout << "FAIL:" << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cout << "FAIL:unknown error" << std::endl;
		return 1;
	}

}







