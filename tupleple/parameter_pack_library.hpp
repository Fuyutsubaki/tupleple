#pragma once
#include<type_traits>

namespace papali
{
	namespace Impl
	{
		template<size_t ...Idxs>
		struct List{};
		template<size_t N>
		struct make_List
		{
			static const size_t half = N / 2;
			template<size_t...T, size_t ...U>
			static auto trans(List<T...>, List<U...>)
				->List<T..., (T + half)..., U...>;
			using X = typename std::conditional<(N % 2) == 0, List<>, List<N - 1>>::type;

			using type = decltype(trans(typename make_List<half>::type{}, X{}));
		};
		template<>
		struct make_List<0>
		{
			using type = List<>;
		};

		template<size_t N>
		struct make_List_e
		{
			template<size_t ...Idxs>
			static auto trans(List<Idxs...>)
				->std::tuple<std::integral_constant<size_t, Idxs>...>;
			using type = decltype(trans(typename make_List<N>::type{}));
		};

		template<size_t N>
		struct Ignore
		{
			template<class C>
			Ignore(C&&){}
		};

		struct val_at_impl
		{
			template<class T, class...R>
			T&&operator()(T&&a, R&&...)
			{
				return std::forward<T>(a);
			}
		};

		template<class T>
		struct wrap
		{
			using type = T;
		};
	}


	template<class ,class Func>
	class drop_functor{};
	
	template<size_t...Idxs,class Func>
	class drop_functor<Impl::List<Idxs...>,Func>
	{
		Func func_;
	public:
		template<class F>
		drop_functor(F&&f)
			:func_(std::forward<F>(f))
		{}
		template<class ...T>
		auto operator()(Impl::Ignore<Idxs>...,T&&...args)
			->typename std::result_of<Func(T...)>::type
		{
			return func_(std::forward<T>(args)...);
		}
	};

	template<size_t N,class Func>
	drop_functor<typename Impl::make_List<N>::type, Func> make_drop(Func&&func)
	{
		return{ std::forward<Func>(func) };
	}
	
	template<size_t N,class ...T>
	auto value_at(T&&...args)
		-> typename std::result_of<drop_functor<typename Impl::make_List<N>::type, Impl::val_at_impl>(T...)>::type
	{
		return make_drop<N>(Impl::val_at_impl{})(std::forward<T>(args)...);
	}
	template<size_t N,class ...T>
	struct type_at
	{
		using type = decltype(value_at<N>(Impl::wrap<T>{}...));
	};
	template<class N, class >
	struct Tl_at{};

	template<class N, class...T >
	struct Tl_at<N,std::tuple<T...>>
	{
		using R = decltype(value_at<N::value>(Impl::wrap<T>{}...));
		using type =  typename typename std::remove_reference<R>::type::type;
	};

	template<class Idx, class ...T>
	auto value_at_e(T&&...args)
		-> typename std::result_of<drop_functor<typename Impl::make_List<Idx::value>::type, Impl::val_at_impl>(T...)>::type
	{
		return make_drop<Idx::value>(Impl::val_at_impl{})(std::forward<T>(args)...);
	}
	template<class Idx>
	struct value_at_type
	{
		template<class ...T>
		static auto at(T&&...)
			-> typename std::result_of<drop_functor<typename Impl::make_List<Idx::value>::type, Impl::val_at_impl>(T...)>::type
		{
			return make_drop<Idx::value>(Impl::val_at_impl{})(std::forward<T>(args)...);
		}
	};

	template<size_t N,class...T>
	struct take_tuple
	{
		using Tuple = std::tuple<T...>;
		template<class...Idx>
		static auto trans(std::tuple<Idx...>)
			->std::tuple<typename Tl_at<Idx, Tuple>::type ...>;
		using type = decltype(trans(typename Impl::make_List_e<N>::type{}));
	};
	template<class,class Func>
	struct take_functor{};

	template<class...Idxs,class Func>
	struct take_functor<std::tuple<Idxs...>,Func>
	{
		Func func_;
	public:
		template<class F>
		take_functor(F&&func)
			:func_(std::forward<F>(func))
		{}
		template<class...T>
		auto operator()(T&&...args)
			->int//decltype(func_(value_at_e<Idxs>(args...)...))
		{
			return func_(value_at_e<Idxs>(args...)...);
			//return func_(value_at_type<Idxs>::at(std::forward<T>(args)...)...);
		}
		template<class...T>
		auto operator()(T&&...args)const
			->decltype(func_(value_at<Idxs>(args...)...))
		{
			return func_(value_at<Idxs>(args...)...);
		}
	};
	template<size_t N, class Func>
	take_functor<typename Impl::make_List_e<N>::type, Func> make_take(Func&&func)
	{
		return{ std::forward<Func>(func) };
	}
}