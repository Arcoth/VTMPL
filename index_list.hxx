/* Copyright (c) Arcoth, 2013-2015.

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef INDEX_LIST_HXX_INCLUDED
#define INDEX_LIST_HXX_INCLUDED

#include "typedefs.hxx"
#include "value_list.hxx"

#include <type_traits>

namespace vtmpl
{

	template<index_type ... args>
	using index_list = value_list<index_type, args...>;

	template <typename, typename> struct contiguously_quadruple;
	template <typename V, V... indices, V... tail>
	struct contiguously_quadruple<value_list<V, indices...>,
	                              value_list<V, tail...   >> : value_list<V, indices..., (sizeof...(indices)+indices)...,
	                                                                                   (2*sizeof...(indices)+indices)...,
	                                                                                   (3*sizeof...(indices)+indices)...,
	                                                                                   (4*sizeof...(indices)+tail)...> {};

	//! make_contiguous_list: Essential function to generate a list of numbers, used in many other functions to avoid explicit and/or linear recursion.
	/* Generates a list of natural numbers. make_index_list<4> -> {0, 1, 2, 3}, for example, and make_index_list<235> -> {0, 1, 2, 3, 4, ..., 234}.
	   This definition is also more efficient (in terms of computational complexity) than - for instance - the libstdc++-implementation, which uses linear instead of binary recursion.
	   So stick to this instead of std::index_sequence and std::make_index_sequence until a compiler intrinsic turns up */

	template <typename V, size_type N>
	struct make_contiguous_list :
		contiguously_quadruple< eval<make_contiguous_list<V, N/4>>,
		                        eval<make_contiguous_list<V, N%4>> > {};

	template <typename V> struct make_contiguous_list<V, 3> : value_list<V, 0, 1, 2> {};
	template <typename V> struct make_contiguous_list<V, 2> : value_list<V, 0, 1> {};
	template <typename V> struct make_contiguous_list<V, 1> : value_list<V, 0> {};
	template <typename V> struct make_contiguous_list<V, 0> : value_list<V> {};

	template <size_type N>
	using make_index_list = eval< make_contiguous_list<index_type, N> >;

	// make_list_val: Creates a list of N occurences of the value val

	template <typename V, size_type N, V val>
	struct make_list_val :
		concat< eval<make_list_val<V, N/2, val>>, eval<make_list_val<V, N/2, val>> > {};

	template <typename V, V val>
	struct make_list_val<V, 1, val> : value_list<V, val> {};



	/// create a value list from an array pointer and a length

	template <typename T, T const* ptr,
	          size_type len,
	          typename = make_index_list<len>>
	struct list_from_ptr;

	template< typename T, T const* ptr,
	          size_type len,
	          index_type... indices >
	struct list_from_ptr<T, ptr, len, index_list<indices...>> :
		value_list<T, ptr[indices]...>  {};
}

#endif // INDEX_LIST_HXX_INCLUDED
