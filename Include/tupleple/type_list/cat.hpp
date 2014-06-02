#pragma once
#include<type_traits>
#include<tupleple\view\cat.hpp>
#include"binary_fold.hpp"
#include"List.hpp"

namespace tupleple
{
	namespace type_list
	{

		template<class Lists>
		struct flat;
		template<class...Lists>
		struct cat;

		template<class...L, class...R>
		struct cat<List<L...>, List<R...>>
		{
			using type = List<L..., R...>;
		};
		

		template<class Lists>
		struct flat
			: binary_fold<Lists, cat>
		{};

		
		template<class...Lists>
		struct cat
			:flat<List<Lists...>>
		{};
		template<class ...T>
		using cat_t = typename cat<T...>::type;
		template<class Lists>
		using flat_t = typename flat<Lists>::type;
	}
}