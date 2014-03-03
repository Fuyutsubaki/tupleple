#pragma once
#include<tuple>
#include"Index.hpp"
#include"binary_fold.hpp"
#include"utility.hpp"
/*
	using type = std::tuple<float, std::string, void>;
	std::cout << tupleple::type_list::all<std::is_integral,type>::value;	
*/

namespace tupleple
{
	namespace type_list
	{
		template<template<class T>class Pred, class Tuple>
		class all
		{
			template<class L, class R>
			struct eval
			{
				using type = utility::cond<!L::value, L, R>;
			};
			template<class T>
			struct wrap
			{
				using type = Pred<T>;
			};
		public:
			static const bool value = binary_fold<eval, Tuple, wrap>::value;
		};
	}
}



