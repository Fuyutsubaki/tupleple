#pragma once
#include<tupleple\tuple.hpp>
#include<tupleple\index_tuple\index_sequence.hpp>

namespace tupleple
{
	namespace type_list
	{
		namespace deteil
		{
			template<class Seq, class Tuple, template<class...>class Struct>
			struct apply_struct_impl
			{};
			template<size_t...Idxs, class Tuple, template<class...>class Struct>
			struct apply_struct_impl<index::Sequence<Idxs...>, Tuple, Struct>
			{
				using type = Struct<at_t<Idxs, Tuple>...>;
			};
		}
		template<class Tuple, template<class...>class Struct>
		struct apply_struct
		{
			using Seq = index::make_seq_t<size<Tuple>::value>;
			using type = typename deteil::apply_struct_impl<Seq, Tuple, Struct>::type;
		};
		template<class Tuple, template<class...>class Struct>
		using apply_struct_t = typename apply_struct<Tuple, Struct>::type;
		

		template<class Tuple, template<class...>class F>
		struct apply
		{
			using Seq = index::make_seq_t<size<Tuple>::value>;
			using type = typename apply_struct_t<Tuple, F>::type;
		};
		template<class Tuple, template<class...>class F>
		using apply_t = typename apply<Tuple, F>::type;
	}

}