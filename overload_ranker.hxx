/* Copyright (c) Arcoth, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef OVERLOAD_RANKER_HXX_INCLUDED
#define OVERLOAD_RANKER_HXX_INCLUDED

#include "utility.hxx"

#include <utility> // std::forward for the macro

namespace vtmpl
{
	template <typename... T>
	struct select_overload
	{
		template <typename R, typename... Superfluent>
		static auto from( R(*f)(T..., Superfluent...) )
		VTMPL_AUTO_RETURN(f)
	};

#ifdef VTMPL_OVERLOAD_RANK_LIMIT
	constexpr index_type overload_rank_limit = VTMPL_OVERLOAD_RANK_LIMIT;
#else
	constexpr index_type overload_rank_limit = 10;
#endif

	template< index_type i >
	struct rank : rank<i + 1> {};

	template<>
	struct rank<overload_rank_limit> {};

	using first_choice   = rank<0>;
	using second_choice  = rank<1>;
	using third_choice   = rank<2>;
	using fourth_choice  = rank<3>;
	using fifth_choice   = rank<4>;
	using sixth_choice   = rank<5>;
	using seventh_choice = rank<6>;
	using eigth_choice   = rank<7>;
	using ninth_choice   = rank<8>;
	using tenth_choice   = rank<9>;

	using default_choice = rank<overload_rank_limit>;

	constexpr rank<0> ranked_call()
	{
		return {};
	}

	#define VTMPL_DEFINE_RANKED_FORWARDER(rank, name, impl)             \
		template <typename... Args>                                   \
		constexpr auto name( ::vtmpl::rank##_choice, Args&&... args ) \
		VTMPL_AUTO_RETURN( impl(::std::forward<Args>(args)...) )

	#define VTMPL_DEFINE_RANKED_CALLER(name, impl)                 \
		template <typename... Args>                              \
		constexpr auto name( Args&&... args )                    \
		VTMPL_AUTO_RETURN( impl(::vtmpl::ranked_call(), ::std::forward<Args>(args)...) )
}

#endif // OVERLOAD_RANKER_HXX_INCLUDED
