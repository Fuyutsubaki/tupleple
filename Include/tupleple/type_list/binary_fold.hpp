#pragma once
#include"drop.hpp"
#include"take.hpp"
#include"ListStyle.hpp"
#include<tupleple\tuple.hpp>

/*
struct plus
{
	template<class L,class R>
	auto operator()(L l,R r)const
	->decltype(l+r)
	{
	return l+r;
	}
};

int main()
{
	using namespace tupleple;
	auto t = std::make_tuple(1, 1.4f, 31.4, 18L);
	auto x = algorithm::binary_fold(t, plus());
}
*/

namespace tupleple
{
	namespace type_list
	{
		template<class List, template<class...>class Binary_func, class = void>
		class binary_fold
		{
			static const size_t N = size<List>::value;
			using L = typename binary_fold<take_t<N / 2, List>, Binary_func>::type;
			using R = typename binary_fold<drop_t<N / 2, List>, Binary_func>::type;
		public:
			using type = typename Binary_func<L, R>::type;
		};
		template<class List, template<class...>class Binary_func>
		struct binary_fold<List, Binary_func,typename std::enable_if<size<List>::value==1>::type>
		{
			using type = front_t<List>;
		};
		template<class List, template<class...>class Binary_func>
		using binary_fold_t = typename binary_fold<List, Binary_func>::type;



		template<class List, template<class...>class Binary_struct, class = void>
		class binary_fold_struct
		{
			static const size_t N = size<List>::value;
			using L = typename binary_fold_struct<take_t<N / 2, List>, Binary_struct>::type;
			using R = typename binary_fold_struct<drop_t<N / 2, List>, Binary_struct>::type;
		public:
			using type = Binary_struct<L, R>;
		};
		template<class List, template<class...>class Binary_func>
		struct binary_fold_struct<List, Binary_func, typename std::enable_if<size<List>::value == 1>::type>
		{
			using type = front_t<List>;
		};
		template<class List, template<class...>class Binary_func>
		using binary_fold_struct_t = typename binary_fold_struct<List, Binary_func>::type;
	}
}