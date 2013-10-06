#ifndef IDENTITY_HXX_INCLUDED
#define IDENTITY_HXX_INCLUDED

namespace vtmpl
{

	template<typename T>
	struct identity
	{
		using type = T;
	};

}

#endif // IDENTITY_HXX_INCLUDED
