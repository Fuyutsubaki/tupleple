#include<string>
#include<iostream>
#include<memory>
#include"drop.hpp"
#include"take.hpp"



struct test_view
{

};
int main()
{
	using namespace tupleple;
	auto tuple = std::make_tuple(1, std::make_unique<int>(2), 3);
	auto i = at<0>(std::move(tuple) | view::drop<1>());


	using t=type_list::at_t<0,type_list::drop_t<1, std::tuple<char, std::string, long long>>>;
}