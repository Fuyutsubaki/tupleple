#pragma once

#include<tuple>
#include"Index.hpp"
#include"tuple.hpp"
#include"map.hpp"
#include"utility.hpp"
#include"cat.hpp"
#include"binary_fold.hpp"
/*
	auto result=tupleple::filter<std::is_integral>(std::make_tuple(42, 3.14, 'A', 1.4f));
*/
namespace tupleple
{
	namespace type_list
	{
		template<template<class T>class Pred,class Tuple>
		class filter
		{
		private:
			using seq = typename index::make_N_index<size<Tuple>::value>::type;
			template<class Idx>
			class Trans
			{
				using T = typename at<Idx::value, Tuple>::type;
				static const bool r = Pred<T>::value;
			public:
				using type = typename utility::if_<r, std::tuple<Idx>, std::tuple<> >::type;
			};
			template<class L,class R>
			struct bi_cat
			{
				using type = typename cat<L, R>::type;
			};
		public:
			using sequence_type = typename binary_fold<bi_cat, seq, Trans>::type;
			using type = typename index::type_list::to_tuple<sequence_type, Tuple>::type;
		};
	}
	template<template<class T>class Pred,class Tuple>
	auto filter(const Tuple&tuple)
		->typename type_list::filter<Pred, Tuple>::type
	{
		using seq = typename type_list::filter<Pred, Tuple>::sequence_type;
		return index::to_tuple(seq(),tuple);
	}
}