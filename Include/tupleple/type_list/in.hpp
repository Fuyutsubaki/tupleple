#pragma once

#include<type_traits>

#include"any.hpp"
#include"apply.hpp"


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
			:in<Elem, apply_struct_t<tList, List>>
		{};
		
		template<class Elem, class ...T>
		struct in<Elem,List<T...>>
		{
			template<class T>
			struct isSame
				:std::is_same<Elem,T>
			{};
			static const bool value = any<List<T...>, isSame>::value;
		};


		/*namespace deteil
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
		{};*/
	}
}