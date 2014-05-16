#pragma once
#include"Index.hpp"
#include"utility.hpp"
namespace tupleple
{
	namespace utility
	{
		namespace deteil
		{
			template<class Seq>
			struct at_impl{};

			template<size_t ...Idxs>
			struct at_impl<index::Sequence<Idxs...>>
			{
				template<size_t>
				struct do_nothing
				{
					template<class T>
					do_nothing(T&&){}
				};

				template<class T, class ...R>
				static T&&at(do_nothing<Idxs>..., T&&a, R&&...)
				{
					return std::forward<T>(a);
				}
			};
		}

		template<size_t N, class...R>
		auto value_at(R&&...args)
			->decltype(deteil::at_impl<index::make_seq_t<N>>::at(std::declval<R>()...))
		{
			return deteil::at_impl<index::make_seq_t<N>>::at(std::forward<R>(args)...);
		}

		template<class...T>
		struct type_at
		{
			using R = decltype(value_at(utility::identity<T>{}...));
			using type = typename typename std::remove_reference<R>::type::type;
		};
		template<class...T>
		using type_at_t = typename type_at<T...>::type;
	}
}