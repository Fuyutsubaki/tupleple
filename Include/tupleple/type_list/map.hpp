#ifndef TUPLEPLE_TYPELIST_MAP_HPP
#define TUPLEPLE_TYPELIST_MAP_HPP
#include<tupleple\utility\utility.hpp>
#include<tupleple\index_tuple\index_sequence.hpp>

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class...>class F>
		class map
		{
			static_assert(sizeof(Tuple),"not define");
		};

		template<class...T, template<class...>class F>
		struct map<List<T...>,F>
		{
			using type = List<typename F<T>::type...>;
		};
		template<class Tuple, template<class>class F>
		using map_t = typename map<Tuple, F>::type;
	}


}





#endif