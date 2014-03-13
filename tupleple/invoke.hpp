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
				template<size_t ...N>
				static auto trans(index::Sequence<N...>)
					->typename Transform<at<N, Tuple>...>::type;
			public:
				using type = decltype(trans(index::make_seq<size<Tuple>::value>()));
			};
		}
		template<template<class...>class Transform, class Tuple>
		using invoke = typename impl::invoke_impl<Transform, Tuple>::type;
	}
}