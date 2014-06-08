/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef ALGORITHMS_HXX_INCLUDED
#define ALGORITHMS_HXX_INCLUDED

#include "value_list.hxx"
#include "index_list.hxx"
#include "type_list.hxx"
#include "utility.hxx"

namespace vtmpl
{

	template< typename List,
	          typename OutputIterator >
	void copy( OutputIterator out )
	{
		auto first = std::begin(List::array);
		auto last  = std::end(List::array);
		while( first != last )
			*out++ = *first++;
	}

	template <typename str,
	          size_type pos,
	          size_type len = npos,
	          typename = eval<make_index_list<min(len, str::length - pos)>>> struct sub_list;

	template <typename Type, Type ... args,
	          size_type pos,
	          size_type len,
	          index_type... indices>
	struct sub_list<value_list<Type, args...>,
	                pos, len,
	                index_list<indices...>> :
		value_list<Type, value_list<Type, args...>::array[pos + indices]...> {};

	/// split_at: Splits the list into to sublists as specified by the position. The value at position pos is in the first list.

	template <typename list,
	          size_type pos,
	          bool keep_delim = true> struct split_at;

	template <typename val_t,
	          val_t ... values,
	          size_type pos,
	          bool keep_delim>
	struct split_at<value_list<val_t, values...>,
	                pos,
	                keep_delim> :
		type_list< eval<sub_list<value_list<val_t, values...>, 0, pos>>,
	                 eval<sub_list<value_list<val_t, values...>, pos + keep_delim, sizeof...(values) - pos - keep_delim>> > {};

	/// concat/concat_3

	template <typename, typename          > struct concat;
	template <typename, typename, typename> struct concat_3;

	template < typename val_t,
	           val_t ... first,
	           val_t ... second >
	struct concat<value_list<val_t, first...>,
	               value_list<val_t, second...>> :
		value_list<val_t, first..., second...> {};

	// to reduce recursion
	template < typename val_t,
	           val_t ... first,
	           val_t ... second,
	           val_t ... third >
	struct concat_3<value_list<val_t, first...>,
			    value_list<val_t, second...>,
			    value_list<val_t, third...>> :
		value_list<val_t, first..., second..., third...> {};

	/// replace

	template <typename list,
	          size_type pos,
	          typename list::value_type new_val>
	struct replace;

	template <typename val_t, val_t... values,
	          size_type pos,
	          val_t new_val>
	struct replace<value_list<val_t, values...>,
	               pos,
	               new_val> :
		concat_3< eval<sub_list<value_list<val_t, values...>, 0, pos>>,
	               value_list<val_t, new_val>,
	               eval<sub_list<value_list<val_t, values...>, pos + 1, value_list<val_t, values...>::length - pos - 1>> > {};

	/// remove_if_not

	template< typename T,
	          typename,
	          typename = value_list<typename T::value_type> >
	struct remove_if_not;

	template< typename T,
	          T... seq,
	          T... not_erase,
	          T... so_far >
	struct remove_if_not< value_list<T, seq...>,
	                      value_list<T, not_erase...>,
	                      value_list<T, so_far...> >
	{
		using split_pair = split_at<value_list<T, seq...>, sizeof...(seq)/2>;

		using first  = remove_if_not< typename split_pair::first , value_list<T, not_erase...>, value_list<T, so_far...> >;
		using second = remove_if_not< typename split_pair::second, value_list<T, not_erase...>, value_list<T, so_far...> >;

		using type = eval<concat<eval<first>, eval<second>>>;
	};

	template< typename T,
	          T seq,
	          T... not_erase,
	          T... so_far >
	struct remove_if_not< value_list<T, seq>,
	                      value_list<T, not_erase...>,
	                      value_list<T, so_far...> >  :  cond< value_list<T, not_erase...>::find(seq) != npos,
	                                                           value_list<T, seq>, value_list<T> > {};
	template< typename T,
		    T... not_erase,
		    T... so_far >
	struct remove_if_not< value_list<T>,
	                      value_list<T, not_erase...>,
	                      value_list<T, so_far...> >  :  value_list<T, so_far...> {};

	/// find_first_not_of

	template <typename, typename, size_type = 0, typename=void> struct find_first_not_of;

	template< typename List, typename Check, size_type pos >
	struct find_first_not_of<List, Check, pos, requires<Check::find(List::array[pos]) != npos && pos != List::length-1>> :
		find_first_not_of<List, Check, pos+1> {};

	template< typename List, typename Check, size_type pos >
	struct find_first_not_of<List, Check, pos, requires<Check::find(List::array[pos]) != npos && pos == List::length-1>>
	{
		sconst auto value = npos;
	};

	template< typename List, typename Check, size_type pos >
	struct find_first_not_of<List, Check, pos, requires<Check::find(List::array[pos]) == npos>>
	{
		sconst auto value = pos;
	};

	/// transform: Use to apply a function to a list of values

	template <typename List,
	          template<typename V, V> class,
	          typename = eval<make_index_list<List::length>>> struct transform;

	template <typename V,
	          V... values,
	          template<typename FV, FV> class function,
	          index_type... enums>
	struct transform<value_list<V, values...>, function, index_list<enums...>> :
		index_list< function<V, value_list<V, values...>::array[enums]>::value... > {};

	/// generate: Use to generate a list with a function which takes an index as an argument

	template <size_type N,
	          template<typename T, T> class generator,
	          typename = eval<make_index_list<N>>> struct generate;

	template <size_type N,
	          template<typename FV, FV> class generator,
	          typename V,
	          V... values>
	struct generate<N, generator, value_list<V, values...>> :
		value_list< V, generator<V, values>::value... > {};

	/// predefined function objects (for transform):

	namespace functions
	{
		#define DEFINE_FO( name, ... )                                             \
			template< typename T, T a>                                           \
			struct name                                                          \
			{                                                                    \
				template<typename ValueT, typename ValueT::value_type b = ValueT::value>                                                  \
				struct function : std::integral_constant<T, (__VA_ARGS__)> {}; \
			}


		DEFINE_FO( add     ,  b + a );
		DEFINE_FO( bit_xor ,  b ^ a );
		DEFINE_FO( bit_and ,  b & a );
		DEFINE_FO( bit_or  ,  b | a );
		DEFINE_FO( multiply,  b * a );
		DEFINE_FO( modulo  ,  b % a );


		#undef DEFINE_FO
		#define DEFINE_FO( name, ... ) \
			template<typename T, T a> struct name : std::integral_constant<T, (__VA_ARGS__)> {}

		DEFINE_FO( square , a*a );
		DEFINE_FO( negate , -a );
		DEFINE_FO( bit_not, ~a );

		#undef DEFINE_FO

		template< typename T, T(*func)( T ) >
		struct from_function_ptr
		{
			template< typename V, V b >
			struct function : std::integral_constant<V, func(b)> {};
		};
	}

	/// rtrim: cuts of all values after a specific one

	template<typename List, typename List::value_type = typename List::value_type{}> struct rtrim;

	template<typename Type, Type ... args, Type to_find>
	struct rtrim<value_list<Type, args...>, to_find> :
		sub_list< value_list<Type, args...>, 0, value_list<Type, args...>::find(to_find) > {};
}

#endif // ALGORITHMS_HXX_INCLUDED
