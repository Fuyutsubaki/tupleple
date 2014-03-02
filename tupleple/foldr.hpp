#pragma once
#include"tuple.hpp"
#include"Index.hpp"
#include"push.hpp"
/*
template<class L, class R>
struct Maxsize
{
	using type = typename tupleple::utility::if_ < (sizeof(L)>sizeof(R)), L, R>::type;
};

int main()
{
	using tuple = std::tuple<char[42], int,char>;
	using type = tupleple::type_list::foldr<Maxsize, tuple>::type;
	std::cout << typeid(type).name();
}

*/

namespace tupleple
{
	namespace type_list
	{
		//(&&1(&&2(&&3 4)))
		namespace deteil
		{
			template<bool is_back, size_t N, class Tuple, template<class L, class R>class Transform>
			class foldr_impl2;
			template<size_t N, class Tuple, template<class L, class R>class Transform>
			struct foldr_impl :foldr_impl2<(N==(size<Tuple>::value-1)), N, Tuple, Transform>
			{

			};
			template<size_t N, class Tuple, template<class L, class R>class Transform>
			class foldr_impl2<false, N, Tuple, Transform>
			{
				using rhs = typename foldr_impl<N + 1, Tuple, Transform>::type;
				using lhs = typename at<N, Tuple>::type;
			public:
				using type = typename Transform<lhs, rhs>::type;
			};
			template<size_t N,class Tuple, template<class L, class R>class Transform>
			struct foldr_impl2<true,N, Tuple, Transform>
			{
				using type = typename at<N, Tuple>::type;
			};
		}

		template<template<class L, class R>class Transform, class ...R>
		class foldr;
		//(&&1(&&2(&&3 4)))
		template<template<class L_ist, class R_eturn>class Transform, class Tuple>
		struct foldr<Transform, Tuple>
		{
			using type = typename deteil::foldr_impl<0, Tuple, Transform>::type;
		};

		//(&&1(&&2(&&3 Init)))
		template<template<class L_ist, class R_eturn>class Transform, class Tuple, class Init>
		struct foldr<Transform, Tuple,Init>
		{
			using type = typename foldr < Transform, typename push<Tuple, Init>::type>::type;
		};
	}
}