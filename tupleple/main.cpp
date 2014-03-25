#include<string>
#include<iostream>
#include"Index.hpp"
#include"cat.hpp"
#include"cons.hpp"
#include"drop.hpp"
#include"filter.hpp"
#include"foldl.hpp"
#include"push.hpp"
#include"replicate.hpp"
#include"reverse.hpp"
#include"take.hpp"
#include"zip.hpp"
#include<vector>
#include<memory>
#include<list>
#include<array>
#include"apply.hpp"





struct Func
{
	template<class...R>
	void operator()(R...x)
	{
		 { x... };
	}
};
template<class F>
struct Test
{
	using X = typename tupleple::utility::template carry_variadic_result_of<F>::type<char, int>;
};
int main()
{
	using tuple = std::tuple<char, int>;
	using X = tupleple::type_list::apply_t<tuple, tupleple::utility::template carry_variadic_result_of<Func>::type>;
	std::cout << typeid(X).name();






}
