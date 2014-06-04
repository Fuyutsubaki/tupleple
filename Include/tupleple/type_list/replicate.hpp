#pragma once
#include"List.hpp"
#include"map.hpp"
#include<tupleple\index_tuple\index_TypeList.hpp>
#include"apply.hpp"
namespace tupleple
{
	namespace type_list
	{
		template<size_t N,class T>
		struct replicate
		{
			template<class>
			struct Impl
			{
				using type = T;
			};
			using type = map_t <index::make_List_t<N>, Impl>;
		};
		template<size_t N, class T>
		using replicate_t = typename replicate<N, T>::type;
	}
}