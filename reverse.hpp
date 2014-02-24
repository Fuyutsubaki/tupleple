#pragma once
#include<tuple>
#include"sequence.hpp"

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
			using sequence_type = typename sequence::make_reverse_N_Sequence < size<Tuple>::value>::type;
			using type = typename sequence::type_list::to_tuple<sequence_type, Tuple>::type;
		};
	}
	template<class Tuple>
	auto reverse(const Tuple&tuple)
		->typename type_list::reverse<Tuple>::type
	{
		using seq = typename type_list::reverse<Tuple>::sequence_type;
		return sequence::to_tuple(seq(), tuple);
	}
}