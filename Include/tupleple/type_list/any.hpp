#pragma once
#include<tuple>
#include<tupleple\utility\utility.hpp>
#include"apply.hpp"
namespace tupleple
{
	namespace type_list
	{

		template<class Tuple, template<class>class F>
		struct any
			:any<apply_struct_t<Tuple, std::tuple>, F>
		{};

		namespace deteil
		{
			template<class...>
			struct any_impl :std::true_type
			{};
			template<class...T>
			struct any_impl<std::pair<T, std::false_type>...>:std::false_type
			{};
			template<class...>
			struct none_impl :std::false_type
			{};
			template<class...T>
			struct none_impl<std::pair<T, std::false_type>...>:std::true_type
			{};
		}
		template<class...T, template<class>class F>
		struct any<std::tuple<T...>, F>
			:deteil::any_impl<std::pair<T, typename utility::expr2Bool<F<T>>::type>...>
		{};

	}
}