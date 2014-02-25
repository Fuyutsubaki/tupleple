#pragma once

#include<tuple>
#include"sequence.hpp"
#include"tuple.hpp"
#include"map.hpp"

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

		template<class Tuple, template<class T>class Pred>
		struct filter< Pred, Tuple>
		{
		private:
			using seq = typename map_to_sequence<Tuple, Pred>::type;
		public:
			using sequence_type = typename sequence::bit_filter<seq>::type;
			using type = typename sequence::type_list::to_tuple<sequence_type, Tuple>::type;
		};
	}
	template<template<class T>class Pred,class Tuple>
	auto filter(const Tuple&tuple)
		->typename type_list::filter<Pred, Tuple>::type
	{
		using seq = typename type_list::filter<Pred, Tuple>::sequence_type;
		return sequence::to_tuple(seq(),tuple);
	}
}