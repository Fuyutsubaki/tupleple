#pragma once 
#include<tuple>
#include"tuple.hpp"
#include"cons.hpp"
/*
template<class L, class R>
struct Maxsize
{
	using type = tupleple::utility::cond < (sizeof(L)>sizeof(R)), L, R>;
};

int main()
{
	using tuple = std::tuple<char, int,long long>;
	using type = tupleple::type_list::foldl1<Maxsize, tuple>;
	std::cout << typeid(type).name();
}
*/

namespace tupleple
{
	namespace type_list
	{
		//(+ (+ (+ (+ 0 1) 2) 3) 4)
		namespace impl{
			namespace deteil
			{
				template<size_t N, class Tuple, template<class L, class R>class Transform>
				class foldl_impl
				{
					using rhs = at<N, Tuple>;
					using lhs = typename foldl_impl<N - 1, Tuple, Transform>::type;
				public:
					using type = typename Transform<lhs, rhs>::type;
				};
				template<class Tuple, template<class L, class R>class Transform>
				struct foldl_impl<0, Tuple, Transform>
				{
					using type = at<0, Tuple>;
				};
			}

			template<template<class, class>class Transform, class Tuple>
			struct foldl1_impl
			{
				using type = typename deteil::foldl_impl<size<Tuple>::value - 1, Tuple, Transform>::type;
			};

			template<template<class L, class R>class Transform, class Tuple, class Init>
			struct foldl_impl
			{
				using type = typename foldl1_impl < Transform, cons<Init, Tuple>>::type;
			};
		}
		template<template<class Result, class Element>class Transform, class Tuple, class Init>
		using foldl = typename impl::foldl_impl<Transform, Tuple, Init>::type;

		template<template<class, class>class Transform, class Tuple>
		using foldl1 = typename impl::foldl1_impl<Transform, Tuple>::type;

	}
}