#ifndef PARAMETER_PACK_LIBRARY_HPP_140521
#define PARAMETER_PACK_LIBRARY_HPP_140521
#include<type_traits>
#include<tuple>
namespace ppl
{
	namespace deteil
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
	}

	namespace deteil
	{
		template<class, class Func>
		class drop_impl{};

		template<size_t...Idxs, class Func>
		struct drop_impl<deteil::List<Idxs...>, Func>
		{
			template<size_t N>
			struct Ignore
			{
				template<class C>
				Ignore(C&&){}
			};
			template<class ...T>
			static auto drop(Func&&func_,Ignore<Idxs>..., T&&...args)
				->typename std::result_of<Func(T...)>::type
			{
				return func_(std::forward<T>(args)...);
			}
		};
	}
	template<size_t N ,class Func>
	class drop_functor
	{
		using Impl = deteil::drop_impl<typename deteil::make_List<N>::type, Func&>;
		Func func_;
	public:
		template<class F>
		drop_functor(F&&f)
			:func_(std::forward<F>(f))
		{}
		template<class...T>
		auto operator()(T&&...args)
			->decltype(Impl::drop(func_, std::forward<T>(args)...))
		{
			return Impl::drop(func_, std::forward<T>(args)...);
		}
	};

	template<size_t N,class Func>
	auto make_drop(Func&&func)
		->drop_functor<N, Func>
	{
		return{ std::forward<Func>(func) };
	}
	

	namespace deteil
	{
		struct val_at_impl
		{
			template<class T, class...R>
			T&&operator()(T&&a, R&&...)
			{
				return std::forward<T>(a);
			}
		};
	}

	template<size_t N,class ...T>
	auto value_at(T&&...args)
		-> typename std::result_of<drop_functor<N, deteil::val_at_impl>(T...)>::type
	{
		return make_drop<N>(deteil::val_at_impl{})(std::forward<T>(args)...);
	}

	namespace deteil
	{
		template<class T>
		struct wrap
		{
			using type = T;
		};
	}

	template<size_t N,class ...T>
	struct type_at
	{		
		using type = decltype(value_at<N>(deteil::wrap<T>{}...));
	};

	namespace deteil
	{
		template< class C>
		struct take_impl
		{
			static_assert(sizeof(C) &&1, "NOO");
		};

		template< class...T>
		struct take_impl<std::tuple<T...>>
		{
			template<class Func, class ...R>
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
			using R = decltype(value_at<N::value>(deteil::wrap<T>{}...));
			using type = typename typename std::remove_reference<R>::type::type;
		};
		template<size_t N, class...T>
		struct take_tuple
		{
			using Tuple = std::tuple<T...>;
			template<class...Idx>
			static auto trans(std::tuple<Idx...>)
				->std::tuple<typename Tl_at<Idx, Tuple>::type ...>;
			using type = decltype(trans(std::declval<typename deteil::make_List_e<N>::type>()));
		};
	}

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
			->int//decltype(deteil::take_impl<typename deteil::take_tuple<N, T...>::type>::take(std::declval<Func&>(), std::declval<T>()...))
		{
			return deteil::take_impl<typename deteil::take_tuple<N, T...>::type>::take(func_, std::forward<T>(args)...);
		}
	};


	template<size_t N, class Func>
	take_functor<N, Func> make_take(Func&&func)
	{
		return{ std::forward<Func>(func) };
	}
}




#endif