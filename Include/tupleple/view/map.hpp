#ifndef TUPPLEPLE_VIEW_MAP_HPP
#define TUPPLEPLE_VIEW_MAP_HPP

#include<tupleple\tuple.hpp>

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
			map_functor(Func&&func)
			:func_(std::forward<Func>(func))
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
		using result_of
			= std::result_of<Func(type_list::result_of_t<N, utility::result_of_forward_mem_t<T, Tuple>>)>;

		template<size_t N, class T>
		static auto get(T&&x)
			->type_list::result_of_t<N, T>
		{
			return
				utility::forward_mem<T, Func>(x.func)
				(
				utility::forward_mem<T, Tuple>(x.base) | at<N>()
				);
		}
	};



}




#endif