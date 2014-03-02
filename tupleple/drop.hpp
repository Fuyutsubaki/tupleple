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
		template<size_t N, class Tuple>
		class drop
		{
			using seq = typename index::make_N_index<size<Tuple>::value - N>::type;
			template<class T>
			struct Up
			{
				using type = index::Index<T::value + N>;
			};
		public:
			using indexs_type = typename map<Up, seq>::type;
			using type = typename index::type_list::to_tuple<indexs_type, Tuple>::type;
		};
	}

	template<size_t N, class Tuple>
	auto drop(const Tuple&tuple)
		->typename type_list::drop<N, Tuple>::type
	{
		using seq = typename type_list::drop<N, Tuple>::indexs_type;
		return index::to_tuple(seq(), tuple);
	}
}


