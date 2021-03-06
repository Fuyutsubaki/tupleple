#pragma once
#include"List.hpp"
#include<tupleple\utility\utility.hpp>
#include<tupleple\index_tuple\index_sequence.hpp>
#include<tupleple\utility\to_typelist.hpp>

namespace tupleple
{

	namespace type_list
	{
		template<class Tuple,template<class>class F>
		struct all
			:all<utility::to_typelist_t<Tuple>, F>
		{};

		namespace deteil
		{
			template<class...>
			struct all_impl :std::false_type
			{};
			template<class...T>
			struct all_impl<std::integral_constant<T,true>...>:std::true_type
			{};
		}
		template<class...T, template<class>class F>
		struct all<List<T...>,F>
			:deteil::all_impl<typename utility::expr2Bool<F<T>>::type...>
		{};
	
	}
}