#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"



/*
struct Func
{
	template<class T>
	std::pair<T, size_t> operator()(T x)const
	{
		return std::pair<T, size_t>(x, sizeof(x));
	}
};
int main()
{
	auto r = tupleple::map(Func(), std::make_tuple('X', 3));
}
*/


namespace tupleple
{
	namespace type_list
	{
		template<template<class T>class Transform, class Tuple>
		class map
		{
			using seq = typename index::make_N_index<size<Tuple>::value>::type;
			template<size_t ...N>
			static auto trans(std::tuple<index::Index<N> ...>)
				->std::tuple<typename Transform<typename at<N, Tuple>::type>::type...>;
			template<class ...C>
			static auto trans(std::tuple<C...>)
				->std::tuple<void, void, void>;
		public:
			using type = decltype(trans(seq()));
		};
	}
	namespace deteil
	{
		template<class Func, class Tuple,size_t ...N>
		static auto map_impl(const Func&func, const Tuple&tuple, std::tuple<index::Index<N>...>)
			->std::tuple<decltype(func(at<N>(tuple)))...>
		{
			return std::tuple<decltype(func(at<N>(tuple)))...>(func(at<N>(tuple))...);
		}
		template<class Tuple>
		typename index::make_N_index<type_list::size<Tuple>::value>::type map_impl_index_();
	}
	template<class Func,class Tuple>
	auto map(const Func&func,const Tuple&tuple)
		->decltype(deteil::map_impl(func, tuple, deteil::map_impl_index_<Tuple>()))
	{
		using seq = typename index::make_N_index<type_list::size<Tuple>::value>::type;
		return deteil::map_impl(func,tuple,seq());
	}
}