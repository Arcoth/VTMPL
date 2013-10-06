#ifndef VALUE_LIST_HXX_INCLUDED
#define VALUE_LIST_HXX_INCLUDED

#include "typedefs.hxx"
#include "identity.hxx"

#include <limits>
#include <type_traits>

namespace vtmpl
{

	template <typename T, T...> struct value_list;

	constexpr size_type npos = std::numeric_limits<size_type>::max();

	template <typename Type,
			  Type... args>
	struct value_list_base : identity<value_list<Type, args...>>
	{
		static constexpr size_type length = sizeof...(args);

		using value_type = Type;

		static constexpr value_type arr[]{ args... };

	private:

		static constexpr size_type _count_impl( char c, size_type index )
		{
			return arr[index] == c + (index == 0 ? 0 : _count_impl(c, index - 1));
		}

		static constexpr size_type _find_nested_impl( value_type open, value_type close, size_type Z, size_type pos )
		{
			return array[pos] == close? (Z == 0 ? pos : _find_nested_impl(open, close, Z-1, pos+1)) :
				 array[pos] == open ? _find_nested_impl(open, close, Z+1, pos+1) :
				 _find_nested_impl(open, close, Z, pos+1) ;
		}

		static constexpr size_type _find_impl( char c, size_type index )
		{
			return index == length ? npos : c == arr[index] ? index : _find_impl(c, index + 1);
		}

	public:

		static constexpr size_type count( char c )
		{ return _count_impl( c, length - 1 ); }

		static constexpr size_type find_nested( value_type open, value_type close, size_type start_pos = 0 )
		{ return _find_nested_impl(open, close, 0, start_pos); }

		static constexpr size_type find( char c )
		{ return _find_impl( c, 0 ); }
	};

	template <typename Type,
			  Type... args>
	constexpr Type value_list_base<Type, args...>::arr[];

	template<typename Type,
		     Type... args>
	struct value_list : value_list_base<Type, args...> {};

	template<char... args>
	struct value_list<char, args...> : value_list_base<char, args...>
	{
		static char constexpr nt_arr[]{ args..., '\0' };
	};

	template<char... args>
	char constexpr value_list<char, args...>::nt_arr[];

	template< typename, typename >  struct equal;

	template< typename T, T... first, T... last >
	struct equal< value_list<T, first...>,
	              value_list<T, second...> > :


}

#endif // VALUE_LIST_HXX_INCLUDED
