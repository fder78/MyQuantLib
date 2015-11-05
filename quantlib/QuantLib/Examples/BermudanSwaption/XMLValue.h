#pragma once

#include "StringUtil.h"

using namespace tinyxml2;

// By Hyun Chul
class XMLValue
{
public:
	XMLValue( const XMLElement* record, const std::string& param )
		: m_record( record )
	{
		m_param = param;
		const XMLElement* firstElement = record->FirstChildElement( param.c_str() );
		if( firstElement )
		{
			m_type = ::ToWString( firstElement->Attribute( "type" ) );
			m_value = ::ToWString( firstElement->Attribute( "value" ) );
		}
		else
		{
			m_type = L"empty";
			m_value = L"";
		}
	}

	std::wstring GetType() const { return m_type; }

	Date GetValueT( const Date& ) const
	{
		QL_ASSERT( m_type == L"date", m_param + "의 타입이 date가 아닙니다." );
		if( m_value.find( L"-") != std::wstring::npos )
		{
			return ::ConvertToDate( m_value );
		}
		else
		{
			return ::ConvertToDateFromBloomberg( m_value );
		}
	}

	Real GetValueT( const Real& ) const
	{
		QL_ASSERT( m_type == L"double", m_param + "의 타입이 double이 아닙니다." );
		return boost::lexical_cast<Real>( m_value );
	}

	int GetValueT( const int& ) const
	{
		QL_ASSERT( m_type == L"double", m_param + "의 타입이 double이 아닙니다." );
		return boost::lexical_cast<int>( m_value );
	}

	bool GetValueT( const bool& ) const
	{
		QL_ASSERT( m_type == L"double", m_param + "의 타입이 double이 아닙니다." );
		return boost::lexical_cast<double>( m_value ) != 0;
	}

	std::wstring GetValueT( const std::wstring& ) const
	{
		QL_ASSERT( m_type == L"string", m_param + "의 타입이 string이 아닙니다." );
		return m_value;
	}

	const char* GetValueT( const char* ) const
	{
		return m_record->FirstChildElement( m_param.c_str() )->Attribute( "value" );
	}

	template<typename T>
	T GetNullableValue() const
	{
		if( m_type == L"empty" || m_value == L"" )
		{
			return T();
		}

		return GetValueT( T() );
	}

	template<typename T>
	T GetValue() const
	{
		if( m_type == L"empty" || m_value == L"" )
		{
			return T();
		}

		return GetValueT( T() );
	}

	template<typename T>
	operator T() const
	{
		return GetValueT( T() );
	}

private:
	std::string m_param;
	std::wstring m_type;
	std::wstring m_value;
	const XMLElement* m_record;
};

inline bool operator == ( const XMLValue& lhs, const wchar_t* rhs )
{
	return lhs.GetValue<std::wstring>() == std::wstring( rhs );
}

inline bool operator != ( const XMLValue& lhs, const wchar_t* rhs )
{
	return lhs.GetValue<std::wstring>() != std::wstring( rhs );
}


template<typename T>
bool operator == ( const XMLValue& lhs, const T& rhs )
{
	return lhs.GetValue<T>() == rhs;
}

template<typename T>
bool operator != ( const XMLValue& lhs, const T& rhs )
{
	return lhs.GetValue<T>() != rhs;
}

inline std::string ConvertDateFormat( const Date& bloombergFormat )
{
	return ::ToString( ::ToWString( bloombergFormat ) );
}

inline std::string GetType( bool val )
{
	return "double";
}

inline std::string GetType( double val )
{
	return "double";
}

inline std::string GetType( const std::string& val )
{
	return "string";
}

inline std::string GetType( const Date& val )
{
	return "date";
}

inline std::string GetType( int val )
{
	return "double";
}

//template<typename T>
//void SetXMLValue( TiXmlNode& parent, const std::string& name, const T& v )
//{
//	std::string type( ::GetType( v ) );
//	TiXmlElement* node = static_cast<TiXmlElement*>( parent.InsertEndChild( TiXmlElement( name ) ) );
//
//	node->SetAttribute( "type", type );
//	node->SetAttribute( "value", ::ToString( ::ToWString( v ) ) );
//}

// = 연산자에 Str 암시적변환이 잘 안되어서 만듦
class XMLStrValue
{
public:
	XMLStrValue( const XMLElement* record, const std::string& param )
		: m_value( record, param )
	{
	}

	operator std::wstring() const
	{
		return GetValue();
	}

	std::wstring GetValue() const
	{
		return m_value.GetValueT( std::wstring() );
	}

private:
	XMLValue m_value;
};