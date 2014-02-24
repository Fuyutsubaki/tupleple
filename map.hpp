#pragma once
#include<tuple>
#include"at.hpp"
#include"sequence.hpp"

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple,template<class T>class Transform>
		class map
		{
			using seq = typename sequence::make_N_Sequence<size<Tuple>::value>::type;
			template<size_t ...N>
			static auto trans(sequence::Sequence<N...>)
				->std::tuple<typename Transform<typename at<N, Tuple>::type>::type...>;
		public:
			using type = decltype(trans(seq()));
		};
		//typeÅ®size_t
		template<class Tuple, template<class T>class Pred>
		class map_to_sequence
		{
			using seq = typename sequence::make_N_Sequence<size<Tuple>::value>::type;
			template<size_t ...N>
			static auto trans(sequence::Sequence<N...>)
				->sequence::Sequence<Pred<typename at<N, Tuple>::type>::value...>;
		public:
			using type = decltype(trans(seq()));
		};
	}
}