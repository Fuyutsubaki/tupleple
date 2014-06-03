#pragma once
#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\mem_forward.hpp>
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
		{
			Tuple base;
			friend tuple_trait<view::reverse_view<Tuple>>;
		public:
			reverse_view(Tuple&&tuple)
				:base(std::forward<Tuple>(tuple))
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
	{
		using Base = utility::remove_cv_ref_t<Tuple>;
		using View = view::reverse_view<Tuple>;
		static const size_t size = type_list::size<Base>::value;

		template<size_t Idx>
		using element = type_list::at_t<size - 1 - Idx, Base>;

		template<size_t N, class T>
		using result_type_of
			= result_of<size - 1 - N, decltype(utility::mem_forward<Tuple>(std::declval<T>().base))>;

		template<size_t Idx, class T>
		static auto get(T&&x)
			->result_of_t<Idx,T>
		{
			return utility::mem_forward<Tuple>(std::forward<T>(x).base) | at<size - 1 - Idx>();
		}

	};

}