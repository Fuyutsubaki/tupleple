#include<string>
#include<iostream>
#include<memory>
#include"drop.hpp"

int main()
{
	using namespace tupleple;
	auto tuple = std::make_tuple(1, std::make_unique<int>(2), 3);
	auto x = tuple | view::drop<1>();
	auto i = at<0>(std::move(x));
}