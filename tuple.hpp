#pragma once 
#include<tuple>

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple>
		struct size
		{
			//static_assert(false,"this is no tuple");
			//static const size_t value = 0;
		};

		template<class ...R>
		struct size<std::tuple<R...>>
		{
			static const size_t value = std::tuple_size<std::tuple<R...>>::value;
		};

		template<size_t N,class Tuple>
		struct at;

		template<size_t N, class ...R>
		struct at<N,std::tuple<R...>>
		{
			using type = typename std::tuple_element<N, std::tuple<R...>>::type;
		};
	}	
	template<size_t N, class ...R>
	auto at(const std::tuple<R...>&tuple)
		->typename type_list::at<N, std::tuple<R...>>::type const &
	{
			return std::get<N>(tuple);
	}

	template<class T>
	struct is_tuple
	{
		static const bool value = false;
	};
	template<class ...T>
	struct is_tuple<std::tuple<T...>>
	{
		static const bool value = true;
	};
}
//atを特殊化することでタプル以外のものもタプル化できる
/*
auto x = std::make_tuple(1, 2, 42);
tupleple::at<2>(x);	//42
*/