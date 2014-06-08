/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef CONST_STRING_HXX_INCLUDED
#define CONST_STRING_HXX_INCLUDED

#include "algorithms.hxx"

namespace vtmpl
{

	template<char ... args>
	using const_string = value_list<char, args...>;

	/// Create a string from a pointer and length

	template< char const* ptr,
	          size_type len,
	          typename = eval<make_index_list<len>> >
	struct string_from_ptr;

	template< char const* ptr,
	          size_type len,
	          index_type... indices >
	struct string_from_ptr<ptr, len, index_list<indices...>> :
		const_string<ptr[indices]...>  {};

}


#ifdef STRING_LITERAL_OPERATOR_TEMPLATES

	template< typename CharT, CharT... chs >
	vtmpl::value_list<CharT, chs...> operator"" _vtmpl_const_string_udl();

	#define VTMPL_STRING_IMPL(str) decltype( str##_vtmpl_const_string_udl )
	#define VTMPL_STRING(str) VTMPL_STRING_IMPL(str)

#else

	#define VTMPL_SPLIT_1(s, x) ( x < sizeof(s) ? s[x] : '\0' )
	#define VTMPL_SPLIT_4(s, x) VTMPL_SPLIT_1  (s, x), VTMPL_SPLIT_1  (s, x+1)  , VTMPL_SPLIT_1  (s, x+2)  , VTMPL_SPLIT_1  (s, x+3)
	#define VTMPL_SPLIT_16(s, x) VTMPL_SPLIT_4  (s, x), VTMPL_SPLIT_4  (s, x+4)  , VTMPL_SPLIT_4  (s, x+8)  , VTMPL_SPLIT_4  (s, x+12)
	#define VTMPL_SPLIT_64(s, x) VTMPL_SPLIT_16 (s, x), VTMPL_SPLIT_16 (s, x+16) , VTMPL_SPLIT_16 (s, x+32) , VTMPL_SPLIT_16 (s, x+48)
	#define VTMPL_SPLIT_256(s, x) VTMPL_SPLIT_64 (s, x), VTMPL_SPLIT_64 (s, x+64) , VTMPL_SPLIT_64 (s, x+128), VTMPL_SPLIT_64 (s, x+194)
	#define VTMPL_SPLIT_1024(s, x) VTMPL_SPLIT_256(s, x), VTMPL_SPLIT_256(s, x+256), VTMPL_SPLIT_256(s, x+512), VTMPL_SPLIT_256(s, x+768)

	//!: Use this macro to create a const_string from a string literal or constant pointer

	#define VTMPL_STRING_IMPL(str, n) vtmpl::rtrim<vtmpl::const_string<VTMPL_SPLIT_##n(str, 0)>>::type

	#define VTMPL_STRING(str) VTMPL_STRING_IMPL(str, 64)
	#define VTMPL_STRING_256(str) VTMPL_STRING_IMPL(str, 256)
	#define VTMPL_STRING_1024(str) VTMPL_STRING_IMPL(str, 1024)

#endif

#endif // CONST_STRING_HXX_INCLUDED
