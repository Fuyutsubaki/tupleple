#pragma once

#include<tuple>
#include"sequence.hpp"
#include"utility.hpp"
/*
	auto result=tupleple::filter<std::is_integral>(std::make_tuple(42, 3.14, 'A', 1.4f));
	tupleple::debug::element_output<0>(result);	//42	:int
	tupleple::debug::element_output<1>(result);	//A		:char
*/
namespace tupleple
{
	namespace type_list
	{
		template<template<class T>class Pred,class T>
		class filter;

		template<class ...R, template<class T>class Pred>
		struct filter< Pred, std::tuple<R...>>
		{
		private:
			using r_seq_ = sequence::Sequence<Pred<R>::value...>;
		public:
			using sequence_type = typename sequence::bit_filter<r_seq_>::type;
			using type = typename sequence::type_list::to_tuple<sequence_type, std::tuple<R...>>::type;
		};
	}
	template<template<class T>class Pred,class ...R>
	auto filter(const std::tuple<R...>&tuple)
		->typename type_list::filter<Pred, std::tuple<R...>>::type 
	{
		using seq = typename type_list::filter<Pred, std::tuple<R...>>::sequence_type;
		return sequence::to_tuple(seq(),tuple);
	}
}