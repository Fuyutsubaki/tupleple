#ifndef TUPLEPLE_UTILITY_UTILITY_HPP_0523
#define TUPLEPLE_UTILITY_UTILITY_HPP_0523

#include<type_traits>
#include<utility>
#include<tupleple\type_list\List.hpp>

namespace tupleple
{
	namespace utility
	{
		template<bool r, class than_, class else_>
		using cond = std::conditional<r, than_, else_>;


		template<bool r, class than_, class else_>
		using cond_t = typename std::conditional<r, than_, else_>::type;
		template<class T>
		struct remove_cv_ref
		{
			using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
		};

		template<class T>
		using remove_cv_ref_t = typename remove_cv_ref<T>::type;

		struct ExtensionMemberFunction
		{};

		template<class T>
		struct identity
		{
			using type = T;
		};

		template<class From, class To>
		struct trace_const
			:cond_t<std::is_const<From>::value, std::add_const<To>, identity<To >>
		{};

		template<class From, class To>
		using trace_const_t = typename trace_const<From, To>::type;



		template<class From, class To>
		struct trace_volatile
			:cond_t<std::is_volatile<From>::value, std::add_volatile<To>, identity<To >>
		{};

		template<class From, class To>
		using trace_volatile_t = typename trace_volatile<From, To>::type;



		template<class From, class To>
		struct trace_lvalue_reference
			: cond_t<std::is_lvalue_reference<From>::value, std::add_lvalue_reference<To>, identity<To >>
		{};

		template<class From, class To>
		using trace_lvalue_reference_t = typename trace_lvalue_reference<From, To>::type;



		template<class From, class To>
		struct trace_rvalue_reference
			: cond_t<std::is_rvalue_reference<From>::value, std::add_rvalue_reference<To>, identity<To >>
		{};

		template<class From, class To>
		using trace_rvalue_reference_t = typename trace_rvalue_reference<From, To>::type;

		template<class From, class To>
		struct trace_cv
			:trace_volatile<From, trace_const_t<From, To> >
		{};

		template<class From, class To>
		using trace_cv_t = typename trace_cv<From, To >::type;

		template<class From, class To>
		struct trace_reference :
			trace_lvalue_reference<From, trace_rvalue_reference_t<From, To> >
		{};

		template<class From, class To>
		using trace_reference_t = typename trace_reference<From, To >::type;

		template<class From, class To>
		struct trace_cv_ref
		{
			using type = trace_reference_t<
			From, trace_reference_t<
			To, trace_cv_t<
			std::remove_reference_t<From>, std::remove_reference_t<To>
			>> >;
			//(From =const int& , To= volatile char&&)
			//	==>const volatile char&

			//trace_ref<From, trace_ref_t<To, trace_cv_t<std::remove_reference_t<From>, std::remove_reference_t<To>>>>
			//->trace_ref<const int&, trace_ref_t<volatile char&&, trace_cv_t<std::remove_reference_t<const int&>, std::remove_reference_t<volatile char&&>>>>
			//->trace_ref<const int&, trace_ref_t<volatile char&&, trace_cv_t<const int, volatile char>>>
			//->trace_ref<const int&, trace_ref_t<volatile char&&, const volatile char>>
			//->trace_ref<const int&, const volatile char&&>
			//->const volatile char&
		};

		template<class From, class To>
		using trace_cv_ref_t = typename trace_cv_ref<From, To >::type;

		template<class>
		struct Ignore_class
		{
			template<class T>
			Ignore_class(T&&){}
		};


		
		//非型の結果を返す関数のためのラッパ
		//VSでは非型のパラメータパックが正常に動作しないことがある
		template<class T>
		struct expr2Bool
		{
			using type = std::integral_constant<bool, T::value>;
		};

		template<class T>
		struct deriver;
		
		//Listの全てを継承する
		template<class ...T>
		struct deriver<type_list::List<T...>>
			:T...{};
	}
}
template<class Lhs, class Rhs,
	typename std::enable_if<std::is_base_of<tupleple::utility::ExtensionMemberFunction, Rhs>::value>::type* = nullptr>
	typename std::result_of<Rhs(Lhs)>::type operator|(Lhs&&lhs, Rhs&&rhs)
{
		auto r = std::is_lvalue_reference<Lhs>::value;
		return std::forward<Rhs>(rhs)(std::forward<Lhs>(lhs));
}

#endif