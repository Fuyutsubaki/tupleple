#ifndef TUPPLEPLE_VIEW_MAP_HPP
#define TUPPLEPLE_VIEW_MAP_HPP

#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\mem_forward.hpp>
#include<tupleple\utility\view_impl_helper.hpp>
/*
using namespace tupleple;
auto r = std::make_tuple(3.5, 1, 3.14, 1.414);
auto c = r | view::map([](double d){return d * 2; });
auto d = c | at<2>();

*/
namespace tupleple{

	namespace view
	{
		namespace deteil
		{
			template<class Func>
			struct Functor
			{
				template<class Func>
				Functor(Func&&func)
					:func(std::forward<Func>(func))
				{}
				Func func;
			};
		}
		
		template<class Tuple, class Func>
		struct map_view
			:utility::base_view<map_view<Tuple, Func>, Tuple, deteil::Functor<Func>>
		{
			map_view(Tuple&&tuple, Func&&func)
				:isuper(std::forward<Tuple>(tuple), std::forward<Func>(func))
			{}
		};

		template<class Func>
		struct map_functor :utility::ExtensionMemberFunction
		{
			template<class T>
			map_functor(T&&func)
			:func_(std::forward<T>(func))
			{}
			template<class Tuple>
			map_view<Tuple, Func> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple), std::forward<Func>(func_) };
			}
		private:
			Func func_;
		};

		template<class Func>
		map_functor<Func> map(Func&&func)
		{
			return{ std::forward<Func>(func) };
		}
	}

	template<class Tuple, class Func>
	struct tuple_trait<view::map_view<Tuple, Func>>
		:utility::view_tuple_trait_helper<view::map_view<Tuple, Func>>
	{
		static const size_t size = base_size;

		template<size_t N>
		using element
			= utility::remove_cv_ref_t<typename std::result_of<Func(base_element_t<N>)>::type>;

		template<size_t N, class T>
		using result_type_of
			= std::result_of<
			decltype(utility::mem_forward<Func>(std::declval<T>().func))
			(base_result_type_of_t<N, T>)
			>;

		template<size_t N, class T>
		static auto get(T&&x)
			->result_of_t<N, T>
		{
			return
				utility::mem_forward<Func>(std::forward<T>(x).func)
				(
				base_forward<T>(x) | at<N>()
				);
		}
	};



}




#endif