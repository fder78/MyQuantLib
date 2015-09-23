#include <ql/quantlib.hpp>
#include <iostream>
#include <fstream>
#include <boost/progress.hpp>
#include <boost/assign/std/vector.hpp> 
#include <fstream>

namespace QuantLib
{
	Integer sessionId()
	{
		return 0;
	}

	void* mutex = NULL;
	void* createMutex() { return NULL; }
	void __Lock::AchieveLock() { }
	void __Lock::ReleaseLock() { }
}

using namespace QuantLib;

int main() {
	
	try{
		std::ofstream fout("C:\\vol test.csv");

		Calendar calendar = TARGET();
		Date settlementDate(25, Sep, 2013);
		DayCounter dayCounter = Thirty360();

		Real underlying = 261.45;
		Spread dividendYield = 0.011394;
		Rate riskFreeRate = 0.027225;

		Handle<Quote> underlyingH(
			boost::shared_ptr<Quote>(new SimpleQuote(underlying)));

		// bootstrap the yield/dividend/vol curves
		Handle<YieldTermStructure> flatTermStructure(
			boost::shared_ptr<YieldTermStructure>(
			new FlatForward(settlementDate, riskFreeRate, dayCounter)));

		Handle<YieldTermStructure> flatDividendTS(
			boost::shared_ptr<YieldTermStructure>(
			new FlatForward(settlementDate, dividendYield, dayCounter)));

		using namespace boost::assign;

		std::vector<Date> dateVec;
		std::vector<Size> days;
		days+=30, 60, 90, 180, 270, 360, 540, 720, 1080;

		for(Size i=0;i<days.size();++i){
			dateVec.push_back(settlementDate+days[i]*Days);
		}

		std::vector<Real> strikes;
		strikes += 104.58, 117.6525, 130.725, 143.7975, 156.87, 169.9425, 183.015, 196.0875, 209.16, 222.2325, 235.305, 248.3775, 261.45, 274.5225, 287.595, 300.6675, 313.74;

		std::vector<Volatility> v;
		v += 0.617477292231429,0.564274001090222,0.515421605211073,0.470017858628986,0.427377646259071,0.386960859562809,0.348326993755946,0.311107228961548,0.27499310485853,0.239755478150912,0.205356231059388,0.172427905656833,0.144299030385647,0.131124293289777,0.137483310065874,0.152567132133481,0.169715716051344,
			0.51713760705746,0.47459920046194,0.435566324515745,0.399328505512051,0.365352864236385,0.333229100218421,0.30263769091605,0.27333571883673,0.245163300254554,0.218088767032983,0.192350922544802,0.168866553161649,0.150197952945543,0.140992788443366,0.143076508838536,0.152212484155459,0.164187772564809,
			0.464129412137984,0.427584681802939,0.394077147738582,0.363004307830376,0.333919069598286,0.306484015612607,0.280446446149198,0.255629867823509,0.231944800725522,0.209432740884784,0.18837927658962,0.169568035776845,0.154694765214984,0.146278831061511,0.145538154177105,0.150646469283411,0.158888331646468,
			0.378297031368133,0.350945717444768,0.325970749704418,0.302936666966769,0.281532893335923,0.261542340788873,0.242827127067572,0.225328312325624,0.209080584858719,0.194245259588529,0.181161752819973,0.170393469548814,0.162674779718641,0.158611144887026,0.158222120077432,0.160838680453472,0.165511447992692,
			0.354825516013235,0.330720418119458,0.308756602706215,0.2885548622096,0.269847954931093,0.252452646085907,0.236256218589732,0.221213709620513,0.207354530613352,0.194797346773909,0.183768147380812,0.174603938995843,0.167703400557153,0.163385549347417,0.161700006273167,0.162349335702646,0.16481201446804,
			0.344603917655515,0.322117382187098,0.301655982356119,0.282867377182824,0.265504258777971,0.249397774308228,0.234443987409134,0.220599381611106,0.207883314656376,0.196385289511135,0.186272073563045,0.177782678170687,0.171190244825169,0.166714199836834,0.164407106659071,0.164095163438497,0.165428621176153,
			0.332738298610015,0.312025035068773,0.293221858192477,0.276006066410748,0.260153052495123,0.245511298824774,0.23198900234207,0.219548177601993,0.208203603017333,0.198023825757732,0.189129585081457,0.181681739522333,0.175848932441976,0.17175210046286,0.169403607698001,0.168677827805929,0.16933639499432,
			0.326170550582517,0.306456800694291,0.288595313817871,0.272280104624839,0.257299614905525,0.243512539695351,0.230834509326476,0.219231412505291,0.208716505472399,0.199348343921601,0.191225304126209,0.184470821175927,0.179204017684821,0.175497272840155,0.173335659412994,0.172601352441305,0.173094279669659,
			0.319689347303201,0.301089510371098,0.284275711451528,0.268959549468738,0.254942510511664,0.242092547522573,0.230330640914388,0.219623135774972,0.209976955124277,0.201434901905973,0.194067729310373,0.187959366154857,0.183183306028258,0.17977331226368,0.177698697212819,0.176856826783737,0.177087633891139;

		Matrix blackVolMatrix(strikes.size(), dateVec.size());
		for (Size i=0; i < strikes.size(); ++i){
			for (Size j=0; j < dateVec.size(); ++j) {
				blackVolMatrix[i][j] = v[j*strikes.size()+i];
			}
		}
		boost::shared_ptr<BlackVarianceSurface> VolSurf(
			new BlackVarianceSurface(settlementDate, calendar, dateVec, strikes, blackVolMatrix, dayCounter));

		boost::shared_ptr<BlackScholesMertonProcess> bsmProcess(
			new BlackScholesMertonProcess(underlyingH, flatDividendTS, flatTermStructure, Handle<BlackVolTermStructure>(VolSurf)));
		VolSurf->setInterpolation(Bicubic());

		LocalVolSurface LV = LocalVolSurface(Handle<BlackVolTermStructure>(VolSurf), flatTermStructure, flatDividendTS, underlyingH);

		Matrix LVMatrix(strikes.size(), dateVec.size());
		for(Size i = 0; i < dateVec.size(); ++i)
		{
			for(Size j = 0; j < strikes.size(); ++j)
			{
				LVMatrix[i][j] = LV.localVol(dateVec[i],strikes[j],true);
				std::cout << std::left << dateVec[i]
				<< " /  "
					<< std::left << strikes[j]
				<< " / "
					<< std::left << LVMatrix[i][j]
				<< std::endl;
				fout<<LVMatrix[i][j]<<",";
			}
			fout<<std::endl;
		}

		fout<<std::endl;
			for (Size i=0; i<30; ++i) {
				for (Size j=0; j<25; ++j) {
					Time t = i/10.0;
					Real k = 100 + j * 10;
					Real lv = LV.localVol(t,k,true);
					std::cout<<lv<<std::endl;
					fout<<lv<<",";
				}
				fout<<std::endl;
			}


		fout.close();

		return 0;

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "unknown error" << std::endl;
	}
}


