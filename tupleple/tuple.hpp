#pragma once 
#include<tuple>
#include"utility.hpp"
namespace tupleple
{
	template<class Tuple>
	struct tuple_definer
	{
		static_assert(sizeof(Tuple)>0, "this is not define");
	};

	namespace type_list
	{
		namespace impl
		{
			template<size_t N, class Tuple>
			struct at_impl
			{
				using type = typename typename tuple_definer<Tuple>::template element<N>::type;
			};
		}
		template<class Tuple>
		struct size
		{
			static const size_t value = tuple_definer<Tuple>::size;
		};

		template<size_t N, class Tuple>
		using at = typename impl::at_impl<N,Tuple>::type;
	}	
	
	template<size_t N, class Tuple>
	auto at(Tuple&&tuple)
		->utility::trace_const_ref<Tuple&&, type_list::at<N, utility::remove_const_ref<Tuple>>>
	{
		return tuple_definer<utility::remove_const_ref<Tuple>>::template get<N>(std::forward<Tuple>(tuple));
	}
	

	template<class ...R>
	struct tuple_definer<std::tuple<R...>>
	{
		using tuple_type = std::tuple<R...>;
		template<size_t N>
		struct element
		{
			using type = typename std::tuple_element<N, tuple_type>::type;
		};
		template<size_t N,class Tuple>
		static auto get(Tuple&&tuple)
			->decltype(std::get<N>(std::forward<Tuple>(tuple)))
		{
			return std::get<N>(std::forward<Tuple>(tuple));
		}
		
		static const size_t size = std::tuple_size<tuple_type>::value;
	};


}
