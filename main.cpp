#include "index_list.hxx"
#include "const_string.hxx"
#include "algorithms.hxx"
#include "type_list.hxx"

#include <algorithm>
#include <iterator>
#include <iostream>

using namespace vtmpl;

template< typename Str, typename ... matches >
struct one_of :
	std::integral_constant<bool, find<type_list<matches...>, Str >::value != npos> {};

template< typename Str >
struct or_matcher
{
	using splitted = split_at<Str, Str::find('|'), false>;

	template< typename Str2 >
	struct matches :
		std::integral_constant<bool,
		                       find<type_list<get<splitted, 0>, get<splitted, 1>>, Str2 >::value != npos> {};
};

int main()
{
	using expr = STRING("a|b");

	static_assert( find<type_list<char, int>, int>::value == 1 , "" );

	static_assert( or_matcher<expr>::matches<STRING("a")>::value , "" );
	static_assert( !or_matcher<expr>::matches<STRING("foo")>::value , "" );
}
