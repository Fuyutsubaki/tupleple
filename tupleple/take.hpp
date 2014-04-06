#pragma once 
#include"tuple.hpp"
/*
	using namespace tupleple;
	auto tuple = std::make_tuple(1, std::make_unique<int>(2), 3);
	auto x = tuple | view::take<2>();
	auto i = at<1>(std::move(x));
*/
namespace tupleple
{
	namespace view
	{
		template<size_t N, class c_ref_Tuple>
		struct take_view
		{
			take_view(c_ref_Tuple&&tuple)
			:base_tuple(std::forward<c_ref_Tuple>(tuple))
			{}
			c_ref_Tuple&& base_tuple;
		};
		template<size_t N>
		struct take_foward
		{
			template<class Tuple>
			friend take_view<N, Tuple> operator|(Tuple&&tuple, take_foward)
			{
				return take_view<N, Tuple>(std::forward<Tuple>(tuple));
			}
		};
		template<size_t N>
		inline take_foward<N> take(){ return take_foward<N>(); }
	}
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct take
		{
			using type = view::take_view<N, Tuple>;
		};
		template<size_t N, class Tuple>
		using take_t = typename take<N, Tuple>::type;
	}

	template <size_t N, class c_ref_Tuple>
	class tuple_trait<view::take_view<N, c_ref_Tuple>>
	{
	public:
		static const size_t size = N;
		template<size_t K>
		struct element
		{
			using base_type = utility::remove_const_ref_t<c_ref_Tuple>;
			using type = type_list::at_t<K, base_type>;
		};
		template<size_t Idx,class T>
		static auto get(T&&tuple)
			->decltype(at<Idx>(utility::foward_member_ref<T, c_ref_Tuple>(tuple.base_tuple)))
		{
			return utility::foward_member_ref<T, c_ref_Tuple>(tuple.base_tuple) | at<Idx>();
		}
	};






}