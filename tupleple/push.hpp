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
				using seq = index::make_seq<size<Tuple>::value>;
				template<size_t ...N>
				static auto trans(index::Sequence<N...>)
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
			template<size_t ...N>
			static result_type push(const Tuple&tuple, const T&x, index::Sequence<N...>)
			{
				return result_type(at<N>(tuple)..., x);
			}

		};
	}
	template<class Tuple, class T>
	type_list::push<Tuple,T> push(const Tuple&tuple, const T&x)
	{
		using seq = index::make_seq<type_list::size<Tuple>::value>;
		return deteil::push_impl<Tuple, T>::push(tuple, x, seq());
	}
}