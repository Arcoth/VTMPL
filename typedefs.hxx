#ifndef TYPEDEFS_HXX_INCLUDED
#define TYPEDEFS_HXX_INCLUDED

#include <type_traits>
#include <cstdint>

namespace vtmpl
{

	using size_type = unsigned;

	using index_type = size_type;

	template<typename T>
	using eval = typename T::type;

	template<bool B, typename T, typename F>
	using cond = eval<std::conditional<B, T, F>>;

	template<int64_t Val>
	using int_ = std::integral_constant<int64_t, Val>;

	template<uint64_t Val>
	using uint_ = std::integral_constant<uint64_t, Val>;

	template<bool C>
	using requires = eval<std::enable_if<C>>;

	constexpr bool isdigit( char c )
	{
		return c >= '0' && c <= '9';
	}

	template<typename T>
	constexpr T max( T a, T b )
	{
		return a > b? a : b;
	}

	template<typename T>
	constexpr T min( T a, T b )
	{
		return a < b? a : b;
	}

	#define sconst static constexpr

}

#endif // TYPEDEFS_HXX_INCLUDED
