#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"

//auto c = tupleple::push(std::make_tuple(1, 2, 3),3);

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple,class T>
		class push
		{
			using seq = typename index::make_N_index<size<Tuple>::value>::type;
			template<size_t ...N>
			static auto trans(std::tuple<index::Index<N>...>)
				->std::tuple<typename at<N, Tuple>::type ...,T>;
		public:
			using type = decltype(trans(seq()));
		};
	}
	namespace deteil
	{
		template<class Tuple, class T>
		struct push_impl
		{
			using result_type = typename tupleple::type_list::push<Tuple, T>::type;
			template<class ...Idx>
			static result_type push(const Tuple&tuple, const T&x, std::tuple<Idx...>)
			{
				return result_type(at<Idx::value>(tuple)..., x);
			}

		};
	}
	template<class Tuple, class T>
	typename type_list::push<Tuple,T>::type push(const Tuple&tuple, const T&x)
	{
		using seq = typename index::make_N_index<type_list::size<Tuple>::value>::type;
		return deteil::push_impl<Tuple, T>::push(tuple, x, seq());
	}
}