#pragma once
#include<functional>
#include<tuple>
#include"Index.hpp"
namespace tupleple
{
	namespace deteil{
		template<class R, class ...Args, size_t ...N >
		std::function<R(std::tuple<Args...>&&)> fuse_cast_impl(const std::function<R(Args...)>&func, std::tuple<index::Index<N>...>)
		{
			return [=](std::tuple<Args...>&&tuple)
			{
				return func(std::get<N>(tuple)...);
			};
		}
	}
	template<class R, class ...Args>
	std::function<R(std::tuple<Args...>&&)> fuse_cast(const std::function<R(Args...)>&func)
	{
		using List = typename index::make_N_index<sizeof...(Args)>::type;
		return deteil::fuse_cast_impl(func, List());
	}
}