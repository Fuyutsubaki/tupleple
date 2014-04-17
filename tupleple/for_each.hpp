#pragma once
#include"tuple.hpp"
#include"map.hpp"
/*

struct disp
{
	template<class T>
	void operator()(const T&x)const
	{
		std::cout << x;
	}
};
int main()
{
	tupleple::for_each(std::make_tuple(1, 3.14, "abc"), disp());
	//abc3.141
	//‡”Ô‚É“®ì‚·‚é•ÛØ‚ÍŒ»Ý‚È‚¢
}
*/
namespace tupleple
{
	namespace deteil
	{
		template<class Func>
		struct for_each_impl_adapter
		{
			for_each_impl_adapter(const Func&func)
				:func_(func)
			{	}
			struct nil{};
			template<class T>
			nil operator()(const T&x)const
			{
				func_(x);
				return nil();
			}
		private:
			const Func&func_;
		};
	}
	template<class Tuple,class Func>
	void for_each(const Tuple&tuple,const Func&func)
	{
		map(deteil::for_each_impl_adapter<Func>(func), tuple);
	}

	namespace
	{

	}
}

