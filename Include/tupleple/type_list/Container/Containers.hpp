#pragma once
#include<utility>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\index_tuple.hpp>
#include<tupleple\type_list\zip.hpp>

namespace tupleple
{
	namespace type_list
	{
		namespace containers
		{
			template<class ...>
			struct Map;

			template<class...Key, class...Val>
			struct Map<std::pair<Key, Val>...>
				:std::pair<Key, Val>...
			{};
			
			template<class ...T>
			struct Vector
			{};

			template<class ...T>
			struct Set
			{};
		}
	}
}