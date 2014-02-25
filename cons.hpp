#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"

//auto c = tupleple::cons(3, std::make_tuple(1, 2, 3));

namespace tupleple
{
	namespace type_list
	{
		template<class T,class Tuple>
		class cons
		{
			using seq = typename index::make_N_index<size<Tuple>::value>::type;
			template<size_t ...N>
			static auto trans(std::tuple<index::Index<N>...>)
				->std::tuple<T, typename at<N, Tuple>::type ...>;
			//Fuckin
			/*template<class ...Idx>
			static auto trans(std::tuple<Idx...>)
				->std::tuple<T, typename at<(Idx::value), Tuple>::type ...>;*/
			
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
			template<class ...Idx>
			static result_type cons(const T&x, const Tuple&tuple, std::tuple<Idx...>)
			{
				return result_type(x, at<Idx::value>(tuple)...);
			}

		};
	}
	template<class T, class Tuple>
	typename type_list::cons<T, Tuple>::type cons(const T&x,const Tuple&tuple)
	{
		using seq = typename index::make_N_index<type_list::size<Tuple>::value>::type;
		return deteil::cons_impl<T, Tuple>::cons(x, tuple, seq());
	}
}