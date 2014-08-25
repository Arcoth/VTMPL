#include "index_list.hxx"
#include "string.hxx"
#include "algorithms.hxx"
#include "type_list.hxx"
#include "random.hxx"
#include "time.hxx"

#include <algorithm>
#include <iterator>
#include <iostream>

using namespace vtmpl;

template< typename Str, typename ... matches >
struct one_of :
	bool_< find<type_list<matches...>, Str >::value != npos > {};

template< typename Str >
struct or_matcher
{
	using splitted = split_at<Str, Str::find('|'), false>;

	template< typename Str2 >
	struct matches :
		bool_< find<type_list<type_list_at<splitted, 0>,
		                      type_list_at<splitted, 1>>, Str2 >::value != npos > {};
};

constexpr unsigned rad( unsigned b )
{
	unsigned const original_b = b+1;
	unsigned res = 1;
	for( unsigned div = 2; div < original_b; ++div )
		if( b % div == 0 )
		{
			res *= div;
			do
				b /= div;
			while( b % div == 0 );
		}

	return res;
}

/*int main()
{
	using expr = VTMPL_STRING("a|b");

	static_assert( find<type_list<char, int>, int>::value == 1 , "" );

	static_assert( or_matcher<expr>::matches<VTMPL_STRING("a")>::value , "" );
	static_assert( !or_matcher<expr>::matches<VTMPL_STRING("foo")>::value , "" );

	std::cout << "Rads of first 30 numbers: ";
	copy<generate<30, functions::from_function_ptr<unsigned, &rad>>>( std::ostream_iterator<unsigned>(std::cout, " ") );


	std::cout << "\nTwenty pseudo-random numbers: ";
	using list = generate_recursive< 20, functions::from_function_ptr<std::uintmax_t, &rand>,
	                                 value_list<std::uintmax_t, time()> >;

	copy< transform<eval<list>, functions::modulo<std::uintmax_t, 10>> >( std::ostream_iterator<std::uintmax_t>(std::cout, " ") );
}*/
