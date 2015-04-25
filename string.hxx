/* Copyright (c) Arcoth, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef CONST_STRING_HXX_INCLUDED
#define CONST_STRING_HXX_INCLUDED

#include "algorithms.hxx"

namespace vtmpl
{

	template <char ... args>
	using string = value_list<char, args...>;

	template <wchar_t ... args>
	using wstring = value_list<wchar_t, args...>;

}

//!: Use the macro VTMPL_STRING to create a list from an array object (a string literal designates an array-object).

# ifdef STRING_LITERAL_OPERATOR_TEMPLATES

	template< typename CharT, CharT... chs >
	vtmpl::value_list<CharT, chs...> operator"" _vtmpl_const_string_udl();

#	define VTMPL_STRING_IMPL(str) decltype( str##_vtmpl_const_string_udl )
#	define VTMPL_STRING(str) VTMPL_STRING_IMPL(str)
#	define VTMPL_STRING_256(str)  VTMPL_STRING(str)
#	define VTMPL_STRING_1024(str) VTMPL_STRING(str)
#
# else
#
#	define VTMPL_STRING_IMPL(str, n) vtmpl::rtrim<vtmpl::value_list<decltype(*str), VTMPL_SPLIT_##n(str, 0, VTMPL_ARRAY_SPLIT)>>::type
#
#	define VTMPL_STRING(str)      VTMPL_STRING_IMPL(str, 64  )
#	define VTMPL_STRING_256(str)  VTMPL_STRING_IMPL(str, 256 )
#	define VTMPL_STRING_1024(str) VTMPL_STRING_IMPL(str, 1024)
#
# endif

#endif // CONST_STRING_HXX_INCLUDED
