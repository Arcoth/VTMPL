/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef VALUE_LIST_HXX_INCLUDED
#define VALUE_LIST_HXX_INCLUDED

#include "typedefs.hxx"

namespace vtmpl
{

	template <typename Type,
	          Type... args>
	struct value_list : identity<value_list<Type, args...>>
	{
		VTMPL_SCONST size_type length = sizeof...(args);

		using value_type = Type;

	private:

		using array_type = cond<length != 0, value_type[], identity<>>;

	public:

		VTMPL_SCONST array_type array{ args... };


#if VTMPL_RELAX_CONSTEXPR_FUNC

		VTMPL_SCONST size_type _count_impl( value_type c, size_type )
		{
			size_type rval = 0;
			for( auto v : array )
				if( v == c )
					++rval;

			return rval;
		}

		VTMPL_SCONST size_type _find_nested_impl( value_type open, value_type close, size_type Z, size_type pos )
		{
			for(; pos != length ; ++pos)
				if     ( array[pos] == open  )
					++Z;
				else if( array[pos] == close )
				{
					if( Z == 0 )
						return pos;
					--Z;
				}

			return npos;
		}

		VTMPL_SCONST size_type _find_impl( value_type c, size_type )
		{
			for( size_type i = 0; i != length; ++i )
				if( array[i] == c )
					return i;

			return npos;
		}

#else

		VTMPL_SCONST size_type _count_impl( value_type c, size_type index )
		{
			return array[index] == c + (index == 0 ? 0 : _count_impl(c, index - 1));
		}

		VTMPL_SCONST size_type _find_nested_impl( value_type open, value_type close, size_type Z, size_type pos )
		{
			return array[pos] == close? (Z == 0 ? pos : _find_nested_impl(open, close, Z-1, pos+1)) :
				 array[pos] == open ? _find_nested_impl(open, close, Z+1, pos+1) :
				 _find_nested_impl(open, close, Z, pos+1) ;
		}

		VTMPL_SCONST size_type _find_impl( value_type c, size_type index )
		{
			return index == length ? npos : c == array[index] ? index : _find_impl(c, index + 1);
		}

#endif

	public:

		VTMPL_SCONST size_type count( value_type c )
		{ return _count_impl( c, length - 1 ); }

		VTMPL_SCONST size_type find_nested( value_type open, value_type close, size_type start_pos = 0 )
		{ return _find_nested_impl(open, close, 0, start_pos); }

		VTMPL_SCONST size_type find( value_type c )
		{ return _find_impl( c, 0 ); }

		VTMPL_SCONST value_type back() { return array[length-1]; }
		VTMPL_SCONST value_type front() { return array[0]; }
	};

	template <typename Type,
	          Type... args>
	constexpr typename value_list<Type, args...>::array_type value_list<Type, args...>::array;

	template<typename> struct nt_array_from;
	template<typename T, T... vals>
	struct nt_array_from<value_list<T, vals...>>
	{
		VTMPL_SCONST T array[]{vals..., T(0)};
	};

	template<typename T, T... vals>
	constexpr T nt_array_from<value_list<T, vals...>>::array[];

	template< typename List, typename List::value_type V >
	struct push_back;
	template< typename ValT, ValT ... values, ValT V >
	struct push_back<value_list<ValT, values...>, V> : value_list<ValT, values..., V> {};
}

#endif // VALUE_LIST_HXX_INCLUDED
