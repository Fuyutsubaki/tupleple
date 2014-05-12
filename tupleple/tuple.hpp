#pragma once 
#include<tuple>
#include"utility.hpp"
namespace tupleple
{
	template<class Tuple,class Enabler=void>
	struct tuple_trait
	{
		using is_not_define = void;
	};

	namespace type_list
	{
		template<size_t N, class Tuple>
		class at
		{
			using type = typename typename tuple_trait<utility::remove_cv_ref_t <Tuple>>::template element<N>::type;
		};

		template<class Tuple>
		struct size
		{
			static const size_t value = tuple_trait<Tuple>::size;
		};

		template<size_t N, class Tuple>
		using at_t = typename at<N,Tuple>::type;

		template<size_t N, class Tuple>
		class result_of
		{
			using base_tuple = utility::remove_cv_ref_t <Tuple>;
			using res =  typename tuple_trait<base_tuple>::template result_of<N, Tuple>;
			using base_result_type = typename res::type;
		public:
			using type = base_result_type;
		};
		template<size_t N, class Tuple>
		using result_of_t = typename result_of<N, Tuple>::type;
	}	


	template<size_t N, class Tuple>
	auto at(Tuple&&tuple)
		->type_list::result_of_t<N, Tuple>
	{
		return tuple_trait<utility::remove_cv_ref_t<Tuple>>::template get<N>(std::forward<Tuple>(tuple));
	}
	
	template<size_t N>
	struct at_foward:utility::ExtensionMemberFunction
	{
		template<class Tuple>
		auto operator () (Tuple&&tuple)
			->type_list::result_of_t<N, Tuple>
		{
			auto r = std::is_lvalue_reference<Tuple>::value;
			return at<N>(std::forward<Tuple>(tuple));
		}
	};
	template<size_t N>
	at_foward<N> at(){ return{}; }

	
	template<class Tuple,class Enabler=void>
	struct is_tuple
		:std::true_type
	{};
	template<class Tuple>
	struct is_tuple<Tuple, typename tuple_trait<Tuple>::is_not_define>
		:std::false_type
	{};

	


}
