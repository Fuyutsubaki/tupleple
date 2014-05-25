#pragma once
#include"parameter_pack_library.hpp"
#include<tuple>


namespace tupleple
{
	template<class T, class ID>
	struct Data
	{
		template<class U>
		Data(U&&arg)
			:data(std::forward<U>(arg))
		{}
		using data_type = T;
		T data;
	};

	template<class ...T>
	class make_tuple_Elem
	{
		using Seq = index::make_tuple_t<sizeof...(T)>;
		template<class...T, class...N>
		static auto trans(std::tuple<T...>, std::tuple<N...>)
			->std::tuple<Data<T, N>...>;
	public:
		using type = decltype(trans(std::declval<std::tuple<T...>>(), Seq{}));
	};
	template<class>
	struct tuple_impl{};

	template<class ...T>
	struct tuple_impl<std::tuple<T...>>
		:T...
	{
		template<class ...R>
		tuple_impl(R&&...args)
			:T(std::forward<R>(args))...
		{}
		template<size_t N>
		auto get()
			->typename typename utility::type_at<N, T...>::type::data_type&
		{
			return static_cast<utility::type_at_t<N, T...>&>(*this).data;
		}
	};
	template<class ...T>
	struct tuple :tuple_impl<typename make_tuple_Elem<T...>::type>
	{
		using base = tuple_impl<typename make_tuple_Elem<T...>::type>;
		template<class ...R>
		tuple(R&&...args)
			:base(std::forward<R>(args)...)
		{}
	};
}