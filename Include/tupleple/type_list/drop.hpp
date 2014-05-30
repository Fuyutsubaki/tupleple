#pragma once 
#include<tupleple\view\drop.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\type_list\List.hpp>
#include<tupleple\type_list\map.hpp>
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
			//VSÇæÇ∆typename T::type...Ç∆Ç©Ç™ê≥èÌÇ…ìÆÇ©Ç»Ç¢Ç±Ç∆Ç™Ç†ÇÈ
			template<class T>
			struct unwrap
			{
				using type = typename T::type;
			};
			template<class...>struct drop_impl{};
			template<class...Idxs,class...T>
			struct drop_impl<List<Idxs...>,T...>
			{
				template<class...R>
				static auto trans(utility::Ignore_class<Idxs>..., R...)
					->List<R...>;
				using type = decltype(trans(utility::identity<T>{}...));
			};
		}
		template<size_t N, class ...T>
		struct drop<N,List<T...>>
		{
			using type = map_t<typename deteil::drop_impl<index::make_List_t<N>, T...>::type, deteil::unwrap>;
		};
		template<size_t N, class Tuple>
		using drop_t = typename drop<N, Tuple>::type;
	}
}

