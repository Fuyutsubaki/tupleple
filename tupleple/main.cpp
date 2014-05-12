#include<iostream>
#include<string>
#include"map.hpp"
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

	using R = index::map_t<std::tuple<char, float, std::string>, std::is_integral>;

	std::cout << typeid(R).name();

}
