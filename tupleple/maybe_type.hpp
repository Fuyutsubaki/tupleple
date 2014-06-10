#pragma once




namespace tupleple
{
	namespace utility
	{
		template<bool r,class T=void>
		struct Maybe_type
		{
			static const bool value = true;
			using type = T;
		};
		template<class T>
		struct Maybe_type<false>
		{
			static const bool value = false;
		};
	}
}