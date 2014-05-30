#pragma once
#include<tuple>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\index_tuple.hpp>
#include"apply.hpp"
namespace tupleple
{

	namespace type_list
	{

		template<class Tuple,template<class>class F>
		struct all
			:all<apply_struct_t<Tuple,std::tuple>,F>
		{};

		namespace deteil
		{
			template<class...>
			struct all_impl :std::false_type
			{};
			template<class...T>
			struct all_impl<std::pair<T, std::true_type>...>:std::true_type
			{};
		}
		template<class...T, template<class>class F>
		struct all<std::tuple<T...>,F>
			:deteil::all_impl<std::pair<T, typename utility::expr2Bool<F<T>>::type>...>
		{};
	
	}
}