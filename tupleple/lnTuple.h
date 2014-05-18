#pragma once
#include"parameter_pack_library.hpp"
#include<tuple>




namespace ln_tuple
{
	template<class Functor>
	struct make_tuple
	{
		Functor func;
		template<class...T>
		void operator()(T&&...args)
		{
			std::make_pair(
				papali::make_take<(sizeof...(T)) / 2>(*this)(std::forward<T>(args)...)
				, papali::make_drop<(sizeof...(T)) / 2>(*this)(std::forward<T>(args)...)
				);
		}
		template<class T>
		void operator()(T&&x)
		{
			
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