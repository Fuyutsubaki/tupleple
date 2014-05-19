#pragma once
#include"parameter_pack_library.hpp"
#include<tuple>




namespace ln_tuple
{
	template<class Functor>
	struct binary_fold
	{
		Functor func;
		template<class T>
		binary_fold(T&&x)
			:func(std::forward<T>(x))
		{}
		template<class...T>
		auto operator()(T&&...args)
			->int/*->std::result_of_t<Functor(
			decltype(papali::make_take<(sizeof...(T)) / 2>(std::declval<binary_fold&>())(std::declval<T>()...))
			, decltype(papali::make_drop<(sizeof...(T)) / 2>(std::declval<binary_fold&>())(std::declval<T>()...)))>*/
		{
			return func(
				papali::make_take<(sizeof...(T)) / 2>(*this)(std::forward<T>(args)...)
				, papali::make_drop<(sizeof...(T)) / 2>(*this)(std::forward<T>(args)...)
				);
		}
		template<class T>
		T&& operator()(T&&x)
		{
			return std::forward<T>(x);
		}
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