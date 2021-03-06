#pragma once 

struct Print
{

	template<class T, class...Tail>
	bool operator()(T&&a, Tail&&...args)
	{
		std::cout << a << '\t';
		return operator()(args...);
	}
	bool operator()()
	{
		return true;
	}
};