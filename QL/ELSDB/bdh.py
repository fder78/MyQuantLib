# -*- coding: utf-8 -*-
import xmlrpc.client
import re
import pymysql
from datetime import datetime, date, timedelta

DBHOST = 'fdos-mt'
DBUSER = 'root'
DBPASSWORD = '3450'

cnxn = pymysql.connect(host=DBHOST,user=DBUSER,passwd=DBPASSWORD, port=3306, charset='euckr')
cn = cnxn.cursor()

def blp( ticker, field ) :
    proxy = xmlrpc.client.ServerProxy("http://10.50.20.204:5500")
    res = proxy.blp( ticker, field )
    return res  

def blph( ticker, field, yyyy, mm, dd ):
    proxy = xmlrpc.client.ServerProxy("http://10.50.20.204:5500")
    res = proxy.blph( ticker, field, yyyy, mm, dd )
    return res  

def blph2( ticker, field, yy1, mm1, dd1, yy, mm, dd, prdUnit, numPeriod, activeDateOption):
    proxy = xmlrpc.client.ServerProxy("http://10.50.20.204:5500")
    res = proxy.blph2( ticker, field, yy1, mm1, dd1, yy, mm, dd, prdUnit, numPeriod, activeDateOption )
    return res  

def getCurncy( crn, dates ) :
	if crn == "KRW" :
		return 1
	elif crn == "USD" :
		query = "select 일자 from ficc.holidays where 일자 < '" + dates.strftime("%Y-%m-%d") + "' and 서울 = 'N' order by 일자 desc limit 1"
		cn.execute( query )
		dates = cn.fetchone()[0]
	proxy = xmlrpc.client.ServerProxy("http://10.50.20.204:5500")
	res = proxy.blph( "KOBR"+crn+" Index", "last price", int(dates.strftime("%Y")), int(dates.strftime("%m")), int(dates.strftime("%d")))
	return res  

def ToMonthCode( month ) :
	if month == 1 :
		res = "F"
	elif month == 2 :
		res = "G"
	elif month == 3 :
		res = "H"
	elif month == 4 :
		res = "J"
	elif month == 5 :
		res = "K"
	elif month == 6 :
		res = "M"
	elif month == 7 :
		res = "N"
	elif month == 8 :
		res = "Q"
	elif month == 9 :
		res = "U"
	elif month == 10 :
		res = "V"
	elif month == 11 :
		res = "X"
	elif month == 12 :
		res = "Z"
	
	return res

def ToBLPCode( underlying, maturity, FPC, strike ) :
	if FPC == "F" : # Futures
		if underlying == "U180" :
			res = "KM" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Index"
		elif underlying == "HSCEI" :
			res = "HC" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Index"
		elif underlying == "SPX" :
			res = "ES" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Index"
		elif underlying == "NKY Index" :
			res = "NI" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Index"
		elif underlying == "NKY IndexO" :
			res = "NK" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Index"
		elif underlying == "VIX" :
			res = "UX" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Index"
		elif underlying == "SILVER" :
			res = "SI" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Comdty"
		elif underlying == "SILVERmINY" :
			res = "ID" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Comdty"
		elif underlying == "MicroGold" :
			res = "MGC" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Comdty"
		elif underlying == "GoldmINY" :
			res = "BQ" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Comdty"
		elif underlying == "Gold" :
			res = "GC" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Comdty"
		elif underlying == "SX5E" :
			res = "VG" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Index"
		elif underlying == "USD" :
			res = "KO" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " Curncy"
		elif re.search( "^A([0-9]{5})0$", underlying ) :
			match = re.search( "^A([0-9]{5})0$", underlying ).group(0)
			res = match[1:-1] + "=" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + " KS Equity"
	elif FPC == "S" : # Stock
		if re.search( "^A([0-9]{5})0$", underlying ) :
			match = re.search( "^A([0-9]{5})0$", underlying ).group(0)
			res = match[1:] + " KS Equity"
	else : # Option 
		if underlying == "U180" :
			res = "KOSPI2 " + str(maturity)[2:4] + "/" + str(maturity)[0:2] + " " + FPC + str(strike) + " Index"
		elif underlying == "HSCEI" :
			res = "HSCEI " + str(maturity)[2:4] + "/" + str(maturity)[0:2] + " " + FPC + str(strike) + " Index"
		elif underlying == "SPX" :
			res = "ES" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + FPC + " " + str(strike) + " Index"
		elif underlying == "SILVER" :
			res = "SI" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + FPC + " " + str(strike/100) + " Comdty"
		elif underlying == "Gold" :
			res = "GC" + ToMonthCode( int(str(maturity)[2:4]) ) + str(maturity)[1] + FPC + " " + str(strike) + " Comdty"
		elif underlying == "NKY Index" :
			res = "NKY " + str(maturity)[2:4] + "/" + str(maturity)[0:2] + " " + FPC + str(strike) + " Index"
		elif underlying == "NKY IndexO" :
			res = "NKY " + str(maturity)[2:4] + "/" + str(maturity)[0:2] + " " + FPC + str(strike) + " Index"
		elif underlying == "SX5E" :
			res = "SX5E " + str(maturity)[2:4] + "/" + str(maturity)[0:2] + " " + FPC + str(strike) + " Index"
	return res
 
if __name__=="__main__":
    #print( bdh( "", "last price", 2013,11,11 ) )
    
    proxy = xmlrpc.client.ServerProxy("http://10.50.20.204:5500")
    print(proxy.blph2( "HSCEI Index", "last price", 2017,1,1,2017,1,11,"DAILY",52,"ALL_CALENDAR_DAYS"))#,"WEEKLY",52,"ALL_CALENDAR_DAYS" ))
    print(proxy.blp( "hscei index", "last price" ))
    print(proxy.blp( "USDKRW Curncy", "last price" ))
    #print(proxy.blp( "010520 Equity", "last price" ))
    
    #print(proxy.blph( "SIH4 Comdty", "last price", 2014,2,5 ))

