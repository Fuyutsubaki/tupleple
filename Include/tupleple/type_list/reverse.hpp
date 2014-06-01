#pragma once
#include"at.hpp"
#include"map.hpp"
#include<tupleple\index_tuple\index_TypeList.hpp>

//using namespace tupleple;
//using namespace type_list;
//static_assert(std::is_same<reverse_t<List<char, int, void>>, List<void, int, char>>::value, "");
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		struct reverse
		{
			
		};
		template<class ...T>
		struct reverse<List<T...>>
		{
			using list = List<T...>;
			static const size_t N = size<list>::value;
			template<class Idx>
			struct trans
			{
				using type = at_t<N - Idx::value - 1, list>;
			};
			using type = map_t<index::make_List_t<N>, trans>;
		};
		template<class Tuple>
		using reverse_t = typename reverse<Tuple>::type;
	}

}