/* Copyright (c) Arcoth, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef TYPE_LIST_HXX_INCLUDED
#define TYPE_LIST_HXX_INCLUDED

#include "index_list.hxx"
#include "typedefs.hxx"
#include <tuple>

namespace vtmpl
{
	template<typename ... Types>
	struct type_list : identity<type_list<Types...>>
	{
		static size_type constexpr length = sizeof...(Types);
		using std_tuple = std::tuple<Types...>;
	};

	template< typename, typename > struct find;
	template< typename to_find, typename ... Args >
	struct find<type_list<Args...>, to_find> :
		size_< value_list<bool, std::is_same<Args, to_find>::value...>::find(true) > {};

	template< typename List, std::size_t i >
	using type_list_at = typename std::tuple_element<i, typename List::std_tuple>::type;

	template< typename List >
	using back = type_list_at<List, List::length-1>;

	// Use this function inside a decltype-specifier to retrieve the deduced template arguments
	template<typename... Args>
	type_list<eval<std::decay<Args>>...> arg_type_list( Args&&... );

	/// concat_type_lists //////////////////////////////////////////////////////////

	template<typename, typename> struct concat;

	template<typename ... first,
			 typename ... second>
	struct concat<type_list<first...>, type_list<second...>> : type_list<first..., second...> {};

	/// replace-last //////////////////////////////////////////////////////////

	template<typename, typename> struct replace_last;
	template<typename New, typename First, typename... Types>
	struct replace_last<New, type_list<First, Types...>> :
	    concat<type_list<First>, typename replace_last<New, type_list<Types...>>::type> {};
	template<typename New, typename First>
	struct replace_last<New, type_list<First>> : type_list<New> {};

	/// sub-list //////////////////////////////////////////////////////////

	template< typename List, std::size_t pos, std::size_t len = npos,
	          typename = eval<make_index_list< min(len, List::length - pos) >> >
	struct sub_type_list;

	template< typename List, std::size_t pos, std::size_t len,
	          index_type ... indices >
	struct sub_type_list<List, pos, len, index_list<indices...>> :
		type_list<type_list_at<List, pos + indices>...> {};

	/// remove //////////////////////////////////////////////////////////

	template< typename List, typename R, typename NewList = type_list<> > struct remove;

	template< typename R, typename T, typename ... Ts, typename ... newTs >
	struct remove<R, type_list<T, Ts...>, type_list<newTs...>> : remove<R, type_list<Ts...>, type_list<newTs..., T>> {};

	template< typename R, typename ... Ts, typename L >
	struct remove<R, type_list<R, Ts...>, L> : remove<R, type_list<Ts...>, L> {};

	template< typename R, typename L >
	struct remove<R, type_list<>, L> : L {};

}


#endif // TYPE_LIST_HXX_INCLUDED
