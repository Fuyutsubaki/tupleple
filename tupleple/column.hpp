#pragma once
#include"tuple.hpp"
#include"base_view.hpp"
#include"STD_tuple_traits.hpp"
namespace tupleple
{
	namespace view
	{
		template<size_t N,class Tuple>
		struct column_view :impl::base_view<column_view<N,Tuple>,Tuple>
		{
			column_view(Tuple&&tuple)
			:isuper(std::forward<Tuple>(tuple))
			{}
		};
		template<size_t N>
		struct column_functor :utility::ExtensionMemberFunction
		{
			template<class T>
			inline column_view<N,T> operator()(T&&tuple)
			{
				return{ std::forward<T>(tuple) };
			}
		};
		template<size_t N>
		inline column_functor<N> column(){ return{}; }
	}
	namespace type_list
	{
		template<size_t N,class Tuple>
		struct column
		{
			using type = view::column_view<N, Tuple>;
		};
		template<size_t N, class Tuple>
		using column_t = typename column<N, Tuple>::type;
	}
	template<size_t N, class Tuple>
	struct tuple_trait<view::column_view<N,Tuple>>
	{
		using base = utility::remove_cv_ref_t<Tuple>;
		static const size_t size = type_list::size<base>::value;

		template<size_t Idx>
		using element = type_list::at<N, type_list::at<Idx, base>>;

		template<size_t Idx, class T>
		using result_of
			= type_list::result_of<N,
			type_list::result_of_t<Idx, utility::result_of_forward_mem_t<T, Tuple>>
			>;

		template<size_t Idx, class T>
		static auto get(T&&x)
			->type_list::result_of_t<Idx, T>
		{
			return utility::forward_mem<T, Tuple>(x.base) | at<Idx>() | at<N>();
		}
	};
}