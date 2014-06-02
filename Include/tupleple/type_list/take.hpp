#pragma once 
#include<tupleple\view\take.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\type_list\zip.hpp>
#include"apply_index.hpp"

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
			//using type = view::take_view<N, Tuple>;
		};

		template<size_t N, class ...T>
		struct take<N,List<T...>>
		{
			using list = List<T...>;
			using type = apply_index_t<index::make_seq_t<N>, list, List>;
		};

		template<size_t N, class Tuple>
		using take_t = typename take<N, Tuple>::type;
	}
}