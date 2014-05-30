#ifndef TUPLEPLE_TUPLE_HPP_0523
#define TUPLEPLE_TUPLE_HPP_0523

#include<tuple>
#include<tupleple\utility\utility.hpp>
#include<tupleple\tuple_traits.hpp>
namespace tupleple
{
	
	namespace type_list
	{
		template<size_t N, class Tuple>
		class result_of
		{
			using base_tuple = utility::remove_cv_ref_t <Tuple>;
			using res = typename tuple_trait<base_tuple>::template result_of<N, Tuple>;
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
	struct at_functor :utility::ExtensionMemberFunction
	{
		template<class Tuple>
		auto operator () (Tuple&&tuple)
			->type_list::result_of_t<N, Tuple>
		{
			return at<N>(std::forward<Tuple>(tuple));
		}
	};
	template<size_t N>
	at_functor<N> at(){ return{}; }


	




}



#endif