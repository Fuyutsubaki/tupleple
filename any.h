#pragma once
#include<tuple>
#include"sequence.hpp"


namespace tupleple
{
	namespace type_list
	{
		template<class Tuple,template<class T>class Pred>
		class any;

		template<class ...R, template<class T>class Pred>
		class any<std::tuple<R...>,Pred>
		{
			template<size_t ...T>
			struct eval;
			template<size_t H,size_t ...T>
			struct eval<H,T...>
			{
				static const bool value = H || eval<T...>::value;
			};
			template<>
			struct eval<>
			{
				static const bool value = 0;
			};
		public:
			static const bool value = eval<Pred<R>::value...>::value;
		};
	}

	namespace deteil
	{
		template<bool r, size_t N, class Tuple>
		struct any_impl2;
		template<size_t N, class Tuple>
		struct any_impl :any_impl2<N<std::tuple_size<Tuple>::value,N,Tuple>
		{};
		template<size_t N,class Tuple>
		struct any_impl2<true, N, Tuple>
		{
			template<class Pred>
			inline static bool any(const Tuple&tuple,const Pred&pred)
			{
				return pred(std::get<N>(tuple))||any_impl<N + 1, Tuple>::any(tuple,pred);
			}
		};
		template<size_t N, class Tuple>
		struct any_impl2<false,N,Tuple>
		{
			template<class Pred>
			inline static bool any(const Tuple&, const Pred&)
			{
				return 0;
			}
		};
	}

	template<class ...R,class Pred>
	bool any(const std::tuple<R...>&tuple,const Pred&pred)
	{
		return deteil::any_impl<0, std::tuple<R...>>::any(tuple,pred);
	}

}



