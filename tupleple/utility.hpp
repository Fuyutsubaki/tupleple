#pragma once
#include<tuple>

namespace tupleple
{
	namespace utility
	{
		template<bool r, class than_, class else_>
		using cond = typename std::conditional<r, than_, else_>::type;

		template<class T>
		using remove_const_ref = typename std::remove_const<typename std::remove_reference<T>::type>::type;
		namespace impl{
			template<class From, class To>
			class trace_const_ref_impl
			{
				using c = cond<std::is_const<typename std::remove_reference<From>::type>::value, const To, To >;
				using ref = cond <
					std::is_rvalue_reference<From>::value,
					c&&,
					cond < std::is_lvalue_reference<From>::value, c&, c >> ;

			public:
				using type = ref;
			};
		}
		template<class From, class To>
		using trace_const_ref = typename impl::trace_const_ref_impl<From, To>::type;


		template<class Functor>
		struct carry_variadic_result_of
		{
			template<class...R>
			using type = typename std::result_of<Functor(R...)>::type;
		};
		template<class Functor>
		struct carry_1_result_of
		{
			template<class T0>
			using type = typename std::result_of<Functor(T0)>::type;
		};
		template<class Functor>
		struct carry_2_result_of
		{
			template<class T0, class T1>
			using type = typename std::result_of<Functor(T0, T1)>::type;
		};
	}
}