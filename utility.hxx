/* Copyright (c) Arcoth@c-plusplus.net, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef UTILITY_HXX_INCLUDED
#define UTILITY_HXX_INCLUDED

#include "typedefs.hxx"

#include <stdexcept>

namespace vtmpl
{

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

	template <std::size_t N>
	constexpr void assert(bool b, char const(&msg)[N])
	{
		if (!b)
			throw std::invalid_argument(msg);
	}

}

#endif // UTILITY_HXX_INCLUDED
