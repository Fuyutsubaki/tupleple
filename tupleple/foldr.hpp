#pragma once
#include"tuple.hpp"
#include"Index.hpp"
#include"push.hpp"
/*
template<class L, class R>
struct Maxsize
{
	using type = tupleple::utility::cond < (sizeof(L)>sizeof(R)), L, R>;
};

int main()
{
	using tuple = std::tuple<char, int,long long>;
	using type = tupleple::type_list::foldr1<Maxsize, tuple>;
	std::cout << typeid(type).name();
}

*/

namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			namespace deteil
			{
				template<bool is_back, size_t N, class Tuple, template<class L, class R>class Transform>
				class foldr_impl2;
				template<size_t N, class Tuple, template<class L, class R>class Transform>
				struct foldr_impl :foldr_impl2<(N == (size<Tuple>::value - 1)), N, Tuple, Transform>
				{

				};
				template<size_t N, class Tuple, template<class L, class R>class Transform>
				class foldr_impl2<false, N, Tuple, Transform>
				{
					using rhs = typename foldr_impl<N + 1, Tuple, Transform>::type;
					using lhs = at<N, Tuple>;
				public:
					using type = typename Transform<lhs, rhs>::type;
				};
				template<size_t N, class Tuple, template<class L, class R>class Transform>
				struct foldr_impl2<true, N, Tuple, Transform>
				{
					using type = at<N, Tuple>;
				};
			}
			template<template<class L_ist, class R_eturn>class Transform, class Tuple>
			struct foldr1
			{
				using type = typename deteil::foldr_impl<0, Tuple, Transform>::type;
			};

			
			template<template<class L_ist, class R_eturn>class Transform, class Tuple, class Init>
			struct foldr
			{
				using type = typename foldr1 < Transform, push<Tuple, Init>>::type;
			};
		}

		//(&&1(&&2(&&3 4)))
		template<template<class L_ist, class R_eturn>class Transform, class Tuple>
		using foldr1 = typename impl::foldr1<Transform, Tuple>::type;
		//(&&1(&&2(&&3 Init)))
		template<template<class L_ist, class R_eturn>class Transform, class Tuple, class Init>
		using foldr = typename impl::foldr<Transform, Tuple, Init>::type;
	}


}