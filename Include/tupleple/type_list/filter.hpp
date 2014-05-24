#pragma once

#include<tupleple\view\filter.hpp>


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
		template<class Tuple,template<class>class Pred>
		struct filter_if
		{
			using type = view::filter_view<Tuple, Pred>;
		};
		template<class Tuple, class T>
		struct filter
		{
			template<class U>
			struct Impl
				:std::is_same<U,T>
			{};
			using type = view::filter_view<Tuple, Impl>;
		};
	}
	
}