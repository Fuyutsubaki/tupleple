#pragma once 

#include<tupleple\utility\view_impl_helper.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\mem_forward.hpp>
/*
	using namespace tupleple;
	std::make_tuple(1, std::make_unique<int>(2), 3) | view::take<1>() | at<0>();
*/
namespace tupleple
{
	namespace view
	{
		template<size_t N,class Tuple>
		struct take_view :utility::base_view<take_view<N,Tuple>, Tuple>
		{
			take_view(Tuple&&tuple)
				:isuper(std::forward<Tuple>(tuple))
			{}
		};
		template<size_t N>
		struct take_functor:utility::ExtensionMemberFunction
		{
			template<class Tuple>
			take_view<N, Tuple> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple) };
			}
		};
		template<size_t N>
		inline take_functor<N> take(){ return{}; }

	}
	template <size_t N, class Tuple>
	struct tuple_trait<view::take_view<N, Tuple>>
		:utility::view_tuple_trait_helper<view::take_view<N, Tuple>>
	{
		static const size_t size = N;
		template<size_t Idx>
		using element = base_element<Idx>;

		template<size_t N, class T>
		using result_type_of
			= base_result_type_of<N, T>;

		template<size_t N, class T>
		static auto get(T&&x)
			->result_of_t<N, T>
		{
			return base_forward<T>(x) | at<N>();
		}
	};
}