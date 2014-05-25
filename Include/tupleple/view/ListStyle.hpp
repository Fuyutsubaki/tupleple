#pragma once
#include"take.hpp"
#include"drop.hpp"

namespace tupleple
{
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