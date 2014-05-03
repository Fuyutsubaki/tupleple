#pragma once
#include<tuple>
#include"is_view.hpp"


namespace tupleple
{
	namespace utility
	{
		template<class tag, class ...Items>
		class basic_view
		{
			friend tuple_trait<basic_view>;
			using Base = std::tuple<Items...>;
			Base base;
			//View	/ T	-> T&&
			//view	/ T&-> T&
			//View&	/ *-> T&

			template<size_t N, class View>
			static auto get(View&&view)
				->utility::trace_cv_ref_t<View,typename std::tuple_element<N, typename typename utility::remove_cv_ref<View>::type::Base>>
			{
				return std::get<N>(std::forward<View>(view).base);
			}
			template<class View>
			static auto first(View&&view)
				->utility::trace_cv_ref_t<View, typename std::tuple_element<0, typename typename utility::remove_cv_ref<View>::type::Base>>
			{
				return get<0>(std::forward<View>(view));
			}
			template<class View>
			static auto second(View&&view)
				->utility::trace_cv_ref_t<View, typename std::tuple_element<1, typename typename utility::remove_cv_ref<View>::type::Base>>
			{
				return get<1>(std::forward<View>(view));
			}
		public:
			basic_view(Items&&...args)
				: base(std::forward<Items>(args)...)
			{}
		};
	}

	template<class tag, class ...Items>
	struct is_view<utility::basic_view<tag,Items...>>
	{
		static const bool value = true;
	};
}