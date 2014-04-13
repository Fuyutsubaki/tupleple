#include<string>
#include<iostream>
#include<memory>
#include"cat.hpp"
#include"reverse.hpp"
#include"binary_fold.hpp"
struct plus
{
	template<class L,class R>
	auto operator()(L lhs, R rhs)
		->decltype(lhs + rhs)
	{
		return lhs + rhs;
	}
};

template<size_t N>
auto test(int)
	->std::enable_if_t<(N>0),decltype(test<N-1>())>
{
	return test<N - 1>(0);
}
template<size_t N>
auto test(bool)
	->std::enable_if_t<(N==0), std::integral_constant<size_t,N>>
{
	return std::integral_constant<size_t, N>(0);
}

int main()
{
	//auto tuple = std::make_tuple(1, 2.5f, 200L);// , 3.14, 42);


	//auto result = tupleple::algorithm::binary_fold(tuple,plus());
	test<2>(0);
}