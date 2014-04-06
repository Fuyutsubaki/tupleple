#pragma once 
#include<tuple>
#include"utility.hpp"
namespace tupleple
{
	template<class Tuple,class Enabler=void>
	struct tuple_trait
	{
		static_assert(sizeof(Tuple)>0, "this is not define");
	};

	namespace type_list
	{
		template<size_t N, class Tuple>
		class at
		{
			using base_tuple = utility::remove_const_ref_t <Tuple>;
			using base_result_type = typename typename tuple_trait<base_tuple>::template element<N>::type;
		public:
			using type = base_result_type;
		};

		template<class Tuple>
		struct size
		{
			static const size_t value = tuple_trait<Tuple>::size;
		};

		template<size_t N, class Tuple>
		using at_t = typename at<N,Tuple>::type;
	}	
	
	namespace deteil
	{
		//コンパイラ的な都合
		template<class Tuple,size_t N>
		struct at_result
		{
			using traits = tuple_trait<utility::remove_const_ref_t<Tuple>>;
			using type = decltype(traits::template get<N>(std::forward<Tuple>(std::declval<Tuple&&>())));
		};
		
	}

	template<size_t N, class Tuple>
	auto at(Tuple&&tuple)
		->typename deteil::at_result<Tuple,N>::type
	{
		return tuple_trait<utility::remove_const_ref_t<Tuple>>::template get<N>(std::forward<Tuple>(tuple));
	}
	
	template<size_t N>
	struct at_foward
	{
		template<class Tuple>
		friend auto operator | (Tuple&&tuple, at_foward)
			->typename deteil::at_result<Tuple, N>::type
		{
			return tuple_trait<utility::remove_const_ref_t<Tuple>>::template get<N>(std::forward<Tuple>(tuple));
		}
	};
	template<size_t N>
	at_foward<N> at(){ return at_foward<N>(); }

	template<class ...R>
	struct tuple_trait<std::tuple<R...>>
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
