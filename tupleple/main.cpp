#include<iostream>
#include<tuple>
#include"do_nothing.hpp"
#include<memory>
#include"STD_tuple_traits.hpp"
#include"forward_as_view.hpp"

template<class C>
tupleple::view::do_nothing_forward test()
{
	return{};
}
template<class>
struct rhs
{
	friend int operator*(int x, rhs){ return 2; }
};





int main()
{
	using namespace tupleple;
	auto c = std::make_tuple(1, std::make_unique<int>(42));
	auto x = move_as_view(c) | test<int>() ;
}
