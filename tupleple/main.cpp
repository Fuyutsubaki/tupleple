#include<iostream>
#include<utility>
#include"take.hpp"
#include<memory>
#include"move_view.hpp"
#include"STD_tuple_traits.hpp"
int main()
{
	using namespace tupleple;
	move_view(std::make_tuple(1, 2, 3)) | view::take<1>() | at<0>();
}