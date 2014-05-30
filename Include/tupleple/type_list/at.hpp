#ifndef TUPLEPLE_TYPELIST_AT_HPP
#define TUPLEPLE_TYPELIST_AT_HPP
#include"List.hpp"
#include<tupleple\index_tuple\index_TypeList.hpp>
namespace tupleple{
	namespace type_list
	{
		template<size_t N,class C,class Enaber=void>
		struct at
		{};


		namespace deteil
		{
			
			template<class...>struct at_impl{};
			template<class...Idxs, class...T>
			struct at_impl<List<Idxs...>, T...>
			{
				template<class T,class...R>
				static auto trans(utility::Ignore_class<Idxs>..., T, R...)
					->typename T::type;
				using type = decltype(trans(utility::identity<T>{}...));
			};
		}

		template<size_t N, class...T>
		struct at<N,List<T...>>
		{
			using type = typename deteil::at_impl<index::make_List_t<N>, T...>::type;
		};
		template<size_t N,class T>
		using at_t = typename at<N, T>::type;
	}
}



#endif