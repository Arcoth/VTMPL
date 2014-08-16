/* Copyright (c) Robert Haberlach, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef OVERLOAD_RANKER_HXX_INCLUDED
#define OVERLOAD_RANKER_HXX_INCLUDED

#include "typedefs.hxx"
/** If you want to gain independence from this header, define index_type in the namespace vtmpl
    as a integer type. */

namespace vtmpl
{

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
}

#endif // OVERLOAD_RANKER_HXX_INCLUDED
