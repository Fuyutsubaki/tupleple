#include"take.hpp"
#include<iostream>
#include<memory>
#include"binary_fold.hpp"
#include"all.hpp"
#include"any.hpp"
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
	auto x = algorithm::any(t, is_plus());
}