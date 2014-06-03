#ifndef TUPPLEPLE_VIEW_MAP_HPP
#define TUPPLEPLE_VIEW_MAP_HPP

#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\mem_forward.hpp>
/*
using namespace tupleple;
auto r = std::make_tuple(3.5, 1, 3.14, 1.414);
auto c = r | view::map([](double d){return d * 2; });
auto d = c | at<2>();

*/
namespace tupleple{

	namespace view
	{
		template<class Tuple, class Functor>
		struct map_view
		{
			Tuple base;
			Functor func;
			friend tuple_trait<view::map_view<Tuple, Functor>>;
		public:
			map_view(Tuple&&tuple, Functor&&func)
				:base(std::forward<Tuple>(tuple))
				, func(std::forward<Functor>(func))
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
	class tuple_trait<view::map_view<Tuple, Func>>
	{
		using base = utility::remove_cv_ref_t<Tuple>;
	public:
		static const size_t size = type_list::size<base>::value;

		template<size_t N>
		using element
			= utility::remove_cv_ref_t<typename std::result_of<Func(type_list::at_t<N, base>)>::type>;

		template<size_t N, class T>
		using result_type_of
			= std::result_of<
			decltype(utility::mem_forward<Func>(std::declval<T>().func))
			(result_of_t<N, decltype(utility::mem_forward<Tuple>(std::declval<T>().base))>)
			>;

		template<size_t N, class T>
		static auto get(T&&x)
			->result_of_t<N, T>
		{
			return
				utility::mem_forward<Func>(std::forward<T>(x).func)
				(
				utility::mem_forward<Tuple>(std::forward<T>(x).base) | at<N>()
				);
		}
	};



}




#endif