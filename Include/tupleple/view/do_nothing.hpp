#pragma once
#include"tuple.hpp"


namespace tupleple
{
	namespace view
	{
		template<class Tuple>
		struct do_nothing_view
		{
			Tuple base;
			friend tuple_trait<view::do_nothing_view<Tuple>>;
		public:
			do_nothing_view(Tuple&&tuple)
				:base(std::forward<Tuple>(tuple))
			{}
		};
		
		struct do_nothing_functor:utility::ExtensionMemberFunction
		{
			template<class T>
			inline do_nothing_view<T> operator()(T&&tuple)
			{
				return{ std::forward<T>(tuple) };
			}
		};

		inline do_nothing_functor do_nothing(){ return{}; }
	}
	template<class Tuple>
	struct tuple_trait<view::do_nothing_view<Tuple>>
	{
		using base = utility::remove_cv_ref_t<Tuple>;
		static const size_t size = type_list::size<base>::value;

		template<size_t N>
		using element = type_list::at<N, base>;

		template<size_t N,class T>
		using result_of
			= type_list::result_of<N, utility::result_of_forward_mem_t<T, Tuple>>;
		
		template<size_t N,class T>
		static auto get(T&&x)
			->type_list::result_of_t<N,T>
		{
			return utility::forward_mem<T, Tuple>(x.base) | at<N>();
		}
	};

}