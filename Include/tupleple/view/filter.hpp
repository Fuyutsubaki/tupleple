#pragma once

#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\type_list\filter.hpp>
#include<tupleple\at.hpp>
#include<tupleple\utility\view_impl_helper.hpp>

/*
	using namespace tupleple;
	auto r = std::make_tuple(false, "ABC", 3.14, 42);
	auto c= r | view::filter_if<std::is_integral>();
	std::cout << (c | at<1>());
*/

namespace tupleple
{
	
	namespace view
	{
		template<class Tuple,template<class>class Pred>
		struct filter_view
			:utility::base_view<filter_view<Tuple,Pred>,Tuple>
		{
			filter_view(Tuple&&tuple)
				:isuper(std::forward<Tuple>(tuple))
			{}
		};

		template<template<class>class Pred>
		struct filter_if_functor :utility::ExtensionMemberFunction
		{
			template<class Tuple>
			filter_view<Tuple, Pred> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple) };
			}
		};

		template<template<class>class Pred>
		inline filter_if_functor<Pred> filter_if()
		{
			return{};
		}
		template<class T>
		struct filter_functor :utility::ExtensionMemberFunction
		{
			template<class U>
			struct same_:std::is_same<T,U>
			{};
			template<class Tuple>
			filter_view<Tuple, same_> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple) };
			}
		};

		template<class T>
		inline filter_functor<T> filter()
		{
			return{};
		}
	}

	template<class Tuple, template<class>class Pred>
	class tuple_trait<view::filter_view<Tuple, Pred>>
		:utility::view_tuple_trait_helper<view::filter_view<Tuple, Pred>>
	{
		static const size_t N = base_size;

		template<class Idx>
		struct Impl
			:Pred<base_element_t<Idx::value>>
		{};
		using Seq = type_list::filter_if_t<index::make_List_t<N>, Impl>;

		template<size_t N>
		struct F
		{
			static const size_t value = type_list::at_t<N, Seq>::value;
		};
	public:
		static const size_t size = type_list::size<Seq>::value;
		
		template<size_t N>
		using element = base_element<F<N>::value>;

		template<size_t N, class T>
		using result_type_of
			= base_result_type_of<F<N>::value,T>;

		template<size_t N, class T>
		static auto get(T&&x)
			->result_of_t<N, T>
		{
			return base_forward<T>(x) | at<F<N>::value>();
		}
	};



}