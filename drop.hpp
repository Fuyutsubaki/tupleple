#pragma once 
#include<tuple>
#include"sequence.hpp"
#include"tuple.hpp"

/*
auto x=tupleple::drop<2>(std::make_tuple(1,2,3,4));
*/
namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		class drop
		{
			template<size_t X>struct Pred{ static const size_t value = X >= N; };
			using seq = typename sequence::make_N_Sequence<size<Tuple>::value>::type;
			using res_seq=typename sequence::map<seq, Pred>::type;
		public:
			using sequence_type = typename sequence::bit_filter<res_seq>::type;
			using type = typename sequence::type_list::to_tuple<sequence_type, Tuple>::type;
		};
	}

	template<size_t N, class Tuple>
	auto drop(const Tuple&tuple)
		->typename type_list::drop<N, Tuple>::type
	{
		using seq = typename type_list::drop<N, Tuple>::sequence_type;
		return sequence::to_tuple(seq(), tuple);
	}
}


