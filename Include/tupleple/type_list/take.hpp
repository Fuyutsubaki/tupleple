#pragma once 

#include<tupleple\index_tuple\index_TypeList.hpp>
#include"apply_index.hpp"

namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct take
			:apply_index<index::make_seq_t<N>, Tuple, List>
		{};

		template<size_t N, class Tuple>
		using take_t = typename take<N, Tuple>::type;
	}
}