/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef ALGORITHMS_HXX_INCLUDED
#define ALGORITHMS_HXX_INCLUDED

#include "index_list.hxx"
#include "type_list.hxx"
#include "utility.hxx"

namespace vtmpl
{

	template< typename List,
	          typename OutputIterator >
	void copy( OutputIterator out )
	{
		for( auto c : eval<List>::array )
			*out++ = c;
	}

	/// sub_list: Creates a sub-list of a given value_list, given start pos and length

	template <typename List,
	          size_type pos,
	          size_type len = npos,
	          typename = eval<make_index_list<min(len, List::length - pos)>>> struct sub_list;

	template <typename List,
	          size_type pos,
	          size_type len,
	          index_type... indices>
	struct sub_list<List, pos, len,
	                index_list<indices...>> :
		list_with_type<List, List::array[pos + indices]...> {};

	/// split_at: Splits the list into to sublists as specified by the position. The value at position pos is in the first list.

	template <typename List,
	          size_type pos,
	          bool keep_separator = true>
	struct split_at :
		type_list< eval<sub_list<List, 0, pos>>,
	                 eval<sub_list<List, pos + !keep_separator>> > {};

	// list operations

	template <typename List, size_type pos>
	struct erase
	{
		using pair = eval< split_at<List, pos, false> >;

		using type = eval< concat<type_list_at<pair, 0>, type_list_at<pair, 1>> >;
	};

	template< typename List, typename List::value_type V >
	using push_back = eval< concat<List, list_with_type<List, V>> >;

	template <typename List>
	using pop_back  = eval< sub_list< List, 0, List::length-1> >;

	namespace detail {
		template <typename List, size_type pos, typename List::value_type value, bool keep>
		struct insert
		{
			using pair = eval< split_at<List, pos, keep> >;

			using type = eval< concat_3<typename pair::first,
							    list_with_type<List, value>,
							    typename pair::second> >;
		};
	}

	template <typename List, size_type pos, typename List::value_type value>
	using assign = eval< detail::insert<List, pos, value, false> >;
	template <typename List, size_type pos, typename List::value_type value>
	using insert = eval< detail::insert<List, pos, value, true> >;

	/// find_first_not_of

	#if VTMPL_RELAX_CONSTEXPR_FUNC

	template <typename List, typename CheckList>
	VTMPL_SCONST size_type find_first_not_of( size_type start_pos = 0 )
	{
		for (size_type s = start_pos; s != List::length; ++s )
			if (CheckList::find(List::array[s]) == npos)
				return s;

		return npos;
	}

	template <typename List, typename CheckList>
	VTMPL_SCONST size_type find_first_of( size_type start_pos = 0 )
	{
		for (size_type s = start_pos; s != List::length; ++s )
			if (CheckList::find(List::array[s]) != npos)
				return s;

		return npos;
	}

	#endif

	/// transform: Use to apply a function to a list of values

	template <typename, class> struct transform;

	template <typename V, V... values,
	          class function>
	struct transform<value_list<V, values...>, function> :
		value_list< V, function()(values)... > {};

	/// generate: Use to generate a list with a function which takes an index as an argument

	template <size_type N, class generator>
	using generate = transform<eval<make_index_list<N>>, generator>;

	/// rtrim: cuts of all values after a specific one

	template<typename List, typename List::value_type to_find = typename List::value_type()>
	using rtrim = eval< sub_list< List, 0, List::find(to_find) > >;

	/// generate_recursive: Use to generate a list with a function which takes the preceding list element as an argument to generate the next one

	template< size_type N, class Generator, typename List >
	struct generate_recursive :
		generate_recursive< N-1, Generator, push_back<List, Generator()(List::back())> > {};

	template< size_type N, class Generator, typename T >
	struct generate_recursive<N, Generator, value_list<T>> :
		generate_recursive<N-1, Generator, value_list<T, Generator()( (T)0 )>> {};

	template< class Generator, typename List >
	struct generate_recursive<0, Generator, List> : List {};

	/// predefined function objects

	namespace functions
	{
		#define DEFINE_UFO( name, ... ) \
			struct name \
			{ \
				template<typename U> \
				constexpr auto operator()(U a) VTMPL_AUTO_RETURN(__VA_ARGS__) \
			};

		#define DEFINE_FO( name, ... ) \
			struct name \
			{ \
				template<typename T, typename U> \
				constexpr auto operator()(T a, U b) VTMPL_AUTO_RETURN(__VA_ARGS__) \
			};


		DEFINE_FO( plus      , a + b )
		DEFINE_FO( bit_xor   , a ^ b )
		DEFINE_FO( bit_and   , a & b )
		DEFINE_FO( bit_or    , a | b )
		DEFINE_FO( multiplies, a * b )
		DEFINE_FO( divides   , a / b )
		DEFINE_FO( modulus   , a % b )


		DEFINE_UFO( square , a*a )
		DEFINE_UFO( negate , -a )
		DEFINE_UFO( bit_not, ~a )

		template< typename T, T(*func)( T ) >
		DEFINE_UFO( from_function_ptr, func(a) )

		template <typename FO, typename Val>
		DEFINE_UFO( bind1st, FO()(Val::value, a) )
		template <typename FO, typename Val>
		DEFINE_UFO( bind2nd, FO()(a, Val::value) )

		template <class first, class... functions>
		DEFINE_UFO( chain, chain<functions...>()( first()(a) ) )
		template <class first>
		DEFINE_UFO( chain<first>, first()(a) )

		#undef DEFINE_FO
		#undef DEFINE_UFO
	}

}

#endif // ALGORITHMS_HXX_INCLUDED
