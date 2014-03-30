#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"
#include<type_traits>
/*
using tuple = std::tuple<char, int, void*>;
using r = tupleple::type_list::map<std::add_pointer, tuple>;
*/

/*
struct Func
{
	template<class T>
	std::pair<T, size_t> operator()(T x)const
	{
		return std::pair<T, size_t>(x, sizeof(x));
	}
};

int main()
{
	auto r = tupleple::map(std::make_tuple('X', 3), Func());
}
*/


namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class T>class Transform>
		class map
		{
			using seq = index::make_tuple_size_seq_t<Tuple>;

			template<size_t ...N>
			static auto trans(index::Sequence<N...>)
				->std::tuple<typename Transform<at_t<N, Tuple>>::type...>;
		public:
			using type = decltype(trans(seq()));
		};
		template<class Tuple, template<class T>class Transform>
		using map_t = typename map<Tuple, Transform>::type;
	}
	namespace deteil
	{
		template<class Tuple, class Func>
		class map_impl
		{
			template<class T>
			struct map_r
			{
				using type = typename std::result_of<Func(T)>::type;
			};
		public:
			using type = type_list::map_t< Tuple, map_r >;
			template<class Tuple, class Func, size_t ...N>
			static type map(const Tuple&tuple, const Func&func, index::Sequence<N...>)
			{
				return type(func(at<N>(tuple))...);
			}
		};
	}
	template<class Func,class Tuple>
	typename deteil::map_impl<Tuple,Func>::type map(const Tuple&tuple, const Func&func)
	{
		using seq = index::make_tuple_size_seq_t<Tuple>;
		return deteil::map_impl<Tuple, Func>::map(tuple, func, seq());
	}
}