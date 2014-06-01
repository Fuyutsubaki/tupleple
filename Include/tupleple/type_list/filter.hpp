#pragma once

#include"map.hpp"
#include"cat.hpp"
#include"List.hpp"

/*
	using namespace tupleple;
	auto r = std::make_tuple(false, "ABC", 3.14, 42);
	auto c= r | view::filter_if<std::is_integral>();
	std::cout << (c | at<1>());
*/
/*
	using namespace tupleple;
	auto r = std::make_tuple(false, "ABC", 3.14, 42, 41);
	auto c = r | view::filter<int>();
	std::cout << (c | at<1>());
*/
namespace tupleple
{
	namespace type_list
	{
		template<class tList,template<class>class Pred>
		struct filter_if
		{
			template<class T>
			struct Trans
			{
				using type = utility::cond_t<Pred<T>::value, List<T>, List<> >;
			};
			using type= flat_t<map_t<tList,Trans>>;
		};

		template<class tList, class T>
		struct filter
		{
			template<class U>
			struct trans
				:std::is_same<U,T>
			{};
			using type = filter_if<tList, trans>;
		};


		template<class tList, template<class>class Pred>
		using filter_if_t = typename filter_if<tList, Pred>::type;
		template<class tList, class T>
		using filter_t = typename filter<tList, T>::type;
	}
	
}