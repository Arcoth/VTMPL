#ifndef TYPE_LIST_HXX_INCLUDED
#define TYPE_LIST_HXX_INCLUDED

#include "value_list.hxx"
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
		std::integral_constant<size_type, value_list<bool, equal<Args, to_find>::value...>::find(true)> {};

	template< typename List, size_type i >
	using get = eval< std::tuple_element<i, typename List::std_tuple> >;

	template< typename List >
	using back = eval< std::tuple_element<List::length-1, typename List::std_tuple> >;

	// Use this function inside a decltype-specifier to retrieve the deduced template arguments
	template<typename... Args>
	type_list<eval<std::decay<Args>>...> arg_type_list( Args&&... );

	/// concat_type_lists //////////////////////////////////////////////////////////

	template<typename, typename> struct concat;

	template<typename ... first,
			 typename ... second>
	struct concat<type_list<first...>, type_list<second...>> : type_list<first..., second...> {};

	/// replace-last

	template<typename, typename> struct replace_last;
	template<typename New, typename First, typename... Types>
	struct replace_last<New, type_list<First, Types...>> :
	    concat<type_list<First>, typename replace_last<New, type_list<Types...>>::type> {};
	template<typename New, typename First>
	struct replace_last<New, type_list<First>> : type_list<New> {};

}


#endif // TYPE_LIST_HXX_INCLUDED
