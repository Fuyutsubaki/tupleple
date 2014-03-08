#pragma once 
#include"tuple.hpp"
#include"Index.hpp"


namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			template<template<class...>class Transform, class Tuple>
			class invoke_impl
			{
				template<class ...Idx>
				static auto trans(std::tuple<Idx...>)
					->typename Transform<index::at_helper<Idx, Tuple>...>::type;
			public:
				using type = decltype(trans(index::make_N_index<size<Tuple>::value>()));
			};
		}
		template<template<class...>class Transform, class Tuple>
		using invoke = typename impl::invoke_impl<Transform, Tuple>::type;
	}
}