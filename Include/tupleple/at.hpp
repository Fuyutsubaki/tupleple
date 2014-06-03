#pragma once


#include<tupleple\utility\utility.hpp>

namespace tupleple
{
	template<size_t N, class Tuple,class =void>
	class result_of;
	
	template<size_t N, class Tuple>
	using result_of_t = typename result_of<N, Tuple>::type;

	template<size_t N>
	struct at_functor :utility::ExtensionMemberFunction
	{
		template<class Tuple>
		auto operator () (Tuple&&tuple)
			->result_of_t<N, Tuple>
		{
			 return at<N>(std::forward<Tuple>(tuple));
		}
	};
	template<size_t N>
	at_functor<N> at(){ return{}; }
}
