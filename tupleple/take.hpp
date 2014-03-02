#pragma once 
#include<tuple>
#include"Index.hpp"
#include"to_tuple.hpp"

/*
	auto x=tupleple::take<2>(std::make_tuple(1,2,3,4));
*/
namespace tupleple
{
	namespace type_list
	{
		template<size_t N,class Tuple>
		struct take
		{
			using indexs_type = typename index::make_N_index<N>::type;
			using type = typename index::type_list::to_tuple<indexs_type, Tuple>::type;
		};
	}

	template<size_t N,class Tuple>
	auto take(const Tuple&tuple)
		->typename type_list::take<N, Tuple>::type
	{
		using Idxs = typename type_list::take<N, Tuple>::indexs_type;
		return index::to_tuple(Idxs(), tuple);
	}
}