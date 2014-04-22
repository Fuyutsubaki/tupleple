#include<iostream>
#include<tuple>
#include"do_nothing.hpp"
#include<memory>

int main()
{
	using namespace tupleple;
	auto c = std::make_tuple(std::make_unique<int>(1)) | view::do_nothing() | at<0>();
}