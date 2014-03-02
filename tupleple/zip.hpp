#pragma once
#include<tuple>
#include"Index.hpp"
#include"map.hpp"
/*
char c = 'X';
int x = 42;
float f = 3.14;
auto t1 = std::make_tuple(c, x, f);
auto t2 = std::tie(c, x, f);
auto t3 = std::make_tuple(&c, &x, &f);

auto result = tupleple::zip(t1,t2,t3);

*/
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple0,class ...Tuple>
		class zip
		{
			using seq = typename index::make_N_index<size<Tuple0>::value>::type;
			template<class Idx>
			struct one_tuple
			{
				using type = std::tuple<typename at<Idx::value, Tuple0>::type, typename at<Idx::value, Tuple>::type...>;
			};
		public:
			using type = typename map<one_tuple, seq>::type;
		};
	}
	namespace deteil
	{
		template<size_t N, class ...Tuple>
		auto zip_impl2(const Tuple&...t)
			->typename type_list::at<N, typename type_list::zip<Tuple...>::type>::type
		{
			using Tuple_=typename type_list::at<N, typename type_list::zip<Tuple...>::type>::type;
			return Tuple_(at<N>(t)...);
		}
		template< class ...Tuple,class ...Idx>
		auto zip_impl(std::tuple<Idx...>,const Tuple&...t)
			->typename type_list::zip<Tuple...>::type
		{
			using res_type=typename type_list::zip<Tuple...>::type;
			return res_type(zip_impl2<Idx::value>(t...)...);
		}
	}
	template<class Tuple0,class ...Tuple>
	auto zip(const Tuple0&t0, const Tuple&...t)
		->typename type_list::zip<Tuple0,Tuple...>::type
	{
		using seq = typename index::make_N_index<type_list::size<Tuple0>::value>::type;
		return deteil::zip_impl(seq(), t0, t...);
	}
}