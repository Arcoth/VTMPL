#ifndef TYPEDEFS_HXX_INCLUDED
#define TYPEDEFS_HXX_INCLUDED

namespace vtmpl
{

	using size_type = unsigned;

	using index_type = size_type;

	template<typename T>
	using eval = typename T::type;

}

#endif // TYPEDEFS_HXX_INCLUDED
