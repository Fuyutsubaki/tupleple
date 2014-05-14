#pragma once

#include"Index.hpp"
#include"tuple.hpp"
#include"map.hpp"
#include"utility.hpp"
#include"cat.hpp"

/*
	using namespace tupleple;
	auto r = std::make_tuple(false, "ABC", 3.14, 42);
	auto c= r | view::filter<std::is_integral>();
	std::cout << (c | at<1>());
*/
namespace tupleple
{
	
	namespace view
	{
		template<class Tuple,template<class>class Pred>
		struct filter_view
		{
			Tuple base;
			friend tuple_trait<view::filter_view<Tuple, Pred>>;
		public:
			filter_view(Tuple&&tuple)
				:base(std::forward<Tuple>(tuple))
			{}
		};

		template<template<class>class Pred>
		struct filter_foward :utility::ExtensionMemberFunction
		{
			template<class Tuple>
			filter_view<Tuple, Pred> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple) };
			}
		};

		template<template<class>class Pred>
		inline filter_foward<Pred> filter()
		{
			return{};
		}

	}

	namespace type_list
	{
		template<class Tuple,template<class>class Pred>
		struct filter
		{
			using type = view::filter_view<Tuple, Pred>;
		};
	}
	template<class Tuple, template<class>class Pred>
	class tuple_trait<view::filter_view<Tuple, Pred>>
	{
		using base = utility::remove_cv_ref_t<Tuple>;
		using Seq = index::seq_to_tuple_t<index::make_tuple_size_seq_t<base>>;
		template<class Idx>
		struct Trans
		{
			using type = utility::cond_t<Pred<type_list::at_t<Idx::value, Tuple>>::value, std::tuple<Idx>, std::tuple<>>;
		};
		using Seqr = type_list::map_t<Seq, Trans>;
		using Res = type_list::flat_t<Seqr>;
		template<size_t N>
		struct F 
		{
			static const size_t value =  type_list::at_t<N, Res>::value;
		};
	public:
		static const size_t size = type_list::size<Res>::value;
		
		template<size_t N>
		using element = type_list::at<F<N>::value, base>;

		template<size_t N, class T>
		using result_of
			= type_list::result_of<F<N>::value, utility::result_of_forward_mem_t<T, Tuple>>;

		template<size_t N, class T>
		static auto get(T&&x)
			->type_list::result_of_t<N, T>
		{
			return utility::forward_mem<T, Tuple>(x.base) | at<F<N>::value>();
		}
	};



}