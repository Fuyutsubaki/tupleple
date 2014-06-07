#pragma once

#include<type_traits>

#include"any.hpp"


//using namespace tupleple;
//using namespace type_list;
//static_assert(in<int, List<char, int>>::value, "");
//static_assert(!in<long, List<char, int>>::value, "");

namespace tupleple
{
	namespace type_list
	{
		template<class Elem,class tList>
		struct in
		{
			template<class T>
			struct isSame
				:std::is_same<Elem, T>
			{};
			static const bool value = any<tList, isSame>::value;
		};
	}
}