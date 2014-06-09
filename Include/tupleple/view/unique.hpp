#pragma once

#include<tupleple\utility\view_impl_helper.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\type_list\unique.hpp>
#include<tupleple\type_list\ListStyle.hpp>
namespace tupleple
{
	namespace view
	{
		namespace deteil
		{
			
		}
		//bool(T ,T)
		template<class Tuple>
		struct type_separate_view
			:utility::base_view<type_separate_view<Tuple>, Tuple>
		{
			type_separate_view(Tuple&&tuple)
			:isuper(std::forward<Tuple>(tuple))
			{}
		};
	}
	template<class Tuple>
	struct tuple_trait<view::type_separate_view<Tuple>>
		:utility::view_tuple_trait_helper<view::type_separate_view<Tuple>>
	{
		using seq = index::make_List_t<base_size>;
		using uniqued = type_list::unique_t<base_simple_type>;
		template<class T>
		struct Impl
		{
			template<class Idx>
			struct is_same
				:std::is_same<T, type_list::at_t<Idx::value, base_simple_type>>
			{};

			using type = type_list::filter_if_t<seq, is_same>;
		};

		using seqs = type_list::map_t<uniqued, Impl>;

		static const size_t size = type_list::size<uniqued>::value;
		template<size_t Idx>
		using element = type_list::at<Idx, uniqued>;

		template<size_t Idx,class T>
		struct result_type_of
		{
			using nidx = type_list::front_t<type_list::at_t<Idx, seqs>>;
			using type= base_result_type_of<nidx::value, T>;
		};

		template<size_t N, class T>
		static auto get(T&&x)
			->result_of_t<N, T>
		{
			//‚È‚ñ‚©‘I‚Ô
			return
				(
				base_forward<T>(x) | at<N>()
				);
		}
	};
}