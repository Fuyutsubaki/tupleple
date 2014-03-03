#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"

//auto c = tupleple::push(std::make_tuple(1, 2, 3),3);

namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			template<class Tuple, class T>
			class push_impl
			{
				using seq = index::make_N_index<size<Tuple>::value>;
				template<size_t ...N>
				static auto trans(std::tuple<index::Index<N>...>)
					->std::tuple<at<N, Tuple> ..., T>;
			public:
				using type = decltype(trans(seq()));
			};
		}
		template<class Tuple, class T>
		using push = typename impl::push_impl<Tuple, T>::type;
	}
	namespace deteil
	{
		template<class Tuple, class T>
		struct push_impl
		{
			using result_type = tupleple::type_list::push<Tuple, T>;
			template<class ...Idx>
			static result_type push(const Tuple&tuple, const T&x, std::tuple<Idx...>)
			{
				return result_type(at<Idx::value>(tuple)..., x);
			}

		};
	}
	template<class Tuple, class T>
	type_list::push<Tuple,T> push(const Tuple&tuple, const T&x)
	{
		using seq = typename index::make_N_index<type_list::size<Tuple>::value>::type;
		return deteil::push_impl<Tuple, T>::push(tuple, x, seq());
	}
}