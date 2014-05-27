#pragma once 
#include<tupleple\view\drop.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\index_tuple.hpp>
/*
using namespace tupleple;
auto tuple = std::make_tuple(1, std::make_unique<int>(2), 3);
auto x = std::move(tuple) | view::drop<1>();
auto i = at<0>(std::move(x));
*/

namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct drop
		{
			using type = view::drop_view<N, Tuple>;
		};
		


		namespace deteil
		{
			template<class...>struct drop_impl{};
			template<class...Idxs,class...T>
			struct drop_impl<std::tuple<Idxs...>,T...>
			{
				template<class...R>
				static auto trans(utility::Ignore_class<Idxs>..., R...)
					->std::tuple<typename utility::unwrap<R>::type ...>;
				using type = decltype(trans(utility::identity<T>{}...));
			};
		}
		template<size_t N, class ...T>
		struct drop<N,std::tuple<T...>>
		{
			using type = typename deteil::drop_impl<index::make_tuple_t<N>, T...>::type;
		};
		template<size_t N, class Tuple>
		using drop_t = typename drop<N, Tuple>::type;
	}
}

