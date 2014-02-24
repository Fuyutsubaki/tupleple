#pragma once
#include<tuple>
#include"sequence.hpp"

/*
char c = 'X';
int x = 42;
float f = 3.14;
auto t1 = std::make_tuple(c, x, f);
auto t2 = std::make_tuple(std::ref(c), std::ref(x), std::ref(f));
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
			using seq = typename sequence::make_N_Sequence<size<Tuple0>::value>::type;
			template<size_t N>
			struct one_tuple
			{
				using type = std::tuple<typename at<N, Tuple0>::type,typename at<N, Tuple>::type...>;
			};
		public:
			using type = typename sequence::type_list::map_to_tuple<seq, one_tuple>::type;
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
		template< class ...Tuple,size_t ...N>
		auto zip_impl(sequence::Sequence<N...>,const Tuple&...t)
			->typename type_list::zip<Tuple...>::type
		{
			using res_type=typename type_list::zip<Tuple...>::type;
			return res_type(zip_impl2<N>(t...)...);
		}
	}
	template<class Tuple0,class ...Tuple>
	auto zip(const Tuple0&t0, const Tuple&...t)
		->typename type_list::zip<Tuple0,Tuple...>::type
	{
		using seq = typename sequence::make_N_Sequence<type_list::size<Tuple0>::value>::type;
		return deteil::zip_impl(seq(), t0, t...);
	}
}