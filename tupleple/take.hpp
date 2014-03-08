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
		namespace impl{
			template<size_t N, class Tuple>
			struct take_impl
			{
				using indexs_type = index::make_N_index<N>;
				using type = index::type_list::to_tuple<indexs_type, Tuple>;
			};
		}
		template<size_t N, class Tuple>
		using take = typename impl::take_impl<N, Tuple>::type;
	}
	

	template<size_t N,class Tuple>
	inline auto take(const Tuple&tuple)
		->type_list::take<N, Tuple>
	{
		using Idxs = typename type_list::impl::take_impl<N, Tuple>::indexs_type;
		return index::to_tuple(Idxs(), tuple);
	}


	//lazy
}