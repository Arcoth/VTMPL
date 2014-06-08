/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef TIME_HXX_INCLUDED
#define TIME_HXX_INCLUDED

#include "const_string.hxx"
#include "parsers.hxx"

namespace vtmpl
{

	template< typename format = VTMPL_STRING("SsMmHh") >
	constexpr std::uintmax_t time()
	{
		using str = VTMPL_STRING( __TIME__ );

		constexpr auto Hh = parse_unsigned<str>().first;
		constexpr auto Mm = parse_unsigned<str>(3).first;
		constexpr auto Ss = parse_unsigned<str>(6).first;

		std::uintmax_t rval = 0;

		for( auto c : format::array )
		{
			rval *= 10;
			switch(c)
			{
				case 'H': rval += Hh / 10; break;
				case 'h': rval += Hh % 10; break;
				case 'M': rval += Mm / 10; break;
				case 'm': rval += Mm % 10; break;
				case 'S': rval += Ss / 10; break;
				case 's': rval += Ss % 10; break;

				default:
					VTMPL_ASSERT(0, "Invalid time format string!");
			}
		}

		return rval;
	}

}

#endif // TIME_HXX_INCLUDED
