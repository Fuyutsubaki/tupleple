#pragma once
#include<tuple>
#include"Index.hpp"
#include"binary_fold.hpp"
#include"utility.hpp"
/*
	using type = std::tuple<float, std::string, void>;
	std::cout << tupleple::type_list::any<type, std::is_integral>::value;
*/

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple,template<class T>class Pred>
		class any
		{
			template<class L,class R>
			struct eval
			{
				using type = typename  utility::if_<L::value, L, R>::type;
			};
			template<class T>
			struct wrap
			{
				using type = Pred<T>;
			};
		public:
			static const bool value = typename binary_fold<eval, Tuple, wrap>::type::value;
		};
	}
}



