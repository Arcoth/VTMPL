/* Copyright (c) Robert Haberlach, 2013-2014.

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

	#define VTMPL_ASSERT( B, MSG ) ( B? 0 : throw ::std::invalid_argument{MSG})

	#define VTMPL_DEFINE_FORWARDER(name, impl)              \
		template <typename... Args>                              \
		constexpr auto name( Args&&... args )                              \
		VTMPL_AUTO_RETURN( (impl)(::std::forward<Args>(args)...) )

	#define VTMPL_AUTO_RETURN(...) -> decltype(__VA_ARGS__) {return (__VA_ARGS__);}

}

#endif // UTILITY_HXX_INCLUDED
