#pragma once
#include<tuple>
#include"tuple.hpp"

namespace tupleple
{
	namespace index
	{
		template<size_t ...N>
		struct Sequence{};
		namespace impl{
			template<size_t N>
			class make_seq_impl
			{
				static const size_t half = N / 2;
				static const size_t halfr = (N - half);
				using left = typename make_seq_impl<half>::type;
				using right = typename make_seq_impl<halfr>::type;
				template<size_t ...L, size_t...R>
				static auto trans(Sequence<L...>, Sequence<R...>)->Sequence<L..., (half + R)...>;
			public:
				using type = decltype(trans(left(), right()));
			};
			template<>
			struct make_seq_impl<1>{ using type = Sequence<0>; };
			template<>
			struct make_seq_impl<0>{ using type = Sequence<>; };
		}
		template<size_t N>
		using make_seq = typename impl::make_seq_impl<N>::type;

		namespace impl
		{
			template<class>
			struct seq_to_tuple_impl;
			template<size_t...N>
			struct seq_to_tuple_impl<Sequence<N...>>
			{
				using type = std::tuple<std::integral_constant<size_t,N>...>;
			};
		}
		template<class Sequence>
		using seq_to_tuple = typename impl::seq_to_tuple_impl<Sequence>::type;
		namespace impl
		{
			template<class Tuple>
			struct tuple_to_seq_impl;
			template<class ...R>
			struct tuple_to_seq_impl<std::tuple<R...>>
			{
				using type = Sequence<R::value...>;
			};
		}
		template<class STDTuple>
		using tuple_to_seq = typename impl::tuple_to_seq_impl<STDTuple>::type;


		template<size_t N>
		using make_tuple = seq_to_tuple<make_seq<N>>;
	}
}