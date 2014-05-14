#pragma once 
#include"tuple.hpp"
#include"base_view.hpp"
/*
	using namespace tupleple;
	std::make_tuple(1, std::make_unique<int>(2), 3) | view::take<1>() | at<0>();
*/
namespace tupleple
{
	namespace view
	{
		template<size_t N,class Tuple>
		struct take_view :impl::base_view<take_view<N,Tuple>, Tuple>
		{
			take_view(Tuple&&tuple)
				:isuper(std::forward<Tuple>(tuple))
			{}
		};
		template<size_t N>
		struct take_forward:utility::ExtensionMemberFunction
		{
			template<class Tuple>
			take_view<N, Tuple> operator()(Tuple&&tuple)
			{
				return take_view<N, Tuple>(std::forward<Tuple>(tuple));
			}
		};
		template<size_t N>
		inline take_forward<N> take(){ return{}; }

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
		using result_of
			= type_list::result_of<N, utility::result_of_forward_mem_t<T, Tuple>>;

		template<size_t N, class T>
		static auto get(T&&x)
			->type_list::result_of_t<N, T>
		{
			return utility::forward_mem<T, Tuple>(x.base) | at<N>();
		}
	};
}