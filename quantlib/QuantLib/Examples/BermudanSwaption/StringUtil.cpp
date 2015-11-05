
#include "StringUtil.h"

bool CompareString( std::wstring lhs, std::wstring rhs )
{
	std::transform( lhs.begin(), lhs.end(), lhs.begin(), ::towupper );
	std::transform( rhs.begin(), rhs.end(), rhs.begin(), ::towupper );

	return ( lhs == rhs );
}
