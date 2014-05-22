#pragma once
#include"parameter_pack_library.hpp"
#include<tuple>




namespace ln_tuple
{

	template<class Functor>
	struct binary_fold;

	template<class Func,class ...T>
	struct fold_impl
	{
		static const size_t N = sizeof...(T);
		static void fold(Func&&func,T&&...args)
		{
			func(
				ppl::make_take<N / 2>()(std::forward<T>(args)...)
				, ppl::make_drop<N / 2>()(std::forward<T>(args)...)
				);
		}
	};
	template<class Func, class T>
	struct fold_impl<Func,T>
	{
		static T&& fold(Func&&,T&&x)
		{
			return std::forward<T>(x);
		}
	};

	template<class Functor>
	struct binary_fold
	{
		Functor func;
		template<class T>
		binary_fold(T&&x)
			:func(std::forward<T>(x))
		{}
	};

	
	template<class T,class...R>
	void make_tuple(T&&x, R&&...args)
	{
		papali::make_take();

	}

	template<class T>
	void make_tuple(T&&x)
	{

	}






}