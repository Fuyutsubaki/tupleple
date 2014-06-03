#pragma once 

#include<tupleple\utility\utility.hpp>
#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\mem_forward.hpp>
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
		{
			Tuple base;
			friend tuple_trait<view::drop_view<N,Tuple>>;
		public:
			drop_view(Tuple&&tuple)
				:base(std::forward<Tuple>(tuple))
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
	class tuple_trait<view::drop_view<N, Tuple>>
	{
		using View = view::drop_view<N, Tuple>;
		using base_type = utility::remove_cv_ref_t<Tuple>;
	public:
		static const size_t size = type_list::size<base_type>::value - N;
		template<size_t Idx>
		using element = type_list::at<Idx + N, base_type>;

		template<size_t Idx, class T>
		using result_type_of
			= result_of < N + Idx, decltype(utility::mem_forward<Tuple>(std::declval<T>().base)) >;

		template<size_t Idx, class T>
		static auto get(T&&x)
			->result_of_t<Idx, T>
		{
			return utility::mem_forward<Tuple>(std::forward<T>(x).base)
				| at<Idx + N>();
		}
	};
}

