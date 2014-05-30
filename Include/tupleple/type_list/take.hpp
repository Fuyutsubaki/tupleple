#pragma once 
#include<tupleple\view\take.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\type_list\zip.hpp>

/*
	using namespace tupleple;
	std::make_tuple(1, std::make_unique<int>(2), 3) | view::take<1>() | at<0>();
*/
namespace tupleple
{
	namespace type_list
	{
		template<size_t N, class Tuple>
		struct take
		{
			using type = view::take_view<N, Tuple>;
		};

		namespace deteil
		{
			template<class seq, class list>
			struct take_impl
			{};
			template<size_t...Idxs, class list>
			struct take_impl<index::Sequence<Idxs...>,list>
			{
				using type = List<at_t<Idxs, list>...>;
			};

		}
		template<size_t N, class ...T>
		struct take<N,List<T...>>
		{
			using type = typename deteil::take_impl<index::make_seq_t<N>, List<T...>>::type;
		};

		template<size_t N, class Tuple>
		using take_t = typename take<N, Tuple>::type;
	}
}