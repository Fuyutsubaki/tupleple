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
		template<class Tuple>
		class reverse
		{
			static const size_t N = size<Tuple>::value;
			using seq = index::make_N_index<N>;
			template<class Idx>
			struct Trans
			{
				using type = index::Index<N - 1 - Idx::value>;
			};
		public:
			using indexs_type = map<Trans, seq>;
			using type = index::type_list::to_tuple<indexs_type, Tuple>;
		};
	}
	template<class Tuple>
	auto reverse(const Tuple&tuple)
		->typename type_list::reverse<Tuple>::type
	{
		using seq = typename type_list::reverse<Tuple>::indexs_type;
		return index::to_tuple(seq(), tuple);
	}
}