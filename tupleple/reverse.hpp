#pragma once
#include<tuple>
#include"Index.hpp"
#include"binary_fold.hpp"
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
			using seq = typename index::make_N_index<size<Tuple>::value>::type;
			template<class L,class R>
			struct Trans
			{
				using type = typename cat<R, L>::type;
			};
			template<class T>
			struct wrap
			{
				using type = std::tuple<T>;
			};
		public:
			using indexs_type = typename binary_fold<Trans, seq, wrap>::type;
			using type = typename index::type_list::to_tuple<indexs_type, Tuple>::type;
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