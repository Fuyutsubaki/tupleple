#pragma once
#include<tupleple\view\take.hpp>
#include<tupleple\view\drop.hpp>
#include<tupleple\view\ListStyle.hpp>


namespace tupleple
{
	namespace algorithm
	{
		template<class Tuple, class Func
			, typename std::enable_if<(type_list::size<utility::remove_cv_ref_t<Tuple>>::value != 1)>::type* =nullptr >
		Func& for_each(Tuple&&tuple, Func&func)
		{
			static const size_t N = type_list::size<utility::remove_cv_ref_t<Tuple>>::value;
			for_each(std::forward<Tuple>(tuple) | view::take<N / 2>(),func);
			for_each(std::forward<Tuple>(tuple) | view::drop<N / 2>(),func);
			return func;
		}
		template<class Tuple, class Func
			, typename std::enable_if<(type_list::size<utility::remove_cv_ref_t<Tuple>>::value == 1)>::type* = nullptr >
			Func& for_each(Tuple&& tuple, Func&func)
		{
				func(std::forward<Tuple>(tuple) | view::front());
				return func;
		}
	}
}