#pragma once
#include<tuple>
#include"Index.hpp"
#include"foldr.hpp"
#include"cons.hpp"
#include"to_tuple.hpp"
/*
auto x=tupleple::reverse(std::make_tuple(1,2,3,4));
*/

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		struct reverse
		{
			using normal_idxs = typename index::make_N_index<size<Tuple>::value>::type;
			template<class L_ist,class R_eturn>
			struct Trans
			{
				using type =  typename push<R_eturn,L_ist>::type;
			};
			using indexs_type = typename foldr<Trans, normal_idxs,std::tuple<>>::type;
			using type = typename index::type_list::to_tuple<indexs_type, Tuple>::type;
		};
	}
	template<class Tuple>
	auto reverse(const Tuple&tuple)
		->typename type_list::reverse<Tuple>::type
	{
		using seq = typename type_list::reverse<Tuple>::indexs_type;
		return index::to_tuple(seq(), tuple);
	}
}