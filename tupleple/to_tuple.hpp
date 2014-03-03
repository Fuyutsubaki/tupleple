#pragma once
#include"map.hpp"
#include"tuple.hpp"
/*
using seq = std::tuple<tupleple::index::Index<2>, tupleple::index::Index<0>>;
auto r = tupleple::index::to_tuple(seq(), std::make_tuple(1, 2, 3.14));
*/

namespace tupleple
{
	namespace index
	{
		namespace type_list
		{
			namespace impl{
				//Index s ,Tuple
				template<class Idxs, class Tuple>
				class to_tuple_impl
				{
					static_assert(is_tuple<Tuple>::value, "this is not tuple");
					template<class Idx>
					struct Trans
					{
						using type = tupleple::type_list::at<Idx::value, Tuple>;
					};
				public:
					using type = tupleple::type_list::map<Trans, Idxs>;
				};
			}
			template<class Idxs, class Tuple>
			using to_tuple = typename impl::to_tuple_impl<Idxs, Tuple>::type;
		}

		template<class ...Idx,class Tuple>
		inline auto to_tuple(std::tuple<Idx...>,const Tuple&tuple)
			->type_list::to_tuple<std::tuple<Idx...>,Tuple>
		{
			using result_type = type_list::to_tuple<std::tuple<Idx...>, Tuple>;
			return result_type(tupleple::at<Idx::value>(tuple)...);
		}
	}
}