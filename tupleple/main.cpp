#include<iostream>
#include<utility>
#include"take.hpp"
#include<memory>
#include"move_view.hpp"
#include"STD_tuple_traits.hpp"
#include"column.hpp"
#include"zip.hpp"
int main()
{
	using namespace tupleple;
	char c = 'X';
	int x = 42;
	float f = 3.14;
	auto t1 = std::make_tuple(c, x, f);
	auto t2 = std::tie(c, x, f);
	auto t3 = std::make_tuple(&c, &x, &f);

	auto result = tupleple::view::zip(t1, t2, t3);

	std::cout << (result | at<2>() | at<0>());
}