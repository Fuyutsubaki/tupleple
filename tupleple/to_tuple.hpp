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
			//Index s ,Tuple
			template<class Idxs, class Tuple>
			class to_tuple
			{
				static_assert(is_tuple<Tuple>::value, "this is not tuple");
				template<class Idx>
				struct Trans
				{
					using type =  typename tupleple::type_list::at<Idx::value, Tuple>::type;
				};
			public:
				using type = typename tupleple::type_list::map<Trans, Idxs>::type;
			};
		}

		template<class ...Idx,class Tuple>
		auto to_tuple(std::tuple<Idx...>,const Tuple&tuple)
			->typename type_list::to_tuple<std::tuple<Idx...>,Tuple>::type
		{
			using result_type = typename type_list::to_tuple<std::tuple<Idx...>, Tuple>::type;
			return result_type(tupleple::at<Idx::value>(tuple)...);
		}



	}
}