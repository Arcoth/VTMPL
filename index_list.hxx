#ifndef INDEX_LIST_HXX_INCLUDED
#define INDEX_LIST_HXX_INCLUDED

#include "identity.hxx"
#include "typedefs.hxx"
#include "value_list.hxx"

#include <type_traits>

namespace vtmpl
{

	template<index_type ... args>
	using index_list = value_list<index_type, args...>;

	template <typename, typename> struct multiply;
	template <index_type... indices, index_type... tail>
	struct multiply<index_list<indices...>,
	                index_list<tail...   >> : index_list<indices..., (sizeof...(indices)+indices)...,
	                                                                 (2*sizeof...(indices)+indices)...,
	                                                                 (3*sizeof...(indices)+indices)...,
														 (4*sizeof...(indices)+tail)...> {};

	//! make_index_list: Essential function to generate a list of numbers, used in many other functions to avoid recursion.
	// Generates a list of natural numbers. make_index_list<4> -> {0, 1, 2, 3}, for example, and make_index_list<23510> -> {0, 1, 2, 3, 4, ..., 23509}.

	template <index_type N>
	struct make_index_list :
		multiply< typename make_index_list<N/4>::type,
		          typename make_index_list<N%4>::type > {};

	template <> struct make_index_list<3> : index_list<0, 1, 2> {};
	template <> struct make_index_list<2> : index_list<0, 1> {};
	template <> struct make_index_list<1> : index_list<0> {};
	template <> struct make_index_list<0> : index_list<> {};


}

#endif // INDEX_LIST_HXX_INCLUDED
