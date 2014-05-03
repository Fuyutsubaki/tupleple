#pragma once
#include"do_nothing.hpp"


namespace tupleple
{
	template<class T>
	auto foward_as_view(T&&x)
		->view::do_nothing_view<T&&>
	{
		return{ std::forward<T>(x) };
	}
	template<class T>
	auto move_as_view(T&&x)
		->view::do_nothing_view<std::remove_reference_t<T>&&>
	{
		return{ std::move(x) };
	}
}