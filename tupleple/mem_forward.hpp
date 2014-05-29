#pragma once

#include<type_traits>
#include<utility>


//mem is ref -> T
//other -> U

template<class T, class U>
auto mem_forward(U&&x)
->typename std::conditional<std::is_reference<T>::value, T, U&&>::type
{
	return std::forward<typename std::conditional<std::is_reference<T>::value, T, U&&>::type>(x);
}
//struct C
//{
//	C(int&x)
//	:v(x), c(x), l(x), r(std::move(r))
//	{}
//	int v;
//	const int c;
//	int&l;
//	int&&r;
//};
//
//int main()
//{
//	int x = 0;
//	C c(x);
//	const C cc(x);
//	static_assert(std::is_same<decltype(mem_forward<decltype(c.v)>(c.v)), int&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(c.c)>(c.c)), const int&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(c.l)>(c.l)), int&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(c.r)>(c.r)), int&&>::value, "");
//
//	static_assert(std::is_same<decltype(mem_forward<decltype(cc.v)>(cc.v)), const int&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(cc.c)>(cc.c)), const int&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(cc.l)>(cc.l)), int&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(cc.r)>(cc.r)), int&&>::value, "");
//
//	static_assert(std::is_same<decltype(mem_forward<decltype(C(x).v)>(C(x).v)), int&&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(C(x).c)>(C(x).c)), const int&&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(C(x).l)>(C(x).l)), int&>::value, "");
//	static_assert(std::is_same<decltype(mem_forward<decltype(C(x).r)>(C(x).r)), int&&>::value, "");
//}
