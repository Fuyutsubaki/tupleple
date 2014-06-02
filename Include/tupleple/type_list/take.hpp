#pragma once 
#include<tupleple\view\take.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\type_list\zip.hpp>
#include"apply_index.hpp"


namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct take
		{};

		template<size_t N, class ...T>
		struct take<N,List<T...>>
		{
			using list = List<T...>;
			using type = apply_index_t<index::make_seq_t<N>, list, List>;
		};

		template<size_t N, class Tuple>
		using take_t = typename take<N, Tuple>::type;
	}
}