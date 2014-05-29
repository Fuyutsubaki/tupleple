#pragma once
#include<tupleple\utility\utility.hpp>
#include<type_traits>
#include<tuple>
#include<tupleple\utility\index_tuple.hpp>
#include<tupleple\type_list\zip.hpp>
namespace tupleple
{
	namespace type_list
	{
		template<class element,class Tuple>
		struct in
		{};
		namespace deteil
		{
			template<class T, class ...>
			struct Data
				: utility::identity<T>
			{};

			template<class>
			struct type_set_impl;
			
			template<class...T>
			struct type_set_impl<std::tuple<T...>>
				:T...
			{};
			template<class...T>
			struct type_set
				:type_set_impl<typename zip_struct<Data, index::make_tuple_t<sizeof...(T)>, std::tuple<T...>>::type>
			{};
		}
		template<class Elem, class ...T>
		struct in<Elem, std::tuple<T...>>
			:std::is_base_of<utility::identity<Elem>, deteil::type_set<T...>>
		{};
	}
}