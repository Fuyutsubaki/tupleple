#ifndef TUPLEPLE_TUPLE_TRAITS_HPP
#define TUPLEPLE_TUPLE_TRAITS_HPP

#include<tupleple\type_list\at.hpp>
#include<tupleple\type_list\size.hpp>
#include<utility>
#include"at.hpp"
namespace tupleple
{
	template<class Tuple, class Enabler = void>
	struct tuple_trait
	{
		template<class >
		struct false_
		{
			static const bool value = false;

		};
		using is_not_define = void;
	};
	template<class Tuple, class Enabler = void>
	struct is_tuple
		:std::true_type
	{};
	template<class Tuple>
	struct is_tuple<Tuple, typename tuple_trait<Tuple>::is_not_define>
		:std::false_type
	{};

	template<class T>
	using Enabler_is_tuple = typename std::enable_if<is_tuple<T>::value>::type;

	namespace type_list
	{
		template<size_t N, class T>
		struct at<N, T, typename std::enable_if<is_tuple<T>::value>::type>
		{
			using type = typename tuple_trait<T>:: template element<N>::type;
		};
		template< class T>
		struct size<T,typename std::enable_if<is_tuple<T>::value>::type>
		{
			static const size_t value=tuple_trait<T>::size;
		};
	}

	

	template<size_t N, class Tuple>
	class result_of<N,Tuple,typename std::enable_if<is_tuple<utility::remove_cv_ref_t<Tuple>>::value>::type>
	{
		using base_tuple = utility::remove_cv_ref_t <Tuple>;
		using res = typename tuple_trait<base_tuple>::template result_type_of<N, Tuple>;
		using base_result_type = typename res::type;
	public:
		using type = base_result_type;
	};
	template<size_t N, class Tuple>
	auto at(Tuple&&tuple)
		->result_of_t<N, Tuple>
	{
		return tuple_trait<utility::remove_cv_ref_t<Tuple>>::template get<N>(std::forward<Tuple>(tuple));
	}
}





#endif