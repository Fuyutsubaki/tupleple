#pragma once

#include<tupleple\utility\view_impl_helper.hpp>
#include<tupleple\index_tuple\index_sequence.hpp>
namespace tupleple
{
	namespace view
	{
		template<class Tuple>
		struct type_separate_view
			:utility::base_view<type_separate_view<Tuple>, Tuple>
		{
			type_separate_view(Tuple&&tuple)
			:isuper(std::forward<Tuple>(tuple))
			{}
		};
	}
	template<class Tuple>
	struct tuple_trait<view::type_separate_view<Tuple>>
		:utility::view_tuple_trait_helper<view::type_separate_view<Tuple>>
	{
		using seq = index::make_seq_t<base_size>;

	};
}