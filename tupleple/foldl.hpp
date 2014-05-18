#pragma once
#include"tuple.hpp"
#include"ListStyle.hpp"
#include"move_view.hpp"


namespace tupleple
{

	namespace algorithm
	{
		namespace deteil
		{
			template<class Init, class Tuple, class Functor,class =void>
			struct foldl_impl
			{
				using L = std::result_of_t<Functor(Init, decltype(std::declval<Tuple>() | view::front()))>;
				using R = decltype(std::declval<Tuple>() | view::tail());
				using Next = foldl_impl<L, R, Functor>;
				using result_type = typename Next::result_type;
				static result_type fold(Init&&init, Tuple&&tuple, Functor&&func)
				{
					return Next::fold
						(
						std::forward<Functor>(func)(std::forward<Init>(init), std::forward<Tuple>(tuple) | view::front())
						, std::forward<Tuple>(tuple) | view::tail()
						, std::forward<Functor>(func)
						);
				}
			};
			template<class Init, class Tuple, class Functor>
			struct foldl_impl<Init,Tuple,Functor
				, typename std::enable_if<(type_list::size<utility::remove_cv_ref_t<Tuple>>::value == 0)>::type>
			{
				using result_type = Init;
				static result_type fold(Init&&init, Tuple&&, Functor&&)
				{
					return std::forward<Init>(init);
				}
			};
		}
		template<class Init, class Tuple, class Functor>
		auto foldl(Init&&init, Tuple&&tuple, Functor&&func)
			->typename deteil::foldl_impl<Init, result_of_forward_view_t<Tuple>, Functor>::result_type
		{
			
			return deteil::foldl_impl<Init, decltype(forward_view<Tuple>(std::forward<Tuple>(tuple))), Functor>::
				fold(
				std::forward<Init>(init)
				, forward_view<Tuple>(std::forward<Tuple>(tuple))
				,std::forward<Functor>(func)
				);
		}
	}

	



}