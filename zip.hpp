#pragma once
#include<tuple>
#include"sequence.hpp"


namespace tupleple
{
	namespace type_list
	{
		template<class Tuple1,class Tuple2>
		class zip;
		template<class ...L,class ...R>
		struct zip<std::tuple<L...>, std::tuple<R...>>
		{
			using type = std::tuple<std::tuple<L, R>...>;
		};
	}
	namespace deteil
	{
		template<class ...L, class ...R,size_t ...N>
		auto zip_impl(const std::tuple<L...>&l, const std::tuple<R...>&r,sequence::Sequence<N...>)
			->typename type_list::zip<std::tuple<L...>, std::tuple<R...>>::type
		{
			return 
				typename type_list::zip<std::tuple<L...>, std::tuple<R...>>::type
				( std::tuple<L, R>(std::get<N>(l), std::get<N>(r))... );
		}
	}
	template<class ...L, class ...R>
	auto zip(const std::tuple<L...>&l, const std::tuple<R...>&r)
		->typename type_list::zip<std::tuple<L...>, std::tuple<R...>>::type
	{
		return deteil::zip_impl(l,r
			, typename sequence::make_N_Sequence<std::tuple_size<std::tuple<L...>>::value>::type()
			);
	}
}