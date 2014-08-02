#pragma once
#include<type_traits>


namespace tupleple
{
	namespace mpl
	{
		template<bool r>
		struct Bool_
			:std::conditional<r, std::true_type, std::false_type>
		{};
		
		template<class T>
		struct identity
		{
			using type = T;
		};
		template<class T>
		struct unbox
		{
			using type = typename T::type;
		};
		template<class T>
		using unbox_t = typename unbox<T>::type;
		template<class R, class T, class F>
		struct if_
			:std::conditional<unbox_t<R>::value, T, F>::type
		{};
	}
	namespace index
	{
		template<std::size_t ...Idxs>
		struct Sequence
		{};
		template<std::size_t N>
		struct make_sequence;
		template<std::size_t N>
		using make_sequence_t = typename make_sequence<N>::type;
		template<std::size_t N>
		struct make_sequence
		{
			template<std::size_t...Idxs>
			static auto trans(Sequence<Idxs...>, ...)
				->Sequence<Idxs..., (N / 2 + Idxs)...>;
			template<std::size_t...Idxs>
			static auto trans(Sequence<Idxs...>, std::true_type)
				->Sequence<Idxs..., (N / 2 + Idxs)..., N>;
		public:
			using type = decltype(trans(make_sequence_t<N / 2>{}, mpl::unbox_t<mpl::Bool_<N % 2>>{}));
		};
		template<>
		struct make_sequence<0>
		{
			using type = Sequence<>;
		};
	}
	namespace mpl
	{

		template<typename...T>
		struct List
		{
			using type = List;
		};
		
		template<std::size_t N, class list>
		class at
		{
			template<std::size_t>
			struct do_nothing
			{
				do_nothing(...);
			};
			template<class T, class IdxSeq>struct impl;
			template<class...T, std::size_t ...Idxs>
			struct impl<List<T...>, index::Sequence<Idxs...>>
			{
				template<class U>
				static U trans(do_nothing<Idxs>..., U, ...);
				using type = decltype(trans(id<T>{}...));
			};
		public:
			using type = unbox_t<unbox_t<impl<unbox_t<list>, typename index::make_sequence<N>::type>>>;
		};

		template<class list>
		struct list_size
		{
			template<class...T>
			static std::integral_constant<std::size_t, (sizeof...(T))> impl(List<T...>);
			using type = decltype(impl(unbox_t<list>{}));
		};

		template<class list, class Func>
		class map
		{
			template<class T>
			struct F
				:Func::type::template apply<T>
			{};

			template<class...T>
			static auto trans(List<T...>)
				->List<unbox_t<F<T>>...>;
			
		public:
			using type = decltype(trans(unbox_t<list>{}));
		};

		template<class list, class Func>
		struct binary_fold1
		{
			template<std::size_t Begin, std::size_t Len>
			struct impl
				//:Func::apply<unbox_t<impl<Begin, Len / 2>>, unbox_t<impl<Begin + Len / 2, Len - Len / 2>>>
			{};
			template<std::size_t Begin>
			struct impl<Begin, 1>
				:at<Begin, list>
			{};
		public:
			//using type = unbox_t<impl<0, 0>>;
		};
	}
}