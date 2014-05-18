#pragma once
#include"tuple.hpp"
#include"take.hpp"
#include"drop.hpp"
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		struct front
			:at<0, Tuple>
		{};
		template<class Tuple>
		using front_t = front<Tuple>;

		template<class Tuple>
		struct tail
			:drop<1,Tuple>
		{};
		template<class Tuple>
		using tail_t = tail<Tuple>;
	}
	namespace view
	{
		
		auto front()
			->at_functor<0>
		{
			return{};
		}
	
		auto tail()
			->drop_functor<1>
		{
			return{};
		}
	}



}