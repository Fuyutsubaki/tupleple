#pragma once
#include"Index.hpp"
namespace tupleple
{

	namespace no_tuple
	{
		template<size_t>
		struct do_nothing
		{
			template<class T>
			do_nothing(T&&){}
		};
		template<size_t N, class Func>
		struct drop_functor
		{
			Func func_;
			template<size_t ...Idxs, class...R>
			auto dropi2(do_nothing<Idxs>...a, R&&...args)
				->std::result_of_t<Func(R...)>
			{
				return func_(std::forward<R>(args)...);
			}
			template<size_t ...Idxs, class...R>
			auto dropi(index::Sequence<Idxs...>, R&&...args)
				->decltype(dropi2<Idxs...>(std::declval<R>()...))
			{
				return dropi2<Idxs...>(std::forward<R>(args)...);
			}

		public:
			drop_functor(Func func)
				:func_(func)
			{}
			template<class ...R>
			auto operator()(R&&...args)
				->decltype(dropi(index::make_seq_t<N>(), std::declval<R>()...))
			{
				return dropi(index::make_seq_t<N>(), std::forward<R>(args)...);
			}
		};

		template<size_t N, class Func>
		drop_functor<N, Func> make_drop(Func&&func)
		{
			return{ std::forward<Func>(func) };
		}

	}
}