#pragma once
#include<tuple>

#include"map.hpp"
#include<tupleple\utility\view_impl_helper.hpp>
#include"column.hpp"
#include<tupleple\tuple_traits.hpp>
#include<tupleple\type_list\map.hpp>
#include<tupleple\STD_tuple_traits.hpp>

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
		struct zip_view:utility::base_view<zip_view<Tuple>,Tuple>
		{
			zip_view(Tuple&&tuple)
			:isuper(std::forward<Tuple>(tuple))
			{}
		};

		template<class...Tuples>
		auto zip(Tuples&&...tuples)
			->zip_view<std::tuple<Tuples...>>
		{
			return zip_view<std::tuple<Tuples...>>{ std::tuple<Tuples...>{ std::forward<Tuples>(tuples)... } };
		}
	}
	template<class Tuple>
	struct tuple_trait<view::zip_view<Tuple>>
		:utility::view_tuple_trait_helper <view::zip_view<Tuple >>
	{
	public:
		//???
		using head_simpletype = utility::remove_cv_ref_t<base_element_t<0>>;
		static const size_t size = type_list::size<head_simpletype>::value;// type_list::size<x>::value;

		template<size_t Idx>
		using element = utility::identity<view::column_view<Idx, base_type>>;

		template<size_t Idx, class T>
		using result_type_of = utility::identity<
			view::column_view<Idx, result_base_forward_t<T>>>;

		template<size_t Idx, class T>
		static auto get(T&&x)
		->result_of_t<Idx, T>
		{
			return{ base_forward<T>(x) };
		}
	};
}