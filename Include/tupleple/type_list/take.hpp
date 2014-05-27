#pragma once 
#include<tupleple\view\take.hpp>
/*
	using namespace tupleple;
	std::make_tuple(1, std::make_unique<int>(2), 3) | view::take<1>() | at<0>();
*/
namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct take
		{
			using type = view::take_view<N, Tuple>;
		};

		template<size_t N, class Tuple>
		using take_t = typename take<N, Tuple>::type;

	}
}