#pragma once
#include<type_traits>
#include<tupleple\index_tuple\index_sequence.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\type_list\size.hpp>

namespace tupleple
{

	namespace deteil
	{
		template<class Tuple, class Functor, size_t ...index>
		typename std::result_of<Functor(result_of_t<index, Tuple>...)>::type
			apply_impl(Tuple&&tuple, Functor&&functor, index::Sequence<index...>)
		{
				return std::forward<Functor>(functor)((std::forward<Tuple>(tuple) | at<index>())...);
		}
	}

	template<class Tuple,class Functor>
	auto apply(Tuple&&tuple, Functor&&functor)
		->decltype(deteil::apply_impl(std::declval<Tuple>()
		, std::declval<Functor>()
		, index::make_seq_t<type_list::size<utility::remove_cv_ref_t<Tuple>>::value>{}))
	{
		return deteil::apply_impl(std::forward<Tuple>(tuple)
			, std::forward<Functor>(functor)
			, index::make_seq_t<type_list::size<utility::remove_cv_ref_t<Tuple>>::value>{});
	}

	template<class Functor>
	class apply_functor
	{
		Functor func_;
	public:
		apply_functor(Functor&&func_)
			:func_(std::forward<Functor>(func_))
		{}
		template<class Tuple>
		auto operator()(Tuple&&tuple)
			->decltype(apply(std::declval<Tuple>(), std::declval<Functor>()))
		{
			return apply(std::forward<Tuple>(tuple), std::forward<Functor>(func_));
		}
	};

	template<class Functor>
	apply_functor<Functor> make_apply(Functor&&functor)
	{
		return{ std::forward<Functor>(functor) };
	}
}