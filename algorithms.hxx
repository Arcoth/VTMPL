#ifndef ALGORITHMS_HXX_INCLUDED
#define ALGORITHMS_HXX_INCLUDED

#include "value_list.hxx"
#include "index_list.hxx"
#include "type_pair.hxx"

namespace vtmpl
{

	template <typename,
	          size_type,
	          size_type len,
	          typename = eval<make_index_list<len>>> struct sub_list;

	template <typename Type, Type ... args,
	          size_type pos,
	          size_type len,
	          index_type... indices>
	struct sub_list<value_list<Type, args...>,
	                pos, len,
	                index_list<indices...>> :
		value_list<Type, value_list<Type, args...>::arr[pos + indices]...> {};

	/// concat: Use to merge two lists.

	template <typename, typename> struct concat;

	template < typename val_t,
	           val_t ... first,
	           val_t ... second >
	struct concat<value_list<val_t, first...>,
	              value_list<val_t, second...>> : value_list<val_t, first..., second...> {};

	/// transform: Use to apply a function to a list of indices

	template <typename T,
	          template<index_type> class,
	          typename = eval<make_index_list<T::length>>> struct transform;

	template <index_type... indices,
	          template<index_type> class function,
	          index_type... enums>
	struct transform<index_list<indices...>, function, index_list<enums...>> :
		index_list< function<index_list<indices...>::arr[enums]>::value... > {};

	/// generate: Use to generate a list with a function which takes an index as an argument

	template <size_type N,
	          template<size_type> class generator,
	          typename = eval<make_index_list<N>>> struct generate;

	template <size_type N,
	          template<size_type> class generator,
	          index_type... indices>
	struct generate<N, generator, index_list<indices...>> :
		index_list< generator<indices>::value... > {};

	/// predefined function objects (for transform):

	namespace functions
	{
		#define DEFINE_FO( name, ... )                                                  \
			template<index_type a>                                                      \
			struct name                                                                 \
			{                                                                           \
				template<index_type b>                                                  \
				struct function : std::integral_constant<index_type, (__VA_ARGS__)> {}; \
			}

		DEFINE_FO(add, b + a);
		DEFINE_FO(xor_, b xor a);
		DEFINE_FO(multiply, b * a);
		DEFINE_FO(modulo, b % a);


		#undef DEFINE_FO
		#define DEFINE_FO( name, ... )                                                  \
			template<index_type a> struct name : std::integral_constant<index_type, (__VA_ARGS__)> {}

		DEFINE_FO( square, a*a );
		DEFINE_FO( invert, -a );

		#undef DEFINE_FO
	}

	/// split_at: Splits the list into to sublists as specified by the position. The value at position pos is in the first list.

	template <typename list,
	          size_type pos> struct split_at;

	template <typename val_t,
	          val_t ... values,
	          size_type pos>
	struct split_at<value_list<val_t, values...>,
	                pos> :
		type_pair< eval<sub_list<value_list<val_t, values...>, 0, pos>>,
	                 eval<sub_list<value_list<val_t, values...>, pos, sizeof...(values) - pos>> > {};

	/// rtrim: cuts of all values after a specific one

	template<typename List, typename List::value_type> struct rtrim;
	template<typename Type, Type ... args, Type to_find>
	struct rtrim<value_list<Type, args...>, to_find> :
		split_at<value_list<Type, args...>,
		         value_list<Type, args...>::find( to_find )>::first {};
}

#endif // ALGORITHMS_HXX_INCLUDED
