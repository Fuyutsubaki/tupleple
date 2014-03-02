#pragma once
#include<tuple>

namespace tupleple
{
	namespace type_list
	{
		template<class ...Tuple>
		struct cat
		{
			using type = typename decltype(std::tuple_cat(std::declval<Tuple>()...));
		};
	}
	template<class ...Tuple>
	type_list::cat<Tuple...> cat(const Tuple&...tuple)
	{
		return std::tuple_cat(tuple...);
	}
}