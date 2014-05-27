#pragma once

#include"take.hpp"
#include"drop.hpp"
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		struct unique
		{
			template<size_t N>
			struct impl
			{

				drop_t<N, Tuple>;

				at_t<N,Tuple>;
			};
		};
	}













}