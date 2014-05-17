#pragma once
#include"Index.hpp"
#include"parameter_pack_at.hpp"
namespace tupleple
{
	namespace ln_tuple
	{
		template<size_t N>
		using make_take_t = index::make_seq_t<N / 2>;
		template<size_t N>
		struct make_drop
		{
			template<size_t...Idx>
			static auto trans(index::Sequence<Idx...>)
				->index::Sequence<(Idx + N / 2)...>;
		public:
			using type = decltype(trans(index::make_seq_t<(N + 1) / 2>{}));
		};
		template<size_t N>
		using make_drop_t = typename make_drop<N>::type;
		template<size_t N>
		struct wrap_val_at
		{
			template<class...T>
			auto at(T&&...args)
				->decltype(utility::value_at<N>(std::forward<T>(args)...))
			{
				return utility::value_at<N>(std::forward<T>(args)...);
			}
		};


		template<class...>
		struct tuple_struct{};

		template<size_t...lhs, size_t...rhs, class...T>
		struct tuple_struct
			<index::Sequence<lhs...>, index::Sequence<rhs...>, T...>
			: tuple_struct<make_take_t<sizeof...(lhs)>, make_drop_t<sizeof...(lhs)>, utility::type_at_t<lhs, T...>...>
			, tuple_struct<make_take_t<sizeof...(rhs)>, make_drop_t<sizeof...(rhs)>, utility::type_at_t<rhs, T...>...>
		{
			using L = tuple_struct<make_take_t<sizeof...(lhs)>, make_drop_t<sizeof...(lhs)>, utility::type_at_t<lhs, T...>...>;
			using R = tuple_struct<make_take_t<sizeof...(rhs)>, make_drop_t<sizeof...(rhs)>, utility::type_at_t<rhs, T...>...>;

			template<class...U>
			tuple_struct(U&&...args)
				:L(wrap_val_at<lhs>::at(std::forward<U>(args)...)...)
				, R(wrap_val_at<rhs>::at(std::forward<U>(args)...)...)
			{}
			
			using L::get;
			using R::get;
		};
		template< size_t rhs, class T>
		class tuple_struct<index::Sequence<>, index::Sequence<rhs>,T>
		{
			using type = typename T::type;
			type data_;
		public:
			template<class T>
			tuple_struct(T&&x)
				:data_(std::forward<T>(x))
			{}
			type decl_type(std::integral_constant<size_t, T::value>)const;
			type& get(std::integral_constant<size_t, T::value>)
			{
				return data_;
			}
			const type& get(std::integral_constant<size_t, T::value>)const
			{
				return data_;
			}
		};
		template<class T, class val>
		struct wrap
		{
			using type = T;
			static const size_t value = val::value;
		};
		template<class...R>
		struct tuple_base
		{
			static const size_t N = sizeof...(R);
			using Seq = index::make_seq_t<N>;
			template<class...Idx>
			static auto trans(std::tuple<Idx...>)
				->tuple_struct<
				make_take_t<N>,
				make_drop_t<N>,
				wrap<R, std::integral_constant<size_t,0>> ...>;

			using type = decltype(trans(index::make_tuple_t<N>{}));
		};

		template<class...T>
		struct tuple :tuple_base<T...>::type
		{
			template<class...R>
			tuple(R&&...args)
				:typename tuple_base<T...>::type(std::forward<R>(args)...)
			{}
		};
	}




}