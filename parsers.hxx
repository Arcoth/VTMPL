/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef PARSERS_HXX_INCLUDED
#define PARSERS_HXX_INCLUDED

#include "type_pair.hxx"
#include "typedefs.hxx"

#include <utility>

#if __cplusplus <= 201103 && !defined VTMPL_ENABLE_CPP1Y

	#error \
	This file uses C++1Y-features (relaxed constraints on constexpr-functions). \
	If your compiler supports those features (via a flag such as -std=c++1y / -std=c++14), define the macro \
	VTMPL_ENABLE_CPP1Y.

#endif


namespace vtmpl
{

	template< typename String >
	constexpr std::pair<std::uintmax_t, size_type> parse_unsigned( size_type pos = 0 )
	{
		std::uintmax_t rval = 0;
		while( pos < String::length && isdigit(String::array[pos]) )
		{
			rval *= 10;
			rval += String::array[pos] - '0';
			++pos;
		}

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

		auto pair = parse_unsigned<String>(pos);

		if( negative )
			pair.first *= -1;

		return pair;
	}

}

#endif // PARSERS_HXX_INCLUDED
