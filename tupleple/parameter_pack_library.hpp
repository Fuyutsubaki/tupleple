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
		template<size_t N>
		struct Ignore
		{
			template<class C>
			Ignore(C&&){}
		};
		Func func_;
	public:
		template<class F>
		drop_functor(F&&f)
			:func_(std::forward<F>(f))
		{}
		template<class ...T>
		auto operator()(Ignore<Idxs>...,T&&...args)
			->typename std::result_of<Func(T...)>::type
		{
			return func_(std::forward<T>(args)...);
		}
	};

	template<size_t N,class Func>
	auto make_drop(Func&&func)
		->drop_functor<typename Impl::make_List<N>::type, Func>
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
		using type = decltype(value_at<N>(wrap<T>{}...));
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
	
	template< class>
	struct take_impl{};

	template< class...T>
	struct take_impl<std::tuple<T...>>
	{
		template<class Func,class ...R>
		static auto take(Func&&func, T&&...args, R&&...)
			->typename std::result_of<Func(T...)>::type
		{
			return std::forward<Func>(func)(std::forward<T>(args)...);
		}
	};
	template<class N, class >
	struct Tl_at{};

	template<class N, class...T >
	struct Tl_at<N, std::tuple<T...>>
	{
		using R = decltype(value_at<N::value>(Impl::wrap<T>{}...));
		using type = typename typename std::remove_reference<R>::type::type;
	};
	template<size_t N, class...T>
	struct take_tuple
	{
		
		using Tuple = std::tuple<T...>;
		template<class...Idx>
		static auto trans(std::tuple<Idx...>)
			->std::tuple<typename Tl_at<Idx, Tuple>::type ...>;
		using type = decltype(trans(typename Impl::make_List_e<N>::type{}));
	};
	
	template<size_t N, class Func>
	struct take_functor
	{
		Func func_;
	public:
		template<class F>
		take_functor(F&&func)
			:func_(std::forward<F>(func))
		{}
		template<class ...T>
		auto operator()(T&&...args)
			->decltype(take_impl<typename take_tuple<N, T...>::type>::take(std::declval<Func>(), std::declval<T>()...))
		{
			return take_impl<typename take_tuple<N, T...>::type>::take(func_, std::forward<T>(args)...);
		}
	};


	template<size_t N, class Func>
	take_functor<N, Func> make_take(Func&&func)
	{
		return{ std::forward<Func>(func) };
	}
}