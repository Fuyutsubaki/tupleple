#pragma once
#include"binary_fold.hpp"
#include"map.hpp"
#include<type_traits>
/*
struct is_plus
{
	template<class T>
	bool operator()(T x)
	{
		return x > 0;
	}
}; 

int main()
{
	using namespace tupleple;
	auto t = std::make_tuple(1, 1.4f, 31.4, -1);
	auto x = algorithm::all(t, is_plus());
}
*/

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class>class Pred>
		struct all
		{
			template<class T>
			struct wrap
			{
				using type = Pred<T>;
			};
			template<class L, class R>
			struct eval
			{
				using type = utility::cond_t<!L::value, L, R>;
			};
			static const bool value = binary_fold_t<map_t<Tuple, wrap>, eval>::value;
		};
	}
	namespace algorithm
	{
		template<class Tuple,class Pred>
		bool all(Tuple&&tuple,Pred&&pred)
		{
			return binary_fold(
				std::forward<Tuple>(tuple) | view::map(std::forward<Pred>(pred))
				, [](bool l, bool r){return l&&r; });
		}
	}
}



