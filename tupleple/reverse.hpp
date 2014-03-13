#pragma once
#include<tuple>
#include"Index.hpp"

#include"to_tuple.hpp"
#include"cat.hpp"
/*
auto x=tupleple::reverse(std::make_tuple(1,2,3,4));
*/

namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			template<class Tuple>
			class reverse_impl
			{
				static const size_t N = size<Tuple>::value;
				using seq = index::make_seq<N>;

				template<size_t...K>
				static auto trans(index::Sequence<K...>)
					->index::Sequence<(N - K - 1)...>;
			public:
				using seq_type = decltype(trans(seq()));
				using type = type_list::to_tuple<seq_type, Tuple>;
			};
		}
		template<class Tuple>
		using reverse = typename impl::reverse_impl<Tuple>::type;
	}
	template<class Tuple>
	auto reverse(const Tuple&tuple)
		->type_list::reverse<Tuple>
	{
		using seq = typename type_list::impl::reverse_impl<Tuple>::seq_type;
		return to_tuple(seq(), tuple);
	}
}