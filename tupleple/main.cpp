#include<iostream>
#include<utility>
#include"take.hpp"
#include<memory>
#include"move_view.hpp"
#include"STD_tuple_traits.hpp"
#include"column.hpp"
#include"zip.hpp"
#include"parameter_pack_at.hpp"
#include"lnTuple.h"



template<class ...T,class...R>
void f(const std::tuple<T...>&c,T...s,R...t)
{

}
int main()
{
	using namespace tupleple;
	
	ln_tuple::tuple<char, int, double, float,long long> c('A', 4, 3.140, 0, 0);

}