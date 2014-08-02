
#include<iostream>
#include<memory>
#include<tuple>

//
//
//struct dummy{};
//template<class L, class R>
//struct overload_function
//{	
//	overload_function(const L&l, const R&r)
//	:l(l), r(r)
//	{}
//	L l;
//	R r;
//	template<class T,class...Args>
//	auto operator()(T, Args&&...args)
//		->typename std::result_of<R(Args...)>::type
//	{
//		return r(std::forward<Args>(args)...);
//	}
//	template<class...Args>
//	auto operator()(dummy, Args&&...args)
//		->typename std::result_of<L(Args...)>::type
//	{
//		return l(std::forward<Args>(args)...);
//	}
//};
//template<class L,class R>
//overload_function<L, R> make_overload(L&&l, R&&r)
//{
//	return{ std::forward<L>(l), std::forward<R>(r) };
//}
//
//
//
//#include<tupleple\type_list\quick_sort.hpp>
//
//#include<tupleple\type_list\all.hpp>
//#include<tupleple\type_list\zip.hpp>
//#include<tupleple\type_list\binary_fold.hpp>
//#include<tupleple\type_list\in.hpp>
//#include<tupleple\STD_tuple_traits.hpp>
//template<class L,class R>
//struct is_small_size
//	:std::integral_constant < bool, (sizeof(L)<sizeof(R))>
//{
//};
//
//
//template<int i>
//struct Which
//{
//	static const size_t value = i;
//};
//
//struct Insert
//{
//	template<class L,class R>
//	void operator()(L&lhs, const R&rhs)
//	{
//		lhs = rhs;
//	}
//};
//template<class T>
//struct Get
//{
//	T operator()(const T&x)const
//	{
//		return x;
//	}
//	template<class U>
//	T operator()(U&x)const
//	{
//		throw "F**K!!";
//		return *(T*)nullptr;
//	}
//};
//#include"variant.hpp"
//#include"debug.h"
//#include<string>
//
//
//template<class T>
//struct S
//{
//	static void fun(){};
//};
//void f()
//{
//	std::cout << "X";
//}
//
//template<void(*l)(), void(*r)()>
//struct Comp
//	//:std::integral_constant < bool, (l < r)>
//{
////	static const std::size_t v = l & 0xFFFF;
//	void f()
//	{
//		l();
//	}
//};
//
//namespace tupleple{
//	namespace type_list{
//template<class L,class R>
//struct comp
//{
//	static const bool value = L::value < R::value;
//};
//template<class T>
//struct end
//{
//	static const bool value = 
//	std::is_same<typename T::left1, List<>>::value && std::is_same<typename T::left2, List<>>::value;
//};
//template<class Res, class list1, class list2>
//struct state
//{
//	using left1 = list1;
//	using left2 = list2;
//	using result = Res;
//};
//
//template<class Res, class L1, class L2>
//struct nextImpl
//{};
//
//template<class ...Res, class H1, class H2, class ...T1, class ...T2>
//struct nextImpl<List<Res...>, List<H1, T1...>, List<H2, T2...>>
//{
//	static const bool r = typename comp<H1, H2>::value;
//	using type = state<
//		List<Res..., typename std::conditional<r, H1, H2>::type>
//		, typename std::conditional<r, List<T1...>, List< H1, T1...>>::type
//		, typename std::conditional<!r, List<T2...>, List<H2, T2...>>::type
//	>;
//};
//
//template<class ...Res, class ...T,  class Comp>
//struct nextImpl<List<Res...>, List<>, List<T...>>
//{
//	using type = state<List<Res..., T...>, List<>, List<>>;
//};
//
//template<class ...Res, class ...T, class Comp>
//struct nextImpl<List<Res...>, List<T...>, List<>>
//{
//	using type = state<List<Res..., T...>, List<>, List<>>;
//};
//
//template<class State>
//struct Next
//	:nextImpl<typename State::result, typename State::left1, typename State::left2>
//{};
//
//
//	}
//}
//template<class T>
//int WD()
//{
//
//}
//
//template<class T, std::size_t N, class Iter1, class Iter2>
//struct state
//{
//	Iter1 it1;
//	Iter2 it2;
//	std::array<T, N> res;
//};





#include"mpl\mpl.hpp"

struct Func
{
	template<class T>
	struct apply
	{
		using type = void;
	};
	using type = Func;
};

int main()
{
	namespace mpl = tupleple::mpl;
	using X = mpl::map<mpl::List<char, int>, Func>::type;
	std::cout << typeid(X).name();
}