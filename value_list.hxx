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
	struct value_list : identity<value_list<Type, args...>>
	{
		sconst size_type length = sizeof...(args);

		using value_type = Type;

		sconst value_type array[]{ args... };

	private:

		sconst size_type _count_impl( value_type c, size_type index )
		{
			return array[index] == c + (index == 0 ? 0 : _count_impl(c, index - 1));
		}

		sconst size_type _find_nested_impl( value_type open, value_type close, size_type Z, size_type pos )
		{
			return array[pos] == close? (Z == 0 ? pos : _find_nested_impl(open, close, Z-1, pos+1)) :
				 array[pos] == open ? _find_nested_impl(open, close, Z+1, pos+1) :
				 _find_nested_impl(open, close, Z, pos+1) ;
		}

		sconst size_type _find_impl( value_type c, size_type index )
		{
			return index == length ? npos : c == array[index] ? index : _find_impl(c, index + 1);
		}

	public:

		sconst size_type count( value_type c )
		{ return _count_impl( c, length - 1 ); }

		sconst size_type find_nested( value_type open, value_type close, size_type start_pos = 0 )
		{ return _find_nested_impl(open, close, 0, start_pos); }

		sconst size_type find( value_type c )
		{ return _find_impl( c, 0 ); }
	};

	template <typename Type,
	          Type... args>
	constexpr Type value_list<Type, args...>::array[];

	template<typename> struct nt_array_from;
	template<typename T, T... vals>
	struct nt_array_from<value_list<T, vals...>>
	{
		sconst T array[]{vals..., T(0)};
	};

	template<typename T, T... vals>
	constexpr T nt_array_from<value_list<T, vals...>>::array[];

	template< typename T, typename T2 >
	using equal = std::is_same<T, T2>;


}

#endif // VALUE_LIST_HXX_INCLUDED
