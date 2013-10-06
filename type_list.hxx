#ifndef TYPE_LIST_HXX_INCLUDED
#define TYPE_LIST_HXX_INCLUDED

#include "type_pair.hxx"

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
		std::integral_constant<size_type, value_list<bool, std::is_same<Args, to_find>::value...>>::find(true)> {};

	template< typename List, size_type i >
	using get = eval< std::tuple_element<i, typename List::std_tuple> >;

	// Use this function inside a decltype-specifier to retrieve the deduced template arguments
	template<typename... Args>
	type_list<eval<std::decay<Args>>...> arg_type_list( Args&&... );

	/// concat_type_lists //////////////////////////////////////////////////////////

	template<typename, typename> struct concat;

	template<typename ... first,
			 typename ... second>
	struct concat<type_list<first...>, type_list<second...>> : type_list<first..., second...> {};

}


#endif // TYPE_LIST_HXX_INCLUDED
