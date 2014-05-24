#pragma once

#include<tupleple\tuple.hpp>
#include<tuple>
namespace tupleple
{
	template<class ...R>
	struct tuple_trait<std::tuple<R...>>
	{
		using tuple_type = std::tuple<R...>;
		template<size_t N>
		using element = std::tuple_element<N, tuple_type>;

		template<size_t N, class Tuple>
		static auto get(Tuple&&tuple)
			->type_list::result_of_t<N,Tuple>
		{
			return std::get<N>(std::forward<Tuple>(tuple));
		}

		template<size_t N,class Tuple>
		struct result_of
		{
			using simple = utility::remove_cv_ref_t<Tuple>;
			using ele = typename std::tuple_element<N, simple>::type;
			using type = utility::trace_cv_ref_t<Tuple&&,ele>;
		};
		static const size_t size = std::tuple_size<tuple_type>::value;
	};
}