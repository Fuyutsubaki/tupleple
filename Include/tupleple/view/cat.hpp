#pragma once

#include<type_traits>
#include<tupleple\utility\mem_forward.hpp>
#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\type_list\cat.hpp>
#include<tupleple\type_list\replicate.hpp>
#include<tupleple\STD_tuple_traits.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\utility\view_impl_helper.hpp>
/*
using namespace tupleple;
auto a = std::make_tuple(1, 2);
auto b = std::make_tuple(std::make_unique<int>(42), 'B');
auto c = std::make_tuple(std::string(":-)"), std::string(":-|"));
auto p = view::cat(a, std::move(b), c) | at<2>();

*/
namespace tupleple
{
	namespace view
	{
		template<class Tuple>
		struct flat_view 
			:utility::base_view<flat_view<Tuple>,Tuple>
		{
			flat_view(Tuple&&tuple)
				:isuper(std::forward<Tuple>(tuple))
			{}
		};
		template<class ...T>
		flat_view<std::tuple<T...>> cat(T&&...tuples)
		{
			return std::tuple<T...>{ std::forward<T>(tuples)... };
		}

		
		struct flat_functor :utility::ExtensionMemberFunction
		{
			template<class Tuple>
			flat_view<Tuple> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple) };
			}
		};
		flat_functor flat()
		{
			return{};
		}
	}

	template<class Tuple>
	class tuple_trait<view::flat_view<Tuple>>
		:utility::view_tuple_trait_helper<view::flat_view<Tuple>>
	{
		static const size_t N = base_size;
		template<class Idx>
		struct n_size
		{
			static const size_t value = type_list::size<utility::remove_cv_ref_t<base_element_t<Idx::value>>>::value;
		};
		using Seq = index::make_List_t<N>;
		template<class Idx>
		struct Impl1
		{
			using type = type_list::replicate_t<n_size<Idx>::value, Idx>;
		};
		template<class Idx>
		struct Impl2
		{
			using type = index::make_List_t<n_size<Idx>::value>;
		};


		using Seq1 = typename type_list::flat<typename type_list::map<Seq, Impl1>::type>::type;		//11 2 333
		using Seq2 = typename type_list::flat<type_list::map_t<Seq, Impl2>>::type;//12 1 123
		template<size_t Idx>
		struct F1
			:type_list::at_t<Idx, Seq1>
		{};
		template<size_t Idx>
		struct F2
			:type_list::at_t<Idx, Seq2>
		{};

	public:
		static const size_t size = type_list::size<Seq1>::value;

		template<size_t Idx>
		using element = 
			type_list::at<F2<Idx>::value, base_element_t<F1<Idx>::value>>;
		
		template<size_t Idx, class T>
		using result_type_of =
			result_of < F2<Idx>::value, result_of_t< F1<Idx>::value, result_base_forward_t<T>>>;
		
		template<size_t Idx, class T>
		static auto get(T&&x)
		->result_of_t<Idx, T>
		{
			return base_forward<T>(x) | at<F1<Idx>::value>() | at<F2<Idx>::value>();
		}
	};
}