/* Copyright (c) Arcoth@c-plusplus.net, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef MATH_HXX_INCLUDED
#define MATH_HXX_INCLUDED

#include "typedefs.hxx"
#include "index_list.hxx"

#include <climits>

namespace vtmpl
{
	template <typename Integral>
	constexpr bool is_power_of_2( Integral i )
	{
		return (i & i - 1) == 0 && i != 0;
	}

	template <typename V, size_type exp>
	struct log_table : concat< eval<log_table<V, exp-1>>, eval<make_list_val<V, 1 << (exp-1), exp-1>> > {};
	template <typename V>
	struct log_table<V, 0> : value_list<V, V(-1)> {};

	namespace detail
	{
		// computes ilog2 - rounded downwards to the next lower multiple of base
		template <unsigned bits, unsigned base>
		struct trunc_ilog2_env
		{
			static_assert (is_power_of_2(bits / base), ""); // for convenience; strange recursive errors might occur on exotic platforms

			template <typename Integral>
			constexpr unsigned operator()( Integral i )
			{
				using next_env = trunc_ilog2_env<bits/2, base>;

				return i >= Integral(1) << bits ? bits + next_env()(i >> bits)
				                                : next_env()(i & (Integral(1) << bits) - 1 );
			}
		};

		template <unsigned bits>
		struct trunc_ilog2_env<bits, bits>
		{
			template <typename Integral>
			constexpr unsigned operator()( Integral i )
			{
				return (i >= Integral(1) << bits) * bits;
			}
		};

		constexpr unsigned lookup_ilog2( unsigned long long i, unsigned trunc_bits )
		{
			using log = log_table<unsigned, CHAR_BIT>;

			return trunc_bits + log::array[i >> trunc_bits];
		}
	}

	/// computes the integer logarithm of i - rounded downwards to the next lower multiple of base.
	/// bits should be (sizeof Integral) * CHAR_BIT / 2 initially.
	template <unsigned bits, unsigned base, typename Integral>
	constexpr unsigned trunc_ilog2( Integral i )
	{
		return detail::trunc_ilog2_env<bits, base>()(i);
	}

	constexpr unsigned ilog2( unsigned long long i )
	{
		using bits = uint_<sizeof(i)*CHAR_BIT>;

	#if defined __GNUG__ || defined __clang__

		return i? bits() - 1 - __builtin_clzll(i) : -1;

	#else

		return detail::lookup_ilog2( i, trunc_ilog2<bits() / 2, CHAR_BIT>(i) );

	#endif
	}
}

#endif // MATH_HXX_INCLUDED
