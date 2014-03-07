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
		namespace impl{
			template<template<class T>class Pred, class Tuple>
			class filter_impl
			{
			private:
				using seq = index::make_N_index<size<Tuple>::value>;
				template<class Idx>
				class Trans
				{
					using T = at<Idx::value, Tuple>;
					static const bool r = Pred<T>::value;
				public:
					using type = utility::cond<r, std::tuple<Idx>, std::tuple<> >;
				};
				template<class L, class R>
				struct bi_cat
				{
					using type = cat<L, R>;
				};
			public:
				using sequence_type = binary_fold<bi_cat, seq, Trans>;
				using type = index::type_list::to_tuple<sequence_type, Tuple>;
			};
		}
		template<template<class T>class Pred, class Tuple>
		using filter = typename impl::filter_impl<Pred, Tuple>::type;
	}
	template<template<class T>class Pred,class Tuple>
	inline auto filter(const Tuple&tuple)
		->type_list::filter<Pred, Tuple>
	{
		using seq = typename type_list::impl::filter_impl<Pred, Tuple>::sequence_type;
		return index::to_tuple(seq(),tuple);
	}
}