#pragma once
#include"drop.hpp"
#include"take.hpp"
#include"map.hpp"
#include"tuple.hpp"

/*
template<class L,class R>
struct MaxSize
{
	using type = tupleple::utility::cond<(sizeof(L)>sizeof(R)), L, R > ;
};
int main()
{
	using tuple = std::tuple<char, long long, int>;
	using t = tupleple::type_list::binary_fold1<MaxSize, tuple>;
	std::cout << typeid(t).name();
}
*/


namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			namespace deteil
			{
				template<size_t tuple_size, template<class L, class R>class binary_transform_class, class Tuple>
				class binary_fold_impl2;
				template<template<class L, class R>class binary_transform_class, class Tuple>
				struct binary_fold_impl :binary_fold_impl2<size<Tuple>::value, binary_transform_class, Tuple>
				{
					//using type=;
				};
				template<size_t tuple_size, template<class L, class R>class binary_transform_class, class Tuple>
				class binary_fold_impl2
				{
					using lhs = take<tuple_size / 2, Tuple>;
					using rhs = drop<tuple_size / 2, Tuple>;
					using lhs_res = typename binary_fold_impl<binary_transform_class, lhs>::type;
					using rhs_res = typename binary_fold_impl<binary_transform_class, rhs>::type;
				public:
					using type = typename binary_transform_class<lhs_res, rhs_res>::type;
				};
				template<template<class L, class R>class binary_transform_class, class Tuple>
				struct binary_fold_impl2<1, binary_transform_class, Tuple>
				{
					using type = at<0, Tuple>;
				};
			}

			template<template<class L, class R>class binary_transform_class, class Tuple>
			struct binary_fold_impl1
				:deteil::binary_fold_impl<binary_transform_class, Tuple>
			{
				//using type=;
			};
			template<template<class L, class R>class binary_transform_class, class Tuple, template<class R>class pre_transform_class>
			struct binary_fold_impl
				:deteil::binary_fold_impl<binary_transform_class, map<pre_transform_class,Tuple>>
			{
				//using type=;
			};
		}
		//ê[Ç≥O(log N)
		//(+(+1 (+2 3))(+(+4 5)(+6 7)))
		template<template<class L, class R>class binary_transform_class, class Tuple, template<class R>class pre_transform_class>
		using binary_fold = typename impl::binary_fold_impl<binary_transform_class, Tuple, pre_transform_class>::type;

		template<template<class L, class R>class binary_transform_class, class Tuple>
		using binary_fold1 = typename impl::binary_fold_impl1<binary_transform_class, Tuple>::type;

	}

	namespace deteil
	{
		
	}
	template<class binary_Func,class Tuple>
	void binary_fold(const binary_Func&func, const Tuple&tuple)
	{
		static const size_t N = type_list::size<Tuple>::value;
		func(
			binary_fold(func,take<N/2>(tuple))
			, binary_fold(func, drop<N / 2>(tuple))
			);
	}
}