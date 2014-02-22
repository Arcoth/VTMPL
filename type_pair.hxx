#ifndef TYPE_PAIR_HXX_INCLUDED
#define TYPE_PAIR_HXX_INCLUDED

#include "identity.hxx"

namespace vtmpl
{
	template<typename A, typename B, typename C = void, typename D = void, typename E = void>
	struct type_pair
	{
		using first = A;
		using second = B;
		using third = C;
		using fourth = D;
		using fifth = E;
	};

}

#endif // TYPE_PAIR_HXX_INCLUDED
