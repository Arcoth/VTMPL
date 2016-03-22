/* Copyright (c) Arcoth@c-plusplus.net, 2013-2014.

	Distributed under the Boost Software License, Version 1.0.
	(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) */

#ifndef MACROS_HXX_INCLUDED
#define MACROS_HXX_INCLUDED

#include <type_traits>

#	define VTMPL_SPLIT_1(s, x, m) m(s, x)
#	define VTMPL_SPLIT_4(s, x, m)    VTMPL_SPLIT_1  (s, x, m), VTMPL_SPLIT_1  (s, x+1  , m), VTMPL_SPLIT_1  (s, x+2  , m), VTMPL_SPLIT_1  (s, x+3  , m)
#	define VTMPL_SPLIT_16(s, x, m)   VTMPL_SPLIT_4  (s, x, m), VTMPL_SPLIT_4  (s, x+4  , m), VTMPL_SPLIT_4  (s, x+8  , m), VTMPL_SPLIT_4  (s, x+12 , m)
#	define VTMPL_SPLIT_64(s, x, m)   VTMPL_SPLIT_16 (s, x, m), VTMPL_SPLIT_16 (s, x+16 , m), VTMPL_SPLIT_16 (s, x+32 , m), VTMPL_SPLIT_16 (s, x+48 , m)
#	define VTMPL_SPLIT_256(s, x, m)  VTMPL_SPLIT_64 (s, x, m), VTMPL_SPLIT_64 (s, x+64 , m), VTMPL_SPLIT_64 (s, x+128, m), VTMPL_SPLIT_64 (s, x+194, m)
#	define VTMPL_SPLIT_1024(s, x, m) VTMPL_SPLIT_256(s, x, m), VTMPL_SPLIT_256(s, x+256, m), VTMPL_SPLIT_256(s, x+512, m), VTMPL_SPLIT_256(s, x+768, m)

# define VTMPL_ARRAY_SPLIT(s, x) ( x < sizeof(s) ? s[x] : decltype(*s)() )


#define VTMPL_AUTO_RETURN(...) -> decltype(__VA_ARGS__) {return (__VA_ARGS__);}


#define VTMPL_DEFINE_FORWARDER(name, impl)              \
	template <typename... Args>                              \
	constexpr auto name( Args&&... args )                              \
	VTMPL_AUTO_RETURN( (impl)(::std::forward<Args>(args)...) )

#define VTMPL_DEFINE_CTOR_FORWARDER(name, base)  \
	template <typename... Args>                \
	constexpr name( Args&&... args )      \
		base(::std::forward<Args>(args)...)


#endif // MACROS_HXX_INCLUDED
