#pragma once 
#include"tuple.hpp"
#include"utility.hpp"
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
		struct drop_forward :utility::ExtensionMemberFunction
		{
			template<class Tuple>
			drop_view<N, Tuple> operator()(Tuple&&tuple)
			{
				return drop_view<N, Tuple>(std::forward<Tuple>(tuple));
			}
		};
		template<size_t N>
		inline drop_forward<N> drop(){ return{}; }

	}
	namespace result_of
	{

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
		using result_of
			= type_list::result_of<Idx + N, utility::result_of_forward_mem_t<T, Tuple>>;

		template<size_t Idx, class T>
		static auto get(T&&x)
			->type_list::result_of_t<Idx, T>
		{
			return utility::forward_mem<T, Tuple>(x.base) | at<Idx + N>();
		}
	};
}

