#pragma once

#include<tupleple\type_list\List.hpp>
#include<tupleple\utility\to_typelist.hpp>
#include<tupleple\type_list\cat.hpp>
#include<tupleple\type_list\binary_fold.hpp>
#include"replicate.hpp"
#include"at.hpp"
namespace tupleple
{

	namespace type_list
	{
		template<template<class...>class Struct, class L,class R>
		struct zip_struct
			:zip_struct<Struct, utility::to_typelist_t<L>, utility::to_typelist_t<R>>
		{};


		template<template<class...>class Struct, class...L, class...R>
		struct zip_struct<Struct, List<L...>, List<R...>>
		{
			using type = List<Struct<L, R>...>;
		};

		template<class...>
		struct zip
		{};
		
		template<class tList>
		struct transpose
		{
			template<class U>
			using wrap = utility::identity<List<U>>;
			
			template<class T>
			using impl = map<T, wrap>;

			template<class L, class R>
			struct implzip
				:implzip<utility::to_typelist_t<L>, utility::to_typelist_t<R>>
			{};
			template<class...L, class...R>
			struct implzip<List<L...>, List<R...>>
			{
				using type = List<typename cat<L, R>::type...>;
			};
			using t = map_t<tList, impl>;
			static const size_t N = size<at_t<0, tList>>::value;
			
			using so = replicate_t<N, List<>>;
			using type = binary_fold_t<t, implzip, so>;
		};

		template<class...L,class...R>
		struct zip<List<L...>,List<R...>>
		{
			using type = List<List<L, R>...>;
		};


		

	}
}