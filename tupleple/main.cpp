#include<iostream>
#include<tuple>
#include"do_nothing.hpp"
#include"STD_tuple_traits.hpp"
#include"apply.hpp"
#include<vector>

#include<algorithm>
#include"binary_fold.hpp"
#include"move_view.hpp"
#include"cat.hpp"
#include<memory>

int main()
{
	using namespace tupleple;
	auto a = std::make_tuple(1, 2);
	auto b = std::make_tuple(std::make_unique<int>(42), 'B');
	auto c = std::make_tuple(std::string(":-)"), std::string(":-|"));

	auto s = view::cat(a, move_view(b), c);
	auto p = s | at<2>();
}

