#pragma once 
#include<tupleple\utility\utility.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\type_list\List.hpp>
#include<tupleple\type_list\map.hpp>
#include<tupleple\utility\to_typelist.hpp>

namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct drop
			:drop<N, utility::to_typelist_t<Tuple>>
		{};
		


		namespace deteil
		{
			//VS‚¾‚Ætypename T::type...‚Æ‚©‚ª³í‚É“®‚©‚È‚¢‚±‚Æ‚ª‚ ‚é
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
		struct drop<N, List<T...>>
		{
			using type = map_t<typename deteil::drop_impl<index::make_List_t<N>, T...>::type, deteil::unwrap>;
		};
		template<size_t N, class Tuple>
		using drop_t = typename drop<N, Tuple>::type;
	}
}

