#pragma once
#include<tupleple\tuple.hpp>
#include<tupleple\view\reverse.hpp>
/*
using namespace tupleple;
auto x = std::make_tuple(1, 2, 3, 4) | view::reverse() | at<0>();
*/
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		struct reverse
		{
			using type = view::reverse_view<Tuple>;
		};
		template<class Tuple>
		using reverse_t = typename reverse<Tuple>::type;
	}

}