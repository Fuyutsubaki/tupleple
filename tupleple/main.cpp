#include"take.hpp"
#include<iostream>
#include<memory>
#include"binary_fold.hpp"
#include"all.hpp"

struct is_plus
{
	template<class T>
	bool operator()(T x)
	{
		return x > 0;
	}
}; 

struct plus
{
	template<class L, class R>
	auto operator()(L l, R r)const
		->decltype(l + r)
	{
		return l + r;
	}
};

int main()
{
	using namespace tupleple;
	auto t = std::make_tuple(1, 1.4f, 31.4, 18L, 1, 1.4f, 31.4, 18L, 1, 1.4f, 31.4, 18L, 1, 1.4f, 31.4, 18L,1, 1.4f, 31.4, 18L);
	auto x = algorithm::binary_fold(t, plus());
}