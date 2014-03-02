#pragma once
#include"drop.hpp"
#include"take.hpp"
#include"map.hpp"
#include"tuple.hpp"

namespace tupleple
{
	namespace type_list
	{
		namespace deteil
		{
			template<size_t tuple_size, template<class L, class R>class binary_transform_class, class Tuple>
			class binary_fold_impl2;
			template<template<class L, class R>class binary_transform_class, class Tuple>
			struct binary_fold_impl :binary_fold_impl2<size<Tuple>::value, binary_transform_class,Tuple>
			{
				//using type=;
			};
			template<size_t tuple_size,template<class L, class R>class binary_transform_class, class Tuple>
			class binary_fold_impl2
			{
				using lhs = typename  take<tuple_size / 2, Tuple>::type;
				using rhs = typename  drop<tuple_size / 2, Tuple>::type;
				using lhs_res = typename binary_fold_impl<binary_transform_class, lhs>::type;
				using rhs_res = typename binary_fold_impl<binary_transform_class, rhs>::type;
			public:
				using type = typename binary_transform_class<lhs_res, rhs_res>::type;
			};
			template<template<class L, class R>class binary_transform_class, class Tuple>
			struct binary_fold_impl2<1, binary_transform_class,Tuple>
			{
				using type =typename at<0,Tuple>::type;
			};
		}
		
		template<template<class L, class R>class binary_transform_class, class Tuple, template<class R>class ...pre_transform_class>
		struct binary_fold;
		//ê[Ç≥O(log N)
		//(+(+1 (+2 3))(+(+4 5)(+6 7)))
		template<template<class L, class R>class binary_transform_class, class Tuple>
		struct binary_fold<binary_transform_class,Tuple>
			:deteil::binary_fold_impl<binary_transform_class,Tuple>
		{
			//using type=;
		};

		template<template<class L, class R>class binary_transform_class, class Tuple, template<class R>class pre_transform_class>
		struct binary_fold <binary_transform_class, Tuple, pre_transform_class>
			:deteil::binary_fold_impl<binary_transform_class, typename map<pre_transform_class, Tuple>::type>
		{
			//using type=;
		};
	}
}