#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"

//auto c = tupleple::cons(3, std::make_tuple(1, 2, 3));

namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			template<class T, class Tuple>
			class cons_impl
			{
				using seq = index::make_seq<size<Tuple>::value>;
				template<size_t ...N>
				static auto trans(index::Sequence<N...>)
					->std::tuple<T, at<N, Tuple> ...>;
			public:
				using type = decltype(trans(seq()));
			};
		}
		template<class T, class Tuple>
		using cons = typename impl::cons_impl < T,Tuple>::type;
	}
	namespace deteil
	{
		template<class T, class Tuple>
		struct cons_impl
		{
			using result_type = tupleple::type_list::cons<T, Tuple>;
			template<size_t ...N>
			static result_type cons(const T&x, const Tuple&tuple, index::Sequence<N...>)
			{
				return result_type(x, at<N>(tuple)...);
			}

		};
	}
	template<class T, class Tuple>
	type_list::cons<T, Tuple> cons(const T&x,const Tuple&tuple)
	{
		using seq = index::make_seq<type_list::size<Tuple>::value>;
		return deteil::cons_impl<T, Tuple>::cons(x, tuple, seq());
	}
}