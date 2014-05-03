#pragma once
#include"tuple.hpp"
#include"utility.hpp"
#include"basic_view.hpp"
/*
using namespace tupleple;
auto x = std::make_tuple(1, 2, 3, 4) | view::reverse() | at<0>();
*/

namespace tupleple
{
	namespace view
	{
		struct reverse_tag{};
		template<class T>
		using reverse_view = utility::basic_view<reverse_tag, T>;
		
		struct reverse_forward:utility::ExtensionMemberFunction
		{
			template<class Tuple>
			reverse_view<Tuple> operator()(Tuple&&tuple)
			{
				return reverse_view<Tuple>(std::forward<Tuple>(tuple));
			}
		};
		inline reverse_forward reverse(){ return{}; }
	}
	template<class Tuple>
	struct tuple_trait<view::reverse_view<Tuple>>
	{
		using Base = utility::remove_cv_ref_t<Tuple>;
		using View = view::reverse_view<Tuple>;
		static const size_t size = type_list::size<Base>::value;
		template<size_t Idx>
		struct element
		{
			using type = type_list::at_t<size - 1 - Idx, Base>;
		};
		template<size_t Idx, class T>
		static auto get(T&&tuple)
			->decltype(View::first(std::forward<T>(tuple)) | at<size - 1 - Idx>())
		{
			return View::first(std::forward<T>(tuple)) | at<size - 1 - Idx>();
		}

	};

}