#include<iostream>
#include<string>
#include"map.hpp"
#include"filter.hpp"
#include"cat.hpp"


int main()
{
	using namespace tupleple;
	auto r = std::make_tuple(false, "ABC", 3.14, 42);
	auto c= r | view::filter<std::is_integral>();
	std::cout << (c | at<1>());
}
