#ifndef TUPLEPLE_TYPELIST_MAP_HPP
#define TUPLEPLE_TYPELIST_MAP_HPP
#include<tupleple\utility\utility.hpp>
#include<tupleple\utility\index_tuple.hpp>
#include<tupleple\tuple.hpp>
namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class>class F>
		class map
		{
			template<size_t ...Idx>
			static auto trans(index::Sequence<Idx...>)
				->std::tuple<typename F< at_t<Idx, Tuple> >::type ...>;
			using seq = index::make_tuple_size_seq_t<Tuple>;
		public:
			using type = decltype(trans(seq()));
		};
		template<class Tuple, template<class>class F>
		using map_t = typename map<Tuple, F>::type;
	}


}





#endif