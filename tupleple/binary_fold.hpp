#pragma once
#include"drop.hpp"
#include"take.hpp"
#include"map.hpp"
#include"tuple.hpp"

/*
template<class L,class R>
struct MaxSize
{
	using type = tupleple::utility::cond<(sizeof(L)>sizeof(R)), L, R > ;
};
int main()
{
	using tuple = std::tuple<char, long long, int>;
	using t = tupleple::type_list::binary_fold1<MaxSize, tuple>;
	std::cout << typeid(t).name();
}
*/


namespace tupleple
{
	namespace algorithm
	{
		namespace deteil
		{
			template<size_t N>
			struct binary_fold_impl;
		}

		template<class Tuple, class binary_func>
		auto binary_fold(Tuple&&tuple, binary_func&&func)
			->decltype(deteil::binary_fold_impl<type_list::size<utility::remove_const_ref_t<Tuple>>::value>
			::fold(std::forward<Tuple>(tuple), std::forward<binary_func>(func)))
		{
			return 
				deteil::binary_fold_impl<type_list::size<utility::remove_const_ref_t<Tuple>>::value>
				::fold(std::forward<Tuple>(tuple), std::forward<binary_func>(func));
		}
		namespace deteil
		{
			template<size_t N>
			struct binary_fold_impl
			{
				static_assert(N<10,"Fuck");
				template<class Tuple, class binary_func>
				static auto fold(Tuple&&tuple, binary_func&&func)
					->decltype(std::forward<binary_func>(func)(
					binary_fold(std::forward<Tuple>(tuple) | view::take<N / 2>(), std::forward<binary_func>(func))
					, binary_fold(std::forward<Tuple>(tuple) | view::drop<N / 2>(), std::forward<binary_func>(func))
					))
				{
					return std::forward<binary_func>(func)(
						binary_fold(std::forward<Tuple>(tuple) | view::take<N / 2>(), std::forward<binary_func>(func))
						, binary_fold(std::forward<Tuple>(tuple) | view::drop<N / 2>(), std::forward<binary_func>(func))
						);
				}
			};
			template<>
			struct binary_fold_impl<1>
			{
				template<class Tuple, class binary_func>
				static auto fold(Tuple&&tuple, binary_func&&)
					->decltype(at<0>(std::forward<Tuple>(tuple)))
				{
					return std::forward<Tuple>(tuple) | at<0>();
				}
			};
			template<>
			struct binary_fold_impl<0>
			{};
		}
	}
}