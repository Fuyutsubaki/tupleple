#pragma once
#include"any.hpp"
#include<type_traits>

namespace tupleple
{
	namespace type_list
	{
		template<class element,class Tuple>
		struct in
		{
			template<class T>
			struct eval
				:std::is_same<T, element>
			{};
			static const bool value = any<Tuple, eval>::value;
		};
	}
}