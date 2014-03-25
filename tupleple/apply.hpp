#pragma once
#include"tuple.hpp"
#include"Index.hpp"
#include"utility.hpp"

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class...>class T>
		class apply
		{
			template<size_t ...N>
			static auto trans(index::Sequence<N...>)
				->T<at<N, Tuple>...>;
			using type = decltype(trans(index::make_seq<size<Tuple>::value>()));
		};
		template<class Tuple, template<class...>class T>
		using apply_t = typename apply<Tuple, T>::type;
	}
	namespace deteil
	{
		template<class Tuple, class Func, size_t ...N>
		typename type_list::apply<Tuple, typename utility::template carry_variadic_result_of<Func>::type>::type 
			apply_impl(Tuple&&tuple, Func &func, index::Sequence<N...>)
			
		{
			return func(at<N>(tuple)...);
		}
	}
	template<class Tuple,class Func>
	type_list::apply<Tuple, typename utility::template carry_variadic_result_of<Func>::type> apply(Tuple&&tuple, Func &func)
	{
		return deteil::apply_impl(tuple, func, index::make_seq<type_list::size<Tuple>::value>);
	}
}