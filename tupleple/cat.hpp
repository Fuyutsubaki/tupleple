#pragma once
#include"tuple.hpp"
#include<type_traits>
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
			TupleL&&lhs;
			TupleR&&rhs;
		};
		template<class TupleL, class TupleR>
		cat_view<TupleL, TupleR> cat(TupleL&&lhs, TupleR&&rhs)
		{
			return cat_view<TupleL, TupleR>(std::forward<TupleL>(lhs), std::forward<TupleR>(rhs));
		}
	}
	template<class TupleL, class TupleR>
	class tuple_trait<view::cat_view<TupleL, TupleR>>
	{
		using Lhs = utility::remove_const_ref_t<TupleL>;
		using Rhs = utility::remove_const_ref_t<TupleR>;
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
		struct element
		{
			using type = utility::cond_t<
			(Idx<Lsize),
			type_list::at_t<Idx,Lhs>,
			type_list::at_t<Idx - Lsize, Rhs>
			>;
		};

		template<size_t Idx, class T>
		static auto get(T&&tuple)
			->typename std::enable_if<
			isL<Idx>::value,
			decltype(at<Idx>(utility::foward_member_ref<T, TupleL>(tuple.lhs)))
			>::type
		{
			return utility::foward_member_ref<T, TupleL>(tuple.lhs)
				| at<Idx>();
		}

		template<size_t Idx, class T>
		static auto get(T&&tuple)
			->typename std::enable_if<
			!isL<Idx>::value, 
			decltype(at<Idx - Lsize>(utility::foward_member_ref<T, TupleR>(tuple.rhs)))
			>::type
		{
			return utility::foward_member_ref<T, TupleR>(tuple.rhs)
				| at<Idx - Lsize>();
		}
	};
}