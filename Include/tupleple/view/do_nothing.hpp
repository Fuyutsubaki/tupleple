#pragma once
#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\mem_forward.hpp>

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
		using result_type_of
			= result_of<N, decltype(utility::mem_forward<Tuple>(std::declval<T>().base))> ;
		
		template<size_t N,class T>
		static auto get(T&&x)
			->result_of_t<N,T>
		{
			return utility::mem_forward<Tuple>(std::forward<T>(x).base) | at<N>();
		}
	};

}