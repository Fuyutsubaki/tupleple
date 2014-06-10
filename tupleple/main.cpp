
#include<iostream>
#include<memory>
#include<tuple>



struct dummy{};
template<class L, class R>
struct overload_function
{	
	overload_function(const L&l, const R&r)
	:l(l), r(r)
	{}
	L l;
	R r;
	template<class T,class...Args>
	auto operator()(T, Args&&...args)
		->typename std::result_of<R(Args...)>::type
	{
		return r(std::forward<Args>(args)...);
	}
	template<class...Args>
	auto operator()(dummy, Args&&...args)
		->typename std::result_of<L(Args...)>::type
	{
		return l(std::forward<Args>(args)...);
	}
};
template<class L,class R>
overload_function<L, R> make_overload(L&&l, R&&r)
{
	return{ std::forward<L>(l), std::forward<R>(r) };
}



#include<tupleple\type_list\quick_sort.hpp>
#include<tupleple\view\type_separate.hpp>
#include<tupleple\type_list\all.hpp>
#include<tupleple\type_list\zip.hpp>
#include<tupleple\type_list\binary_fold.hpp>
#include<tupleple\view\type_separate.hpp>
#include<tupleple\STD_tuple_traits.hpp>
template<class L,class R>
struct is_small_size
	:std::integral_constant < bool, (sizeof(L)<sizeof(R))>
{
};

template<class L,class R>
struct max
	:std::conditional < (sizeof(L)<sizeof(R)), R, L>
{};



//
//
int main()
{
	using namespace tupleple;
	
	
	
	

}