#pragma once 
#include"Index.hpp"
#include"tuple.hpp"
#include"map.hpp"
#include"to_tuple.hpp"
/*
auto x=tupleple::drop<1>(std::make_tuple(1,2,3,4));
*/

namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			template<size_t N, class Tuple>
			class drop_impl
			{
				using seq = index::make_seq<size<Tuple>::value - N>;
				template<size_t ...X>
				static auto trans(index::Sequence<X...>)
					->index::Sequence<(N + X)...>;
			public:
				using seq_type = decltype(trans(seq()));
				using type = type_list::to_tuple<seq_type, Tuple>;
			};
		}
		template<size_t N, class Tuple>
		using drop = typename impl::drop_impl<N, Tuple>::type;
	}

	template<size_t N, class Tuple>
	inline auto drop(const Tuple&tuple)
		->type_list::drop<N, Tuple>
	{
		using seq = typename type_list::impl::drop_impl<N, Tuple>::seq_type;
		return to_tuple(seq(), tuple);
	}
}


