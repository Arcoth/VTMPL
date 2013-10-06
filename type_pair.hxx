#ifndef TYPE_PAIR_HXX_INCLUDED
#define TYPE_PAIR_HXX_INCLUDED

#include "identity.hxx"

namespace vtmpl
{

	template<typename A, typename B>
	struct type_pair : identity<type_pair<A,B>>
	{
		using first = A;
		using second = B;
	};

}

#endif // TYPE_PAIR_HXX_INCLUDED
