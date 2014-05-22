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
	
	namespace type_list
	{
		template<class Tuple,template<class>class Pred>
		struct any
		{
			template<class T>
			struct wrap
			{
				using type = Pred<T>;
			};
			template<class L,class R>
			struct eval
			{
				using type = utility::cond_t<L::value, L, R>;
			};
			static const bool value= binary_fold_t<map_t<Tuple, wrap>, eval>::value;
		};
	}
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



