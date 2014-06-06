#pragma once

//
//namespace tupleple
//{
//	template<class T>
//	auto move_view(T&&x)
//		->view::do_nothing_view<std::remove_reference_t<T>&&>
//	{
//		return{ std::move(x) };
//	}
//
//	template<class T>
//	auto forward_view(std::remove_reference_t<T>&x)
//		->utility::cond_t<std::is_lvalue_reference<T>::value, T, view::do_nothing_view<T&&>>
//	{
//		return{ std::forward<T>(x) };
//	}
//	template<class T>
//	struct result_of_forward_view
//	{
//		using type = utility::cond_t<std::is_lvalue_reference<T>::value, T, view::do_nothing_view<T&&>>;
//	};
//
//	template<class T>
//	using result_of_forward_view_t = typename result_of_forward_view<T>::type;
//}