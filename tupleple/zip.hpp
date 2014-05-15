#pragma once
#include<tuple>
#include"Index.hpp"
#include"map.hpp"
#include"base_view.hpp"
#include"column.hpp"
/*
char c = 'X';
int x = 42;
float f = 3.14;
auto t1 = std::make_tuple(c, x, f);
auto t2 = std::tie(c, x, f);
auto t3 = std::make_tuple(&c, &x, &f);

auto result = tupleple::zip(t1,t2,t3);

*/
namespace tupleple
{
	
	namespace view
	{
		template<class Tuple>
		struct zip_view:impl::base_view<zip_view<Tuple>,Tuple>
		{
			zip_view(Tuple&&tuple)
			:isuper(std::forward<Tuple>(tuple))
			{}
		};

		template<class...Tuples>
		auto zip(Tuples&&...tuples)
			->zip_view<std::tuple<Tuples...>>
		{
			return{ std::tuple<Tuples...>{ std::forward<Tuples>(tuples)... } };
		}
	}
	template<class Tuple>
	class tuple_trait<view::zip_view<Tuple>>
	{
	public:
		static const size_t size = 0xdeadc0de;

		template<size_t Idx>
		using element = type_list::column<Idx, Tuple>;

		template<size_t Idx, class T>
		using result_of = type_list::column<Idx, utility::result_of_forward_mem_t<T, Tuple>>;

		template<size_t Idx, class T>
		static auto get(T&&tuple)
		->type_list::result_of_t<Idx, T>
		{
			return{ utility::forward_mem<T,Tuple>(tuple.base) };
		}
	};
}