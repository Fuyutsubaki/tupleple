#pragma once 
#include<tuple>
#include"tuple.hpp"
#include"cons.hpp"

/*
template<class L, class R>
struct Maxsize
{
	using type = tupleple::utility::cond < (sizeof(L)>sizeof(R)), L, R>;
};

int main()
{
	using tuple = std::tuple<char, int,long long>;
	using type = tupleple::type_list::foldl1<Maxsize, tuple>;
	std::cout << typeid(type).name();
}
*/

namespace tupleple
{
	//(+ (+ (+ (+ 0 1) 2) 3) 4)
	namespace algorithm
	{
		namespace deteil
		{
			template<class Tuple,class Func>
			struct foldl1_impl
			{
				using rest = typename std::result_of<>::type;
				using result_type = void;
				static result_type fold()
				{

				}
			};
		}
	}


}