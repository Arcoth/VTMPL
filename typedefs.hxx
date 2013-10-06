#ifndef TYPEDEFS_HXX_INCLUDED
#define TYPEDEFS_HXX_INCLUDED

#include <type_traits>

namespace vtmpl
{

	using size_type = unsigned;

	using index_type = size_type;

	template<typename T>
	using eval = typename T::type;

	template<bool B, typename T, typename F>
	using cond = eval<std::conditional<B, T, F>>;

}

#endif // TYPEDEFS_HXX_INCLUDED
