#pragma once
#include"drop.hpp"
#include"take.hpp"
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
#include<functional>

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class, class>class Binary_func, class = void>
		class binary_fold
		{
			static const size_t N = size<Tuple>::value;
			using L = typename binary_fold<take_t<N / 2, Tuple>, Binary_func>::type;
			using R = typename binary_fold<drop_t<N / 2, Tuple>, Binary_func>::type;
		public:
			using type = typename Binary_func<L, R>::type;
		};
		template<class Tuple, template<class, class>class Binary_func>
		struct binary_fold<Tuple, Binary_func, std::enable_if_t<size<Tuple>::value == 1>>
		{
			using type = at_t<0, Tuple>;
		};
		template<class Tuple, template<class, class>class Binary_func>
		using binary_fold_t = typename binary_fold<Tuple, Binary_func>::type;
	}
}