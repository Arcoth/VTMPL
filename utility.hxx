#ifndef UTILITY_HXX_INCLUDED
#define UTILITY_HXX_INCLUDED

#include "typedefs.hxx"

#include <stdexcept>

namespace vtmpl
{

	struct non_literal
	{
		non_literal(int);
	};

	constexpr bool isdigit( char c )
	{
		return c >= '0' && c <= '9';
	}

	template<typename T>
	constexpr T max( T a, T b )
	{
		return a > b? a : b;
	}

	template<typename T>
	constexpr T min( T a, T b )
	{
		return a < b? a : b;
	}

	#define VTMPL_ASSERT( B, MSG ) ( B? 0 : throw ::std::invalid_argument{MSG})

}

#endif // UTILITY_HXX_INCLUDED
