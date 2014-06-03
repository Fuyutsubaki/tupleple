#pragma once 

#include<tupleple\utility\base_view.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\mem_forward.hpp>
/*
	using namespace tupleple;
	std::make_tuple(1, std::make_unique<int>(2), 3) | view::take<1>() | at<0>();
*/
namespace tupleple
{
	namespace view
	{
		template<size_t N,class Tuple>
		struct take_view :utility::base_view<take_view<N,Tuple>, Tuple>
		{
			take_view(Tuple&&tuple)
				:isuper(std::forward<Tuple>(tuple))
			{}
		};
		template<size_t N>
		struct take_functor:utility::ExtensionMemberFunction
		{
			template<class Tuple>
			take_view<N, Tuple> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple) };
			}
		};
		template<size_t N>
		inline take_functor<N> take(){ return{}; }

	}
	template <size_t N, class Tuple>
	class tuple_trait<view::take_view<N, Tuple>>
	{
		using View = view::take_view<N, Tuple>;
		using base_type = utility::remove_cv_ref_t<Tuple>;
	public:
		static const size_t size = N;
		template<size_t N>
		using element = type_list::at<N, base_type>;

		template<size_t N, class T>
		using result_type_of
			= result_of<N, utility::result_of_mem_forward_t<T, Tuple>>;

		template<size_t N, class T>
		static auto get(T&&x)
			->result_of_t<N, T>
		{
			return utility::mem_forward<Tuple>(x.base) | at<N>();
		}
	};
}