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
		namespace impl
		{
			template<class Tuple, class binary_func,class =void>
			struct binary_fold_impl
			{
				static const size_t N = type_list::size<utility::remove_const_ref_t<Tuple>>::value;
				using Lhs = binary_fold_impl<view::take_view<N / 2, Tuple>, binary_func>;
				using Rhs = binary_fold_impl<view::drop_view<N / 2, Tuple>, binary_func>;

				using result_type =
					typename std::result_of<binary_func(typename Lhs::result_type, typename Rhs::result_type)>::type;

				static result_type fold(Tuple&&tuple, binary_func&&func)
				{
					return std::forward<binary_func>(func)(
						Lhs::fold(std::forward<Tuple>(tuple) | view::take<N / 2>(), std::forward<binary_func>(func))
						,Rhs::fold(std::forward<Tuple>(tuple) | view::drop<N / 2>(), std::forward<binary_func>(func))
						);
				}
			};
			template<class Tuple, class binary_func>
			struct binary_fold_impl<Tuple, binary_func,
				typename std::enable_if<(type_list::size<utility::remove_const_ref_t<Tuple>>::value==1)>::type>
			{
				using result_type = decltype(std::declval<Tuple>() | at<0>());
				static auto fold(Tuple&&tuple, binary_func&&func)
					->result_type
				{
					return std::forward<Tuple>(tuple) | at<0>();
				}
			};
		}
		template<class Tuple, class binary_func>
		auto binary_fold(Tuple&&tuple, binary_func&&func)
			->typename impl::binary_fold_impl<Tuple, binary_func>::result_type
		{
			return impl::binary_fold_impl<Tuple, binary_func>::fold(std::forward<Tuple>(tuple), std::forward<binary_func>(func));
		}

	}
}