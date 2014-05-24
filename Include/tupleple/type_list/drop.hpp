#pragma once 
#include<tupleple\view\drop.hpp>

/*
using namespace tupleple;
auto tuple = std::make_tuple(1, std::make_unique<int>(2), 3);
auto x = std::move(tuple) | view::drop<1>();
auto i = at<0>(std::move(x));
*/

namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct drop
		{
			using type = view::drop_view<N, Tuple>;
		};
		template<size_t N, class Tuple>
		using drop_t = typename drop<N, Tuple>::type;
	}
}

