#pragma once
#include"tuple.hpp"
#include"basic_view.hpp"
//using namespace tupleple;
//auto c = std::make_tuple(std::make_unique<int>(1)) | view::do_nothing() | at<0>();
namespace tupleple
{
	namespace view
	{
		struct do_nothing_tag{};
		template<class Tuple>
		using do_nothing_view = utility::basic_view<do_nothing_tag, Tuple>;

		struct do_nothing_forward:utility::ExtensionMemberFunction
		{
			template<class T>
			do_nothing_view<T> operator()(T&&tuple)
			{
				return{ std::forward<T>(tuple) };
			}
		};

		do_nothing_forward do_nothing(){ return{}; }
	}
	template<class Tuple>
	struct tuple_trait<view::do_nothing_view<Tuple>>
	{
		using View = view::do_nothing_view<Tuple>;
		using base = utility::remove_cv_ref_t<Tuple>;
		static const size_t value = type_list::size<base>::value;

		template<size_t N>
		struct element
		{
			using type = type_list::at_t<N, base>;
		};
		template<size_t N,class T>
		static auto get(T&&x)
			->decltype(View::first(std::forward<T>(x)) | at<N>())
		{
			return View::first(std::forward<T>(x)) | at<N>();
		}
	};
}