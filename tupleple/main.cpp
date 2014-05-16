#include<iostream>
#include<utility>
#include"take.hpp"
#include<memory>
#include"move_view.hpp"
#include"STD_tuple_traits.hpp"
#include"column.hpp"
#include"zip.hpp"
#include"parameter_pack_at.hpp"



template<class...C,class T=int>
T f(C...c)
{
	return 0;
}

int main()
{
	using namespace tupleple;


	auto r = utility::value_at<6>(1, "", 3.14, false);


}