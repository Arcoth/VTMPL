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

	template<typename T>
	using eval = typename T::type;

	using size_type = unsigned long;

	using index_type = long;

	template<bool B, typename T, typename F>
	using cond = eval<std::conditional<B, T, F>>;

	template<bool B, typename T = void>
	using requires = eval< std::enable_if<B, T> >;

	template<bool Val>
	using bool_ = std::integral_constant<bool, Val>;

	template<std::intmax_t Val>
	using int_ = std::integral_constant<std::intmax_t, Val>;

	template<std::uintmax_t Val>
	using uint_ = std::integral_constant<std::uintmax_t, Val>;

	template<size_type Val>
	using size_ = std::integral_constant<size_type, Val>;

	constexpr size_type npos = std::numeric_limits<size_type>::max();

}

# define VTMPL_SCONST static constexpr

# define IS_CPP1Y_OR_GREATER (__cplusplus > 201103)
#
# ifndef VTMPL_RELAX_CONSTEXPR_FUNC
#     // GCC does not support Relaxing requirements on constexpr functions yet
#	define VTMPL_RELAX_CONSTEXPR_FUNC   (1 || IS_CPP1Y_OR_GREATER && (!defined __GNUC__ || __GNUC__ > 4))
# endif
#
# ifndef STRING_LITERAL_OPERATOR_TEMPLATES
#	define STRING_LITERAL_OPERATOR_TEMPLATES   IS_CPP1Y_OR_GREATER
# endif
#
# undef IS_CPP1Y_OR_GREATER

#endif // TYPEDEFS_HXX_INCLUDED
