#pragma once 

#include<tupleple\utility\view_impl_helper.hpp>
/*
using namespace tupleple;
auto tuple = std::make_tuple(1, std::make_unique<int>(2), 3);
auto x = std::move(tuple) | view::drop<1>();
auto i = at<0>(std::move(x));
*/

namespace tupleple
{
	namespace view
	{
		template<size_t N, class Tuple>
		struct drop_view
			:utility::base_view<drop_view<N,Tuple>,Tuple>
		{
			drop_view(Tuple&&tuple)
				:isuper(std::forward<Tuple>(tuple))
			{}
		};
		
		template<size_t N>
		struct drop_functor :utility::ExtensionMemberFunction
		{
			template<class Tuple>
			drop_view<N, Tuple> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple) };
			}
		};
		template<size_t N>
		inline drop_functor<N> drop(){ return{}; }

	}
	template <size_t N, class Tuple>
	struct tuple_trait<view::drop_view<N, Tuple>>
		:utility::view_tuple_trait_helper<view::drop_view<N, Tuple>>
	{
		static const size_t size = base_size - N;
		template<size_t Idx>
		using element = base_element<Idx + N>;

		template<size_t Idx, class T>
		using result_type_of
			= base_result_type_of<Idx + N, T>;

		template<size_t Idx, class T>
		static auto get(T&&x)
			->result_of_t<Idx, T>
		{
			return base_forward<T>(x) | at<Idx + N>();
		}
	};
}