//
//int main() {
//
//	std::ofstream fout;
//	fout.open("C:\\vol test.csv");
//
//	const Date settlementDate(5, July, 2002);
//	Settings::instance().evaluationDate() = settlementDate;
//
//	const DayCounter dayCounter = Actual365Fixed();
//	const Calendar calendar = TARGET();
//
//	Integer t[] = { 30, 61, 91, 183, 274, 365, 548, 730, 1095 };
//	Rate r[] = { 0.0357,0.0349,0.0341,0.0355,0.0359,0.0368,0.0386,0.0401,0.0401 };
//
//	std::vector<Rate> rates(1, 0.0357);
//	std::vector<Date> dates(1, settlementDate);
//	for (Size i = 0; i < 9; ++i) {
//		dates.push_back(settlementDate + t[i]);
//		rates.push_back(r[i]);
//	}
//	const boost::shared_ptr<YieldTermStructure> rTS(new ZeroCurve(dates, rates, dayCounter));
//	const boost::shared_ptr<YieldTermStructure> qTS(new FlatForward(settlementDate, 0.0, dayCounter));
//
//	const boost::shared_ptr<Quote> s0(new SimpleQuote(1.0));
//
//	Real tmp[] = { 0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1,1.05,1.1,1.15,1.2 };
//	const std::vector<Real> strikes(tmp, tmp+17);
//	strikes += 2,3;
//
//	Volatility v[] =
//	{ 0.625925	,	0.571114,	0.520792,	0.474025,	0.430105,	0.38847,	0.34866,	0.310286,	0.273016,	0.236588,	0.200928,	0.166678,	0.137737,	0.126577,	0.136387,	0.153821,	0.172593,
//	0.523764,	0.480213,	0.440246,	0.403131,	0.368319,	0.335386,	0.303998,	0.273895,	0.244896,	0.21694,	0.190229,	0.165663,	0.145994,	0.1366,	0.139519,	0.149655,	0.16244,
//	0.467588,	0.430238,	0.395982,	0.364201,	0.334436,	0.306336,	0.279635,	0.254143,	0.229752,	0.206484,	0.184609,	0.164939,	0.149368,	0.140884,	0.140865,	0.146962,	0.15608,
//	0.381998,	0.353872,	0.328167,	0.30443,	0.28234,	0.261664,	0.242253,	0.224034,	0.207027,	0.191387,	0.177461,	0.165872,	0.157493,	0.153111,	0.152809,	0.155797,	0.160953,
//	0.357328,	0.332674,	0.310187,	0.289477,	0.270269,	0.25237,	0.235658,	0.220079,	0.205656,	0.192504,	0.180857,	0.171084,	0.163649,	0.158957,	0.157112,	0.1578,	0.160432,
//	0.343006,	0.320339,	0.299704,	0.280746,	0.263214,	0.246938,	0.231812,	0.217794,	0.204904,	0.193241,	0.182984,	0.174396,	0.167781,	0.163383,	0.161257,	0.161202,	0.162828,
//	0.330076,	0.309517,	0.290836,	0.273712,	0.257919,	0.243304,	0.229769,	0.217269,	0.20581,	0.195449,	0.186297,	0.17851,	0.172262,	0.167696,	0.16486,	0.163667,	0.163904,
//	0.321796,	0.302528,	0.285052,	0.269067,	0.254362,	0.240793,	0.228269,	0.216748,	0.206227,	0.196748,	0.18839,	0.181263,	0.175483,	0.17114,	0.168259,	0.166773,	0.166528,
//	0.311176,	0.293491,	0.277492,	0.2629,	0.249524,	0.237231,	0.225937,	0.215597,	0.206204,	0.197778,	0.190367,	0.184036,	0.178849,	0.174848,	0.172036,	0.170358,	0.169708,
// };
//
//	Matrix blackVolMatrix(strikes.size(), dates.size()-1);
//	for (Size i=0; i < strikes.size(); ++i) {
//		for (Size j=0; j < dates.size()-1; ++j) {
//			blackVolMatrix[i][j] = v[j*strikes.size() + i];
//		}
//	}
//
//	const boost::shared_ptr<BlackVarianceSurface> volTS(
//		new BlackVarianceSurface(settlementDate, calendar, std::vector<Date>(dates.begin()+1, dates.end()),	strikes, blackVolMatrix, dayCounter));
//	//volTS->setInterpolation<Bicubic>();
//
//
//	boost::shared_ptr<LocalVolSurface> vol(new LocalVolSurface(Handle<BlackVolTermStructure>(volTS),
//		Handle<YieldTermStructure>(rTS),
//		Handle<YieldTermStructure>(qTS),
//		Handle<Quote>(s0)));
//
//
//	for (Size i=0; i<30; ++i) {
//		for (Size j=0; j<25; ++j) {
//			Time t = i/10.0;
//			Real k = 0.3 + j/25.0;
//			Real lv = vol->localVol(t,k,true);
//			std::cout<<lv<<std::endl;
//			fout<<lv<<",";
//		}
//		fout<<std::endl;
//	}
//	
//	fout.close();
//	std::cout<<"done"<<std::endl;
//	return 0;
//}