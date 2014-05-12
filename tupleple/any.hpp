#pragma once
#include"binary_fold.hpp"
#include"map.hpp"
#include<type_traits>
/*
	using type = std::tuple<float, std::string, void>;
	std::cout << tupleple::type_list::any<std::is_integral,type>::value;
*/

namespace tupleple
{
	namespace algorithm
	{
		template<class Tuple, class Pred>
		bool any(Tuple&&tuple, Pred&&pred)
		{
			return binary_fold(
				std::forward<Tuple>(tuple) | view::map(std::forward<Pred>(pred))
				, [](bool l, bool r){return l || r; });
		}
	}
}



