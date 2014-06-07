#pragma once
#include"List.hpp"
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\to_typelist.hpp>
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class>class F>
		struct any
			:any<utility::to_typelist_t<Tuple>, F>
		{};

		namespace deteil
		{
			template<class...>
			struct any_impl :std::true_type
			{};
			template<class...T>
			struct any_impl<std::integral_constant<T,false>...>:std::false_type
			{};
		}
		template<class...T, template<class>class F>
		struct any<List<T...>, F>
			:deteil::any_impl<typename utility::expr2Bool<F<T>>::type...>
		{};

	}
}