#pragma once 
#include"utility.hpp"
namespace tupleple{
	namespace sequence{

		template<size_t ...N>
		class Sequence
		{};

		template<size_t X,class T>
		struct cons;
		
		template<size_t X,size_t ...N>
		struct cons<X, Sequence<N...>>
		{
			using type = Sequence<X, N...>;
		};

		
		namespace deteil
		{
			template<size_t N>
			class make_N_Sequence_impl
			{
				template<class T>struct Inc;
				template<size_t ...R>
				struct Inc<Sequence<R...>>
				{
					using type = Sequence<0, (R + 1)...>;
				};
			public:
				using type = typename Inc<typename make_N_Sequence_impl<N - 1>::type>::type;
			};
			template<>
			struct make_N_Sequence_impl<0>
			{
				using type = Sequence<>;
			};
		}
		
		template<size_t N>
		//N->[0,1,2...N-1]
		struct make_N_Sequence:deteil::make_N_Sequence_impl<N>
		{};

		
		
		namespace deteil
		{
			template<size_t N>
			class make_reverse_N_Sequence_impl
			{
				template<size_t ...N>
				static auto trans(Sequence<N...>)->Sequence<(N + 1)..., 0>;
				using rest = typename make_reverse_N_Sequence_impl<N - 1>::type;
			public:
				using type = decltype(trans(std::declval<rest>()));
			};
			template<>
			struct make_reverse_N_Sequence_impl<0>
			{
				using type = Sequence<>;
			};
		}
		template<size_t N>
		//N->[N-1,N-2...1,0]
		struct make_reverse_N_Sequence :deteil::make_reverse_N_Sequence_impl<N>
		{};


		namespace type_list
		{
			template<class Seq,class Tuple>
			struct to_tuple;
			template<size_t ...N, class ...R>
			struct to_tuple<Sequence<N...>,std::tuple<R...>>
			{
				using type = std::tuple < typename std::tuple_element<N, std::tuple<R...>>::type...>;
			};
		}

		template<size_t ...N, class ...R>
		inline auto to_tuple(Sequence<N...>, const std::tuple<R...>&tuple)
			->typename type_list::to_tuple<Sequence<N...>, std::tuple<R...>>::type
		{
			using Tuple = typename  type_list::to_tuple<Sequence<N...>, std::tuple<R...>>::type;
			return Tuple(std::get<N>(tuple)...);
		}



		namespace deteil
		{
			template<size_t N, class Seq>struct bit_filter_impl;
			template<size_t N, size_t head, size_t ...tail>
			struct bit_filter_impl<N, sequence::Sequence<head, tail...>>
			{
			private:
				using Rest = typename bit_filter_impl<N + 1, sequence::Sequence<tail...>>::type;
				using Cons = typename sequence::cons<N, Rest>::type;
			public:
				using type = typename utility::if_<head, Cons, Rest>::type;
			};
			template<size_t N>
			struct bit_filter_impl<N, sequence::Sequence<>>
			{
				using type = sequence::Sequence<>;
			};
		}
		template<class Seq>
		struct bit_filter;
		//[0,1,1,0,1]Å®[1,2,4]
		template<size_t ...N>
		struct bit_filter<Sequence<N...>>:deteil::bit_filter_impl<0, Sequence<N...>>
		{};

	}
}
