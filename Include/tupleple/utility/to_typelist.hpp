#pragma once

#include<tupleple\type_list\List.hpp>
#include<tupleple\type_list\apply.hpp>

namespace tupleple
{
	namespace utility
	{
		template<class T>
		struct to_typelist
			:type_list::apply_struct<T,List>
		{};
		template<class T>
		using to_typelist_t = typename to_typelist<T>::type; 
	}
}