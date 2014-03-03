#pragma once
#include<tuple>

namespace tupleple
{
	namespace type_list
	{
		namespace flex
		{
			template<class ...Tuple>
			struct cat
			{
				using type = typename decltype(std::tuple_cat(std::declval<Tuple>()...));
			};
		}
		template<class L,class R>
		using cat = typename flex::cat<L,R>::type;
	}
	template<class ...Tuple>
	typename type_list::flex::cat<Tuple...>::type cat(const Tuple&...tuple)
	{
		return std::tuple_cat(tuple...);
	}
}