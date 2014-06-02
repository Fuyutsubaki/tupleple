#pragma once
#include<tupleple\tuple.hpp>
#include<tupleple\index_tuple\index_sequence.hpp>
#include"List.hpp"
#include"apply_index.hpp"
namespace tupleple
{
	namespace type_list
	{
		
		template<class tList, template<class...>class Struct>
		struct apply_struct
		{
			using type= apply_index_t<index::make_seq_t<size<tList>::value>, tList, Struct>;
		};
		template<class Tuple, template<class...>class Struct>
		using apply_struct_t = typename apply_struct<Tuple, Struct>::type;
		

		template<class List, template<class...>class F>
		struct apply
		{
			using Seq = index::make_seq_t<size<List>::value>;
			using type = typename apply_struct_t<List, F>::type;
		};
		template<class List, template<class...>class F>
		using apply_t = typename apply<List, F>::type;
	}

}