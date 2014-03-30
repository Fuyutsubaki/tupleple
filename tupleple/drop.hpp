#pragma once 
#include"tuple.hpp"
/*
using namespace tupleple;
auto tuple = std::make_tuple(1, std::make_unique<int>(2), 3);
auto x = tuple | view::drop<1>();
auto i = at<0>(std::move(x));*/

namespace tupleple
{
	namespace view
	{
		template<size_t N, class c_ref_Tuple>
		struct drop_view
		{
			drop_view(c_ref_Tuple&&tuple)
			:base_tuple(std::forward<c_ref_Tuple>(tuple))
			{}
			c_ref_Tuple&& base_tuple;
		};
		template<size_t N>
		struct drop_foward
		{
			template<class Tuple>
			friend drop_view<N, Tuple> operator|(Tuple&&tuple, drop_foward)
			{
				return drop_view<N, Tuple>(std::forward<Tuple>(tuple));
			}
		};
		template<size_t N>
		inline drop_foward<N> drop(){ return drop_foward<N>(); }
	}

	namespace type_list
	{
		template<size_t N, class Tuple>
		struct drop
		{
			using type = view::drop_view<N, Tuple>;
		};
		template<size_t N, class Tuple>
		using drop_t = typename drop<N, Tuple>::type;
	}

	template <size_t N, class c_ref_Tuple>
	class tuple_trait<view::drop_view<N, c_ref_Tuple>>
	{
		using base_type = utility::remove_const_ref_t<c_ref_Tuple>;
	public:
		static const size_t size = type_list::size<base_type>::value - N;
		template<size_t K>
		struct element
		{
			using type = type_list::at_t<K, base_type>;
		};
		template<size_t Idx, class T>
		static auto get(T&&tuple)
			->utility::trace_const_ref_t<T, typename element<Idx + N>::type>&&
		{
			return at<Idx + N>(utility::forward_mem<T>(tuple.base_tuple));
		}
	};
}

