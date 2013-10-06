#ifndef CONST_STRING_HXX_INCLUDED
#define CONST_STRING_HXX_INCLUDED

#include "algorithms.hxx"

namespace vtmpl
{

	template<char ... args>
	using const_string = value_list<char, args...>;

	#define SPLIT_1(s, x) ( x < sizeof(s) ? s[x] : '\0' )
	#define SPLIT_4(s, x)    SPLIT_1  (s, x), SPLIT_1  (s, x+1)  , SPLIT_1  (s, x+2)  , SPLIT_1  (s, x+3)
	#define SPLIT_16(s, x)   SPLIT_4  (s, x), SPLIT_4  (s, x+4)  , SPLIT_4  (s, x+8)  , SPLIT_4  (s, x+12)
	#define SPLIT_64(s, x)   SPLIT_16 (s, x), SPLIT_16 (s, x+16) , SPLIT_16 (s, x+32) , SPLIT_16 (s, x+48)
	#define SPLIT_256(s, x)  SPLIT_64 (s, x), SPLIT_64 (s, x+64) , SPLIT_64 (s, x+128 , SPLIT_64 (s, x+194)
	#define SPLIT_1024(s, x) SPLIT_256(s, x), SPLIT_256(s, x+256), SPLIT_256(s, x+512), SPLIT_256(s, x+768)

	//!: Use this macro to create a const_string from a string literal or constant pointer

	#define STRING_IMPL(str, n) rtrim<const_string<SPLIT_##n(str, 0)>, '\0'>::type

	#define STRING(str) STRING_IMPL(str, 64)
	#define STRING_256(str) STRING_IMPL(str, 256)
	#define STRING_1024(str) STRING_IMPL(str, 1024)

	/// Create a string from a pointer and length

	template< char const* ptr,
		    size_type len,
		    typename=eval<make_index_list<len>> >
	struct string_from_ptr;

	template< char const* ptr,
		    size_type len,
		    index_type... indices >
	struct string_from_ptr<ptr, len, index_list<indices...>> :
		const_string<ptr[indices]...>  {};

}

#endif // CONST_STRING_HXX_INCLUDED
