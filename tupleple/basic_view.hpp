#pragma once
#include<tuple>


namespace tupleple
{
	namespace utility
	{
		template<class tag, class ...Tuples>
		class basic_view
		{
			friend tuple_trait<basic_view>;
			std::tuple<Tuples...> base;
			//View	/ T	-> T&&
			//view	/ T&-> T&
			//View&	/ *-> T&
			template<size_t N, class View>
			static auto get(View&&view)
				->decltype(std::get<N>(std::forward<View>(view).base))
			{
				return std::get<N>(std::forward<View>(view).base);
			}
			template<class View>
			static auto first(View&&view)
				->decltype(get<0>(std::forward<View>(view)))
			{
				return get<0>(std::forward<View>(view));
			}
			template<class View>
			static auto second(View&&view)
				->decltype(get<1>(std::forward<View>(view)))
			{
				return get<1>(std::forward<View>(view));
			}
		public:
			template<class ...R>
			basic_view(R&&...args)
				: base(std::forward<R>(args)...)
			{}
		};
	}
}