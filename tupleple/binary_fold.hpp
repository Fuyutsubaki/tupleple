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
		template<class Tuple, template<class L, class R>class binary_transform_class, class Enabler = void>
		class binary_fold1
		{
			static const size_t size = size <Tuple>::value;
			using lhs = take<size / 2, Tuple>;
			using rhs = drop<size / 2, Tuple>;
			using lhs_res = binary_fold1_t<binary_transform_class, lhs>;
			using rhs_res = binary_fold1_t<binary_transform_class, rhs>;
		public:
			using type = typename binary_transform_class<lhs_res, rhs_res>::type;
		};
		template<class Tuple, template<class L, class R>class binary_transform_class>
		struct binary_fold1<Tuple, binary_transform_class, typename std::enable_if<size<Tuple>::value == 1>::type>
		{
			using type = at_t<0, Tuple>;
		};

		template<class Tuple, template<class L, class R>class binary_transform_class>
		struct binary_fold1<Tuple, binary_transform_class, typename std::enable_if<size<Tuple>::value == 0>::type>
		{};


		//ê[Ç≥O(log N)
		//(+(+1 (+2 3))(+(+4 5)(+6 7)))
		template<template<class L, class R>class binary_transform_class, class Tuple>
		using binary_fold1_t = typename binary_fold1<Tuple, binary_transform_class>::type;

	}
}