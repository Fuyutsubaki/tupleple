#pragma once

#include<tupleple\type_list\List.hpp>

namespace tupleple
{

	namespace type_list
	{
		template<class...>
		struct zip
		{};

		template<class...L,class...R>
		struct zip<List<L...>,List<R...>>
		{
			using type = List<List<L, R>...>;
		};
		template<template<class...>class,class...>
		struct zip_struct
		{};


		template<template<class...>class Struct,class...L, class...R>
		struct zip_struct<Struct, List<L...>, List<R...>>
		{
			using type = List<Struct<L, R>...>;
		};



	}






}