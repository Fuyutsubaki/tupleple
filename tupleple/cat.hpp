#pragma once
#include"tuple.hpp"
#include<type_traits>
#include"binary_fold.hpp"

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
		template<class TupleL,class TupleR>
		class cat_view
		{
			friend tuple_trait<cat_view>;
		public:
			cat_view(TupleL&&lhs, TupleR&&rhs)
				:lhs(std::forward<TupleL>(lhs)), rhs(std::forward<TupleR>(rhs))
			{}
		private:
			TupleL lhs;
			TupleR rhs;
		};

		namespace deteil
		{
			struct cat_impl
			{
				template<class TupleL, class TupleR>
				cat_view<TupleL, TupleR> operator()(TupleL&&lhs, TupleR&&rhs)
				{
					return cat_view<TupleL, TupleR>(std::forward<TupleL>(lhs), std::forward<TupleR>(rhs));
				}
			};
			template<class...R>
			struct cat_result
			{
				using type = decltype(algorithm::binary_fold(std::declval<std::tuple<R&&...>>(), std::declval<deteil::cat_impl>()));
			};
		}
		
		template<class ...R>
		auto cat(R&&...tuple)
			->typename deteil::cat_result<R...>::type
		{
			return algorithm::binary_fold(std::forward_as_tuple(std::forward<R>(tuple)...),deteil::cat_impl());
		}
	}

	namespace type_list
	{
		template<class ...R>
		struct cat
		{
			template<class L, class R>
			struct cat_
			{
				using type = view::cat_view<L, R>;
			};
			using type = binary_fold_t<std::tuple<R...>, cat_>;
		};
		template<class ...R>
		using cat_t = typename cat<R...>::type;
	}

	template<class TupleL, class TupleR>
	class tuple_trait<view::cat_view<TupleL, TupleR>>
	{
		using Lhs = utility::remove_cv_ref_t<TupleL>;
		using Rhs = utility::remove_cv_ref_t<TupleR>;
		static const size_t Lsize = type_list::size<Lhs>::value;
		static const size_t Rsize = type_list::size<Rhs>::value;
		
		template<size_t Idx>
		struct isL
		{
			static const bool value = (Idx < Lsize);
		};
	public:
		static const size_t size = Lsize + Rsize;

		template<size_t Idx>
		using element = utility::cond_t <
			(Idx<Lsize),
			type_list::at_t<Idx, Lhs>,
			type_list::at_t<Idx - Lsize, Rhs>
			>;

		template<size_t Idx, class T>
		using result_of = utility::cond_t<
			(Idx<Lsize)
			, type_list::result_of<Idx, utility::result_of_forward_mem_t<T, TupleL>>
			, type_list::result_of<Idx - Lsize, utility::result_of_forward_mem_t<T, TupleR>>
			>;

		template<size_t Idx, class T
			,typename std::enable_if<isL<Idx>::value>::type* =nullptr
		>
		static auto get(T&&tuple)
		->type_list::result_of_t<Idx,T>
		{
			return utility::forward_mem<T, TupleL>(tuple.lhs)
				| at<Idx>();
		}

		template<size_t Idx, class T
			, typename std::enable_if<!isL<Idx>::value>::type* = nullptr
		>
		static auto get(T&&tuple)
		->type_list::result_of_t<Idx, T>
		{
			return utility::forward_mem<T, TupleR>(tuple.rhs)
				| at<Idx - Lsize>();
		}
	};
}