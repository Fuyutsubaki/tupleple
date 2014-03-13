#pragma once
#include"map.hpp"
#include"tuple.hpp"


namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			//Index s ,Tuple
			template<class Sequence, class Tuple>
			class to_tuple_impl
			{
				template<size_t...N>
				static auto trans(index::Sequence<N...>)
					->std::tuple<at<N, Tuple>...>;
			public:
				using type = decltype(trans(Sequence()));
			};
		}
		template<class Sequence, class Tuple>
		using to_tuple = typename impl::to_tuple_impl<Sequence, Tuple>::type;
	}

	template<size_t ...N,class Tuple>
	inline auto to_tuple(index::Sequence<N...>,const Tuple&tuple)
		->type_list::to_tuple<index::Sequence<N...>, Tuple>
	{
		using result_type = type_list::to_tuple<index::Sequence<N...>, Tuple>;
		return result_type(tupleple::at<N>(tuple)...);
	}
}