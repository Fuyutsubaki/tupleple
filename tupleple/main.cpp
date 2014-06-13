
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

#include<tupleple\type_list\all.hpp>
#include<tupleple\type_list\zip.hpp>
#include<tupleple\type_list\binary_fold.hpp>
#include<tupleple\type_list\in.hpp>
#include<tupleple\STD_tuple_traits.hpp>
template<class L,class R>
struct is_small_size
	:std::integral_constant < bool, (sizeof(L)<sizeof(R))>
{
};


#include"variant.hpp"




int main()
{
	using namespace tupleple;
	//tupleple::deteil::variant_apply<void, type_list::List<std::integral_constant<std::size_t,0>>>::apply(std::forward_as_tuple(variant<int, char>{}));

	using v = variant<char, int, int>;
	variant_apply<void>(1, v{1}, 0, v{2});
}