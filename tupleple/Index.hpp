#pragma once
#include<tuple>
#include"tuple.hpp"
#include"utility.hpp"

namespace tupleple
{
	namespace index
	{
		template<size_t ...N>
		struct Sequence{};
		//
		//
		template<size_t N>
		class make_seq;
		template<size_t N>
		using make_seq_t = typename make_seq<N>::type;
		template<size_t N>
		class make_seq
		{
			static const size_t half = N / 2;
			using rest = make_seq_t<half>;
			template<size_t...K>
			static auto trans(Sequence<K...>)
				->utility::cond_t<(N % 2) == 0, Sequence<K..., (half + K)...>, Sequence<K..., (half + K)..., N - 1>>;
		public:
			using type = decltype(trans(rest()));
		};
		template<>
		struct make_seq<0>{ using type = Sequence<>; };

		



		template<class>struct seq_to_tuple;
		template<size_t...N>
		struct seq_to_tuple<Sequence<N...>>
		{
			using type = std::tuple<std::integral_constant<size_t, N>...>;
		};
		template<class Sequence>
		using seq_to_tuple_t = typename seq_to_tuple<Sequence>::type;

		template<class Tuple>struct tuple_to_seq;

		template<class ...R>
		struct tuple_to_seq<std::tuple<R...>>
		{
			using type = Sequence<R::value...>;
		};
		template<class STDTuple>
		using tuple_to_seq_t = typename tuple_to_seq<STDTuple>::type;

		template<size_t N>
		using make_tuple_t = seq_to_tuple_t<make_seq_t<N>>;

		template<class Tuple>
		struct make_tuple_size_seq
		{
			using type = make_seq_t<tupleple::type_list::size<Tuple>::value>;
		};
		template<class Tuple>
		using make_tuple_size_seq_t = typename make_tuple_size_seq<Tuple>::type;
	}
}