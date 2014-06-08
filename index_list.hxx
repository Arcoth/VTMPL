/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef INDEX_LIST_HXX_INCLUDED
#define INDEX_LIST_HXX_INCLUDED

#include "typedefs.hxx"
#include "value_list.hxx"

#include <type_traits>

namespace vtmpl
{

	/// Credit for this binary recursion approach goes to camper @ http://www.c-plusplus.de/

	template<index_type ... args>
	using index_list = value_list<index_type, args...>;

	template <typename, typename> struct multiply;
	template <index_type... indices, index_type... tail>
	struct multiply<index_list<indices...>,
	                index_list<tail...   >> : index_list<indices..., (sizeof...(indices)+indices)...,
	                                                                 (2*sizeof...(indices)+indices)...,
	                                                                 (3*sizeof...(indices)+indices)...,
	                                                                 (4*sizeof...(indices)+tail)...> {};

	//! make_index_list: Essential function to generate a list of numbers, used in many other functions to avoid explicit and linear recursion.
	/* Generates a list of natural numbers. make_index_list<4> -> {0, 1, 2, 3}, for example, and make_index_list<235> -> {0, 1, 2, 3, 4, ..., 234}.
	   This definition is also more efficient (in terms of computational complexity) than the libstdc++-implementation, which uses linear instead of binary recursion.
	   So stick to this instead of std::index_sequence and std::make_index_sequence */

	template <index_type N>
	struct make_index_list :
		multiply< eval<make_index_list<N/4>>,
		          eval<make_index_list<N%4>> > {};

	template <> struct make_index_list<3> : index_list<0, 1, 2> {};
	template <> struct make_index_list<2> : index_list<0, 1> {};
	template <> struct make_index_list<1> : index_list<0> {};
	template <> struct make_index_list<0> : index_list<> {};


}

#endif // INDEX_LIST_HXX_INCLUDED
