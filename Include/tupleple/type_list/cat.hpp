#pragma once
#include<tupleple\tuple.hpp>
#include<type_traits>
#include<tupleple\view\cat.hpp>
#include"binary_fold.hpp"
#include"List.hpp"

/*
using namespace tupleple;
auto a = std::make_tuple(1, 2);
auto b = std::make_tuple(std::make_unique<int>(42), 'B');
auto c = std::make_tuple(std::string(":-)"), std::string(":-|"));

auto s = view::cat(a, move_view(b), c);
auto p = s | at<2>();

*/
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
		/*template<class Tuple>
		struct flat
		{
			template<class L, class R>
			struct cat_
			{
				using type = view::cat_view<L, R>;
			};
			using type = binary_fold_t<Tuple, cat_>;
		};

		template<class ...R>
		struct cat
		{
			using type = typename flat<std::tuple<R...>>::type;
		};
		template<class...L, class...R>
		struct cat<std::tuple<L...>, std::tuple<R...>>
		{
			using type = std::tuple<L..., R...>;
		};
		template<class Tuple>
		using flat_t = typename flat<Tuple>::type;
		template<class ...R>
		using cat_t = typename cat<R...>::type;*/



	}
}