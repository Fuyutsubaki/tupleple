#ifndef TUPLEPLE_UTILITY_INDEX_SEQUENCE_HPP_0523
#define TUPLEPLE_UTILITY_INDEX_SEQUENCE_HPP_0523

#include<tupleple\utility\utility.hpp>

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
			using type = decltype(trans(rest{}));
		};
		template<>
		struct make_seq<0>{ using type = Sequence<>; };
	}
}
















#endif