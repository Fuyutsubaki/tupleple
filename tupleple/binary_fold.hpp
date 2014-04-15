#pragma once
#include"drop.hpp"
#include"take.hpp"
#include"map.hpp"
#include"tuple.hpp"

/*
struct plus
{
	template<class L,class R>
	auto operator()(L l,R r)const
	->decltype(l+r)
	{
	return l+r;
	}
};

int main()
{
	using namespace tupleple;
	auto t = std::make_tuple(1, 1.4f, 31.4, 18L);
	auto x = algorithm::binary_fold(t, plus());
}
*/


namespace tupleple
{
	namespace algorithm
	{
		namespace deteil
		{
			template<class Tuple, class binary_func>
			struct binary_fold_result_type
			{
				static const size_t N = type_list::size<utility::remove_const_ref_t<Tuple>>::value;
				using type = decltype(
					std::declval<binary_func>()(
					binary_fold(std::declval<Tuple>() | view::take<N / 2>(), std::declval<binary_func>()),
					binary_fold(std::declval<Tuple>() | view::drop<N / 2>(), std::declval<binary_func>())
					));
			};
		}

		template<class Tuple, class binary_func>
		auto binary_fold(Tuple&&tuple, binary_func&&func)
			->utility::lazy_enable_if_t<
			(type_list::size<utility::remove_const_ref_t<Tuple>>::value > 1)
			, deteil::binary_fold_result_type<Tuple, binary_func>
			>
		{
			static const size_t N = type_list::size<utility::remove_const_ref_t<Tuple>>::value;
			return std::forward<binary_func>(func)(
				binary_fold(std::forward<Tuple>(tuple) | view::take<N / 2>(), std::forward<binary_func>(func))
				, binary_fold(std::forward<Tuple>(tuple) | view::drop<N / 2>(), std::forward<binary_func>(func))
				);
		}
		template<class Tuple, class binary_func>
		auto binary_fold(Tuple&&tuple, binary_func&&)
			->typename std::enable_if<
			(type_list::size<utility::remove_const_ref_t<Tuple>>::value == 1)
			, decltype(std::forward<Tuple>(tuple) | at<0>())
			>::type
			//«fuckin “®‚©‚Ë‚¥
			/*->std::enable_if_t<
			(type_list::size<utility::remove_const_ref_t<Tuple>>::value == 1)
			, decltype(std::forward<Tuple>(tuple) | at<0>())
			>*/
		{
			return std::forward<Tuple>(tuple) | at<0>();
		}

	}
}