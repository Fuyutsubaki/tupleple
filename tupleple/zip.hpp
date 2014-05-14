#pragma once
#include<tuple>
#include"Index.hpp"
#include"map.hpp"
/*
char c = 'X';
int x = 42;
float f = 3.14;
auto t1 = std::make_tuple(c, x, f);
auto t2 = std::tie(c, x, f);
auto t3 = std::make_tuple(&c, &x, &f);

auto result = tupleple::zip(t1,t2,t3);

*/
namespace tupleple
{
	namespace type_list
	{
		namespace flex
		{
			template<class Tuple0, class ...Tuple>
			class zip
			{
				using seq = index::make_tuple<size<Tuple0>::value>;
				template<class Idx>
				struct one_tuple
				{
					using type = std::tuple<at<Idx::value, Tuple0>, at<Idx::value, Tuple>...>;
				};
			public:
				using type = map<one_tuple, seq>;
			};
		}
		template<class L,class R>
		using zip = typename flex::zip<L, R>::type;
	}
	namespace deteil
	{
		template<size_t N, class ...Tuple>
		auto zip_impl2(const Tuple&...t)
			->type_list::at<N, typename type_list::flex::zip<Tuple...>::type>
		{
			using Tuple_=type_list::at<N, typename type_list::flex::zip<Tuple...>::type>;
			return Tuple_(at<N>(t)...);
		}
		template< class ...Tuple,class ...Idx>
		auto zip_impl(std::tuple<Idx...>,const Tuple&...t)
			->typename type_list::flex::zip<Tuple...>::type
		{
			using res_type=typename type_list::flex::zip<Tuple...>::type;
			return res_type(zip_impl2<Idx::value>(t...)...);
		}
	}
	template<class Tuple0,class ...Tuple>
	auto zip(const Tuple0&t0, const Tuple&...t)
		->typename type_list::flex::zip<Tuple0,Tuple...>::type
	{
		using seq = index::make_tuple<type_list::size<Tuple0>::value>;
		return deteil::zip_impl(seq(), t0, t...);
	}



	namespace view
	{
		template<class TupleL, class TupleR>
		class zip_view
		{
			friend tuple_trait<zip_view<TupleL,TupleR>>;
		public:
			zip_view(TupleL&&lhs, TupleR&&rhs)
				:lhs(std::forward<TupleL>(lhs)), rhs(std::forward<TupleR>(rhs))
			{}
		private:
			TupleL lhs;
			TupleR rhs;
		};
	}
	template<class TupleL, class TupleR>
	class tuple_trait<view::zip_view<TupleL, TupleR>>
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
		using result_of = utility::cond_t<
			(Idx<Lsize)
			, type_list::result_of<Idx, utility::result_of_forward_mem_t<T, TupleL>>
			, type_list::result_of<Idx - Lsize, utility::result_of_forward_mem_t<T, TupleR>>
			>;

		template<size_t Idx, class T
			, typename std::enable_if<isL<Idx>::value>::type* = nullptr
		>
		static auto get(T&&tuple)
		->type_list::result_of_t<Idx, T>
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