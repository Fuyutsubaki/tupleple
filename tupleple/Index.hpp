#pragma once
#include<tuple>
#include"tuple.hpp"

namespace tupleple
{
	namespace index
	{
		template<size_t N>
		struct Index
		{
			static const size_t value = N;
		};
		
		namespace sequence
		{
			template<size_t ...N>
			struct Sequence{};
			template<size_t N>
			class make_N_seq
			{
				static const size_t half = N / 2;
				static const size_t halfr = (N - half);
				using left = typename make_N_seq<half>::type;
				using right = typename make_N_seq<halfr>::type;
				template<size_t ...L,size_t...R>
				static auto trans(Sequence<L...>, Sequence<R...>)->Sequence<L..., (half + R)...>;
			public:
				using type = decltype(trans(left(), right()));
			};
			template<>
			struct make_N_seq<1>{ using type = Sequence<0>; };
			template<>
			struct make_N_seq<0>{ using type = Sequence<>; };
		}
		namespace impl
		{
			template<size_t N>
			class make_N_index_impl
			{
				template<size_t...N>
				static auto trans(sequence::Sequence<N...>)->std::tuple<Index<N>...>;
				using seq = typename sequence::make_N_seq<N>::type;
			public:
				using type = decltype(trans(seq()));
			};
		}
		template<size_t N>
		using make_N_index = typename impl::make_N_index_impl<N>::type;
	}
}