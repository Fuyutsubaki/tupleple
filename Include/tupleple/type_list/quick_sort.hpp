#pragma once
#include"filter.hpp"
#include"cat.hpp"
#include"ListStyle.hpp"

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple,template<class...>class Compare,class=void>
		struct quick_sort
		{
			using pibot = front_t<Tuple>;
			using tail = tail_t<Tuple>;
			template<class T>
			struct is_lhs
				:Compare<T, pibot>
			{};
			template<class T>
			struct is_rhs
			{
				static const bool value = !Compare<T, pibot>::value;
			};

			using lhs = typename quick_sort<filter_if_t<tail, is_lhs>, Compare>::type;
			using rhs = typename quick_sort<filter_if_t<tail, is_rhs>, Compare>::type;
			using type = typename cat<lhs, List<pibot>, rhs>::type;
		};
		template<class Tuple, template<class...>class Compare>
		struct quick_sort<Tuple, Compare,typename std::enable_if<size<Tuple>::value==0>::type>
		{
			using type = List<>;
		};
	}
}