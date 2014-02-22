#pragma once
#include<tuple>
#include"sequence.hpp"

/*
tupleple::reverse(std::make_tuple(1,2,3,4))
*/
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		class reverse;

		template<class ...R>
		struct reverse<std::tuple<R...>>
		{
			using sequence_type = typename sequence::make_reverse_N_Sequence < std::tuple_size<std::tuple<R...>>::value>::type;
			using type = typename sequence::type_list::to_tuple<sequence_type, std::tuple<R...>>::type;
		};
	}
	template<class ...R>
	auto reverse(const std::tuple<R...>&tuple)
		->typename type_list::reverse<std::tuple<R...>>::type
	{
		using seq = typename type_list::reverse<std::tuple<R...>>::sequence_type;
		return sequence::to_tuple(seq(), tuple);
	}
}