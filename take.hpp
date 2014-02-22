#pragma once 
#include<tuple>
#include"sequence.hpp"
/*
	auto x=tupleple::take<2>(std::make_tuple(1,2,3,4));
*/
namespace tupleple
{
	namespace type_list
	{
		template<size_t N,class T>
		class take;

		template<size_t N,class ...R>
		class take<N,std::tuple<R...>>
		{
			template<size_t X>struct Pred{ static const size_t value = X < N; };
			using seq=typename sequence::make_N_Sequence< std::tuple_size<std::tuple<R...>>::value>::type;
			template<size_t ...N>
			static auto trans(sequence::Sequence<N...>)->sequence::Sequence<Pred<N>::value...>;
		public:
			using sequence_type = typename sequence::bit_filter<decltype(trans(std::declval<seq>()))>::type;
			using type = typename sequence::type_list::to_tuple<sequence_type, std::tuple<R...>>::type;
		};
	}

	template<size_t N,class ...R>
	auto take(const std::tuple<R...>&tuple)
		->typename type_list::take<N, std::tuple<R...>>::type
	{
		using seq = typename type_list::take<N, std::tuple<R...>>::sequence_type;
		return sequence::to_tuple(seq(), tuple);
	}
}