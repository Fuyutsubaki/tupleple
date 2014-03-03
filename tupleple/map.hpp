#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"
#include<type_traits>
/*
using tuple = std::tuple<char, int, void*>;
using r = tupleple::type_list::map<std::add_pointer, tuple>;
*/

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
		namespace impl
		{
			template<template<class T>class Transform, class Tuple>
			class map_impl
			{
				using seq = index::make_N_index<size<Tuple>::value>;
				template<size_t ...N>
				static auto trans(std::tuple<index::Index<N> ...>)
					->std::tuple<typename Transform<at<N, Tuple>>::type...>;
			public:
				using type = decltype(trans(seq()));
			};
		}

		template<template<class T>class Transform, class Tuple>
		using map = typename impl::map_impl<Transform, Tuple>::type;
	}
	namespace deteil
	{
		template<class Func,class Tuple>
		class map_impl
		{
			template<class T>
			using map_r = std::result_of<Func(T)>;
		public:
			using type = type_list::map<map_r, Tuple>;
			template<class Func, class Tuple, size_t ...N>
			static type map(const Func&func, const Tuple&tuple, std::tuple<index::Index<N>...>)
			{
				return type(func(at<N>(tuple))...);
			}
		};
	}
	template<class Func,class Tuple>
	typename deteil::map_impl<Func,Tuple>::type map(const Func&func, const Tuple&tuple)
	{
		using seq = index::make_N_index<type_list::size<Tuple>::value>;
		return deteil::map_impl<Func, Tuple>::map(func, tuple, seq());
	}
}