#pragma once

#include<type_traits>
#include<tupleple\utility\mem_forward.hpp>
#include<tupleple\tuple_traits.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\type_list\cat.hpp>
#include<tupleple\type_list\replicate.hpp>
#include<tupleple\STD_tuple_traits.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
/*
using namespace tupleple;
auto a = std::make_tuple(1, 2);
auto b = std::make_tuple(std::make_unique<int>(42), 'B');
auto c = std::make_tuple(std::string(":-)"), std::string(":-|"));

auto s = view::cat(a, move_view(b), c);
auto p = s | at<2>();

*/
namespace tupleple
{
	namespace view
	{
		template<class Tuple>
		class flat_view
		{
			friend tuple_trait<flat_view<Tuple>>;
		public:
			flat_view(Tuple&&tuple)
				:base(std::forward<Tuple>(tuple))
			{}
		private:
			Tuple base;
		};
		template<class ...T>
		flat_view<std::tuple<T...>> cat(T&&...tuples)
		{
			return{ { std::forward<T>(tuples)... } };
		}
		template<class T>
		flat_view<T> flat_test(T&&tuples)
		{
			return{ std::forward<T>(tuples) };
		}
	}

	template<class Tuple>
	class tuple_trait<view::flat_view<Tuple>>
	{
		using base = utility::remove_cv_ref_t<Tuple>;
		static const size_t N = type_list::size<base>::value;
		template<class Idx>
		struct n_size
		{
			static const size_t value = type_list::size<utility::remove_cv_ref_t<type_list::at_t<Idx::value, base>>>::value;
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
		using element = type_list::at<F2<Idx>::value, type_list::at_t<F1<Idx>::value, base>>;

		template<size_t Idx, class T>
		using result_type_of =  result_of<F2<Idx>::value, result_of_t<F1<Idx>::value, decltype(utility::mem_forward<Tuple>(std::declval<T>().base))>>;
		template<size_t Idx, class T>
		static auto get(T&&x)
		->result_of_t<Idx, T>
		{
			 utility::mem_forward<Tuple>(std::forward<T>(x).base) | at<F1<Idx>::value>() | at<F2<Idx>::value>();
		}
	};
}