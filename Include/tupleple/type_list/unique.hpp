#pragma once

#include"take.hpp"
#include"drop.hpp"
#include"ListStyle.hpp"
#include"in.hpp"
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
				using list = drop_t<N, Tuple>;
				using head = front_t<list>;
				using tail = tail_t<list>;
				in<head, tail>::value;
			};
		};
	}













}