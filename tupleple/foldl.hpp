#pragma once 
#include<tuple>
#include"tuple.hpp"
#include"cons.hpp"
/*
template<class L, class R>
struct Maxsize
{
	using type = typename tupleple::utility::if_ < (sizeof(L)>sizeof(R)), L, R>::type;
};

int main()
{
	using tuple = std::tuple<char, int, long>;
	using type = tupleple::type_list::foldl<Maxsize, tuple>::type;
	std::cout << typeid(type).name();
}
*/

namespace tupleple
{
	namespace type_list
	{
		//(+ (+ (+ (+ 0 1) 2) 3) 4)
		namespace deteil
		{
			template<size_t N,class Tuple, template<class L, class R>class Transform>
			class fold_impl
			{
				using rhs = typename at<N, Tuple>::type;
				using lhs = typename fold_impl<N - 1, Tuple, Transform>::type;
			public:
				using type = typename Transform<lhs, rhs>::type;
			};
			template<class Tuple, template<class L, class R>class Transform>
			struct fold_impl<0, Tuple, Transform>
			{
				using type = typename at<0, Tuple>::type;
			};
		}

		template<template<class L, class R>class Transform, class ...R>
		class foldl;

		template<class Tuple,template<class L,class R>class Transform>
		struct foldl<Transform, Tuple>
		{
			using type = typename deteil::fold_impl<size<Tuple>::value - 1, Tuple, Transform>::type;
		};

		template<template<class L_ist, class R_eturn>class Transform, class Tuple, class Init>
		struct foldl<Transform, Tuple, Init>
		{
			using type = typename foldl < Transform, typename cons<Init,Tuple>::type>::type;
		};
	}
}