#pragma once
#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\view_impl_helper.hpp>
/*
using namespace tupleple;
auto x = std::make_tuple(1, 2, 3, 4) | view::reverse() | at<0>();
*/

namespace tupleple
{
	namespace view
	{
		template<class Tuple>
		struct reverse_view
			:utility::base_view<reverse_view<Tuple>, Tuple>
		{
			reverse_view(Tuple&&tuple)
				:isuper(std::forward<Tuple>(tuple))
			{}
		};
		
		struct reverse_functor:utility::ExtensionMemberFunction
		{
			template<class Tuple>
			reverse_view<Tuple> operator()(Tuple&&tuple)
			{
				return reverse_view<Tuple>(std::forward<Tuple>(tuple));
			}
		};
		inline reverse_functor reverse(){ return{}; }
	}
	template<class Tuple>
	struct tuple_trait<view::reverse_view<Tuple>>
		:utility::view_tuple_trait_helper<view::reverse_view<Tuple>>
	{
		static const size_t size = base_size;

		template<size_t Idx>
		using element = base_element<size - 1 - Idx>;

		template<size_t N, class T>
		using result_type_of
			= base_result_type_of<size - 1 - N, T>;

		template<size_t Idx, class T>
		static auto get(T&&x)
			->result_of_t<Idx,T>
		{
			return base_forward<T>(x) | at<size - 1 - Idx>();
		}

	};

}