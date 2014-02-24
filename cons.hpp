#pragma once
#include<tuple>
#include"sequence.hpp"

//auto c = tupleple::cons(3, std::make_tuple(1, 2, 3));

namespace tupleple
{
	namespace type_list
	{
		template<class T,class Tuple>
		class cons
		{
			using seq = typename sequence::make_N_Sequence<size<Tuple>::value>::type;
			template<size_t ...N>
			static auto trans(sequence::Sequence<N...>)
				->std::tuple<T,typename at<N,Tuple>::type...>;
		public:
			using type = decltype(trans(seq()));
		};
	}
	namespace deteil
	{
		template<class T, class Tuple>
		struct cons_impl
		{
			using result_type = typename tupleple::type_list::cons<T, Tuple>::type;
			template<size_t ...N>
			static result_type cons(const T&x, const Tuple&tuple, sequence::Sequence<N...>)
			{
				return result_type(x, at<N>(tuple)...);
			}

		};
	}
	template<class T, class Tuple>
	typename type_list::cons<T, Tuple>::type cons(const T&x,const Tuple&tuple)
	{
		using seq = typename sequence::make_N_Sequence < type_list::size<Tuple>::value>::type;
		return deteil::cons_impl<T, Tuple>::cons(x, tuple, seq());
	}
}