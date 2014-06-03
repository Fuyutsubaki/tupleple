#pragma once

#include<type_traits>
#include<tupleple\utility\mem_forward.hpp>
#include<tupleple\tuple_traits.hpp>

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
			friend tuple_trait<cat_view<TupleL, TupleR>>;
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
			type_list::at<Idx, Lhs>,
			type_list::at<Idx - Lsize, Rhs>
			>;

		template<size_t Idx, class T>
		using result_type_of = void;/* utility::cond_t<
			(Idx<Lsize)
			, result_of<Idx, utility::result_of_mem_forward_t<T, TupleL>>
			, result_of<Idx - Lsize, utility::result_of_mem_forward_t<T, TupleR>>
			>;
*/
		template<size_t Idx, class T
			,typename std::enable_if<isL<Idx>::value>::type* =nullptr
		>
		static auto get(T&&tuple)
		->result_of_t<Idx,T>
		{
			return utility::mem_forward<TupleL>(tuple.lhs)
				| at<Idx>();
		}

		template<size_t Idx, class T
			, typename std::enable_if<!isL<Idx>::value>::type* = nullptr
		>
		static auto get(T&&tuple)
		->result_of_t<Idx, T>
		{
			return utility::mem_forward< TupleR>(tuple.rhs)
				| at<Idx - Lsize>();
		}
	};
}