#ifndef TUPLEPLE_UTILITY_TYPELIST_HPP_0523
#define TUPLEPLE_UTILITY_TYPELIST_HPP_0523

#include<tupleple\utility\utility.hpp>
#include<tupleple\index_tuple\index_sequence.hpp>
#include<tupleple\type_list\List.hpp>
namespace tupleple
{
	namespace index
	{
		
		template<class>struct seq_to_List;
		template<size_t...N>
		struct seq_to_List<Sequence<N...>>
		{
			using type = type_list::List<std::integral_constant<size_t, N>...>;
		};

		template<size_t N>
		using make_List_t = typename seq_to_List<make_seq_t<N>>::type;
	}
}
















#endif