#pragma once
#include"tuple.hpp"
/*
auto x=tupleple::reverse(std::make_tuple(1,2,3,4));
*/

namespace tupleple
{
	namespace view
	{
		template<class Tuple>
		struct reverse_view
		{
			friend tuple_trait<view::reverse_view<Tuple>>;
			reverse_view(Tuple&&tuple)
			:base(std::forward<Tuple>(tuple))
			{}
		private:
			Tuple&&base;
		};
		struct reverse_foward:utility::ExtensionMemberFunction
		{
			template<class Tuple>
			reverse_view<Tuple> operator()(Tuple&&tuple)
			{
				return reverse_view<Tuple>(std::forward<Tuple>(tuple));
			}
		};
		inline reverse_foward reverse(){ return reverse_foward(); }
	}
	template<class Tuple>
	struct tuple_trait<view::reverse_view<Tuple>>
	{
		using Base = utility::remove_const_ref_t<Tuple>;
		static const size_t size = type_list::size<Base>::value;
		template<size_t Idx>
		struct element
		{
			using type = type_list::at_t<size - 1 - Idx, Base>;
		};
		template<size_t Idx, class T>
		static auto get(T&&tuple)
			->decltype(at <size - 1 - Idx>(utility::foward_member_ref<T, Tuple>(tuple.base)))
		{
			return utility::foward_member_ref<T, Tuple>(tuple.base) | at < size - 1 - Idx>();
		}

	};

}