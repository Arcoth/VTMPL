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

}

#endif // TYPEDEFS_HXX_INCLUDED
