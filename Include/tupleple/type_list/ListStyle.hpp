#pragma once


#include"drop.hpp"
#include"at.hpp"
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		struct front
			:at<0, Tuple>
		{};
		template<class Tuple>
		using front_t = typename front<Tuple>::type;

		template<class Tuple>
		struct tail
			:drop<1,Tuple>
		{};
		template<class Tuple>
		using tail_t = typename tail<Tuple>::type;
	}
}