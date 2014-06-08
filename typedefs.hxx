/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef TYPEDEFS_HXX_INCLUDED
#define TYPEDEFS_HXX_INCLUDED

#include <type_traits>
#include <cstdint>
#include <limits>

namespace vtmpl
{

	template<typename T = void>
	struct identity
	{
		using type = T;
	};

	using size_type = unsigned;

	using index_type = int;

	template<typename T>
	using eval = typename T::type;

	template<bool B, typename T, typename F>
	using cond = eval<std::conditional<B, T, F>>;

	template<bool Val>
	using bool_ = std::integral_constant<bool, Val>;

	template<std::intmax_t Val>
	using int_ = std::integral_constant<std::intmax_t, Val>;

	template<std::uintmax_t Val>
	using uint_ = std::integral_constant<std::uintmax_t, Val>;

	template<size_type Val>
	using size_ = std::integral_constant<size_type, Val>;

	constexpr size_type npos = std::numeric_limits<size_type>::max();

	template<bool C>
	using requires = eval<std::enable_if<C>>;

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

	#define sconst static constexpr

}

#endif // TYPEDEFS_HXX_INCLUDED
