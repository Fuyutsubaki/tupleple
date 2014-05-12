#include<iostream>
#include<string>
#include"map.hpp"
//#include"filter.hpp"
#include"cat.hpp"
template<size_t N>
struct Tag{};

template<size_t N, class ...Tail>
struct Data
{
protected:
	void get_(){}
};

template<size_t N,class T,class ...Tail>
class Data<N,T,Tail...>
	:public Data<N + 1, Tail...>
{
public:
	Data(const T&x,const Tail&...tail)
		:Data<N + 1, Tail...>(tail...),item_(x)
	{}
protected:
	using Data<N + 1, Tail...>::get_;
	T&get_(Tag<N>)
	{
		return item_;
	}
private:
	T item_;
};
template<class ...Args>
struct tuple:public Data<0,Args...>
{
	tuple(const Args&...args)
		:Data<0, Args...>(args...)
	{}
	template<size_t N>
	auto get()
		->decltype(get_(Tag<N>()))
	{
		return get_(Tag<N>());
	}
};


int main()
{
	using namespace tupleple;
	/*auto tuple = std::make_tuple(1, std::string("ABC"), 3.14, true);
	auto c = tuple | view::filter<std::is_integral>();
	std::cout << (c | at<0>()) << (c | at<1>());*/
	using R = type_list::cat_t<std::tuple<char, int>, std::tuple< int, long>, std::tuple<long, long long>>;
	using C = type_list::at_t<2, R>;
	std::cout<< typeid(R).name();
}
