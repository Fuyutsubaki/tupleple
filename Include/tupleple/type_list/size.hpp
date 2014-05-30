#ifndef TUPLEPLE_TYPELIST_SIZE_HPP
#define TUPLEPLE_TYPELIST_SIZE_HPP

namespace tupleple{
	namespace type_list
	{
		template<class C,class Enaber=void>
		struct size
		{
			static_assert(sizeof(C) && false, "not define ");
		};

		template<class...T>
		struct size<List<T...>>
		{
			static const size_t value = sizeof...(T);
		};
	}
}



#endif