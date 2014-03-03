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
				using seq = index::make_N_index<size<Tuple>::value - N>;
				template<class T>
				struct Up
				{
					using type = index::Index<T::value + N>;
				};
			public:
				using indexs_type = map<Up, seq>;
				using type = index::type_list::to_tuple<indexs_type, Tuple>;
			};
		}
		template<size_t N, class Tuple>
		using drop = typename impl::drop_impl<N, Tuple>::type;
	}

	template<size_t N, class Tuple>
	inline auto drop(const Tuple&tuple)
		->type_list::drop<N, Tuple>
	{
		using seq = typename type_list::impl::drop_impl<N, Tuple>::indexs_type;
		return index::to_tuple(seq(), tuple);
	}
}


