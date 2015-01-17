/* Copyright (c) Arcoth@c-plusplus.net, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef PARSERS_HXX_INCLUDED
#define PARSERS_HXX_INCLUDED

#include "utility.hxx"

#include <utility>

# if !VTMPL_RELAX_CONSTEXPR_FUNC
#
# warning \
This file uses C++1Y-features (relaxed constraints on constexpr-functions). \
If your compiler supports C++1Y-features, activate them through a flag (most commonly -std=c++1y). \
Or, if your compiler lacks the macro definition, #define VTMPL_RELAX_CONSTEXPR_FUNC to 1 yourself.
#
# endif


namespace vtmpl
{

	template< typename String >
	constexpr std::pair<std::uintmax_t, size_type> parse_unsigned( size_type pos = 0 )
	{
		std::uintmax_t rval = 0;
		bool read_anything = false;

		while( pos < String::length && isdigit(String::array[pos]) )
		{
			read_anything = true;
			rval *= 10;
			rval += String::array[pos] - '0';
			++pos;
		}

		VTMPL_ASSERT(read_anything, "Applied parse_unsigned to string without digits!");

		return {rval, pos};
	}

	template< typename String >
	constexpr std::pair<std::intmax_t, size_type> parse_signed( size_type pos = 0 )
	{
		bool negative = false;

		char first = String::array[pos];
		if( first == '-' )
		{
			negative = true;
			++pos;
		}
		else if( first == '+' )
			++pos;
		else
			vtmpl::assert(isdigit(first), "Applied parse_signed to string without sign or digit!");

		auto pair = parse_unsigned<String>(pos);

		if( negative )
			pair.first *= -1;

		return pair;
	}

}

#endif // PARSERS_HXX_INCLUDED
