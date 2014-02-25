#pragma once 
#include"utility.hpp"
#include"tuple.hpp"
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
				using seq = typename make_N_Sequence_impl<N - 1>::type;
				template<size_t ...N>
				static auto Inc(Sequence<N...>)
					->Sequence<0, (N + 1)...>;
			public:
				using type = decltype(Inc(seq()));
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
			template<size_t...N,class Tuple>
			struct to_tuple<Sequence<N...>,Tuple>
			{
				using type = std::tuple < typename tupleple::type_list::at<N, Tuple>::type...>;
			};
		}

		template<size_t ...N, class Tuple>
		inline auto to_tuple(Sequence<N...>, const Tuple&tuple)
			->typename type_list::to_tuple<Sequence<N...>, Tuple>::type
		{
			using tuple_type = typename  type_list::to_tuple<Sequence<N...>, Tuple>::type;
			return tuple_type(tupleple::at<N>(tuple)...);
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
		namespace type_list
		{
			template<class Seq, template<size_t X>class Trans>
			class map;

			template<size_t...N, template<size_t X>class Trans>
			struct map<Sequence<N...>, Trans>
			{
				using type = Sequence<Trans<N>::value...>;
			};

			template<class Seq, template<size_t X>class Trans>
			class map_to_tuple;

			template<size_t...N, template<size_t X>class Trans>
			struct map_to_tuple<Sequence<N...>, Trans>
			{
				using type = std::tuple<typename Trans<N>::type...>;
			};
		}
		

	}
}
