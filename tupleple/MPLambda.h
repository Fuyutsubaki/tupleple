#pragma once
#include<functional>



namespace mpll
{


	template<class T>
	struct type_value
	{
		using type = T;
	};
	template<class T>
	type_value<T> val(){ return{}; }

	namespace deteil
	{
		template<class T>
		struct UnTv
		{
			using type = T;
		};
		template<class T>
		struct UnTv<type_value<T>>
		{
			using type = T;
		};

		template<class T>
		using UnTv_t = typename UnTv<T>::type;
	}
	template<template<class>class mono_MetaFunc>
	struct mono_base
	{
		template<class T>
		auto operator()(T)
		->type_value<typename mono_MetaFunc<deteil::UnTv_t<T>>::type>
		{return{};}
	};
}