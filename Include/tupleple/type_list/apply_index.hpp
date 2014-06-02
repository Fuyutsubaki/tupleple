#pragma once

#include<tupleple\index_tuple\index_sequence.hpp>
#include"List.hpp"
namespace tupleple
{
	namespace type_list
	{
		template<class Idx, class List, template<class...>class>
		struct apply_index
		{};
		template<size_t... Idxs, class tList, template<class...>class Struct>
		struct apply_index<index::Sequence<Idxs...>, tList, Struct>
		{
			using type = Struct<at_t<Idxs, tList>...>;
		};
		template<class Idx, class List, template<class...>class Struct>
		using apply_index_t = typename apply_index<Idx, List, Struct>::type;
	}
}