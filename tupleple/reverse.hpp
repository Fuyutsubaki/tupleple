#pragma once
#include"tuple.hpp"
#include"utility.hpp"

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
		using result_of
			= type_list::result_of<size - 1 - N, utility::result_of_forward_mem_t<T, Tuple>>;

		template<size_t Idx, class T>
		static auto get(T&&x)
			->type_list::result_of_t<Idx,T>
		{
			return utility::forward_mem<T, Tuple>(x.base) | at<size - 1 - Idx>();
		}

	};

}