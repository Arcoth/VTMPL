/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef RANDOM_HXX_INCLUDED
#define RANDOM_HXX_INCLUDED

#include "parsers.hxx"
#include "time.hxx"

namespace vtmpl
{

	/// POSIX drand48
	template< std::uintmax_t c = 25214903917,
	          std::uintmax_t a = 11,
	          std::uintmax_t m = (1ull << 48) >
	constexpr std::uintmax_t rand48( std::uintmax_t state = time() )
	{
		return (state * c + a) % m;
	}


	//! Credit for this multiply-with-carrier PRNG goes to Volkard Henkel (volkard at http://www.c-plusplus.de)
	template< std::uintmax_t a = 4294967118,
		    std::uintmax_t mask = 0xffffffff,
		    int shift = 32 >
	constexpr std::uintmax_t rand( std::uintmax_t x )
	{
		return a*(x & mask)+(x>>shift);
	}

}

#endif // RANDOM_HXX_INCLUDED
