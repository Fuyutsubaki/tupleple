#pragma once
#include<tuple>

#include"map.hpp"
#include<tupleple\utility\view_impl_helper.hpp>
#include<tupleple\utility\mem_forward.hpp>
#include<tupleple\tuple_traits.hpp>
/*
char c = 'X';
int x = 42;
float f = 3.14;
auto t1 = std::make_tuple(c, x, f);
auto t2 = std::tie(c, x, f);
auto t3 = std::make_tuple(&c, &x, &f);

auto result = tupleple::zip(t1,t2,t3);

*/
namespace tupleple
{
	
	namespace view
	{
		template<std::size_t N, class Tuple>
		struct column_view 
			:utility::base_view<column_view<N, Tuple>, Tuple>
		{
			column_view(Tuple&&tuple)
			:isuper(std::forward<Tuple>(tuple))
			{}
		};
	}
	template<std::size_t N,class Tuple>
	struct tuple_trait<view::column_view<N,Tuple>>
		:utility::view_tuple_trait_helper<view::column_view<N, Tuple>>
	{
		static const std::size_t size = base_size;

		template<size_t Idx>
		using element = base_element_t<Idx>;

		template<size_t Idx, class T>
		using result_type_of = result_of < N, result_of_t<Idx, result_base_forward_t<T>>>;

		template<size_t Idx, class T>
		static auto get(T&&tuple)
			->result_of_t<Idx, T>
		{
			return base_forward<T>(tuple) | at<Idx>() | at<N>();
		}
	};
}