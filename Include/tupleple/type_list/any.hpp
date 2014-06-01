#pragma once
#include"List.hpp"
#include<tupleple\utility\utility.hpp>
#include"apply.hpp"
namespace tupleple
{
	namespace type_list
	{

		template<class Tuple, template<class>class F>
		struct any
			:any<apply_struct_t<Tuple, List>, F>
		{};

		namespace deteil
		{
			template<class...>
			struct any_impl :std::true_type
			{};
			template<class...T>
			struct any_impl<std::integral_constant<T,false>...>:std::false_type
			{};
			
			template<class...>
			struct none_impl :std::false_type
			{};
			template<class...T>
			struct none_impl<std::pair<T, std::false_type>...>:std::true_type
			{};
		}
		template<class...T, template<class>class F>
		struct any<List<T...>, F>
			:deteil::any_impl<typename utility::expr2Bool<F<T>>::type...>
		{};

	}
}