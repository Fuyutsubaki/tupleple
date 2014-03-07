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
		namespace flex
		{
			template<class Tuple0, class ...Tuple>
			class zip
			{
				using seq = index::make_N_index<size<Tuple0>::value>;
				template<class Idx>
				struct one_tuple
				{
					using type = std::tuple<at<Idx::value, Tuple0>, at<Idx::value, Tuple>...>;
				};
			public:
				using type = map<one_tuple, seq>;
			};
		}
		template<class L,class R>
		using zip = typename flex::zip<L, R>::type;
	}
	namespace deteil
	{
		template<size_t N, class ...Tuple>
		auto zip_impl2(const Tuple&...t)
			->type_list::at<N, typename type_list::flex::zip<Tuple...>::type>
		{
			using Tuple_=type_list::at<N, typename type_list::flex::zip<Tuple...>::type>;
			return Tuple_(at<N>(t)...);
		}
		template< class ...Tuple,class ...Idx>
		auto zip_impl(std::tuple<Idx...>,const Tuple&...t)
			->typename type_list::flex::zip<Tuple...>::type
		{
			using res_type=typename type_list::flex::zip<Tuple...>::type;
			return res_type(zip_impl2<Idx::value>(t...)...);
		}
	}
	template<class Tuple0,class ...Tuple>
	auto zip(const Tuple0&t0, const Tuple&...t)
		->typename type_list::flex::zip<Tuple0,Tuple...>::type
	{
		using seq = index::make_N_index<type_list::size<Tuple0>::value>;
		return deteil::zip_impl(seq(), t0, t...);
	}
}