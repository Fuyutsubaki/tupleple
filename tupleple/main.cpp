#include<iostream>
#include<utility>
#include"take.hpp"
#include<memory>
#include"move_view.hpp"
#include"STD_tuple_traits.hpp"
#include"column.hpp"
int main()
{
	using namespace tupleple;
	auto c = std::make_tuple(std::make_tuple("X", 1), std::make_tuple("Y", 2), std::make_tuple("Z", 3));

	auto val = c | view::column<1>();
	std::cout << (val | at<0>()) << std::endl;
	std::cout << (val | at<1>()) << std::endl;
	std::cout << (val | at<2>()) << std::endl;
}