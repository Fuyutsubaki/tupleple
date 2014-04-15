#pragma once
#include<type_traits>
#include<utility>
namespace tupleple
{
	namespace utility
	{
		template<bool r, class than_, class else_>
		using cond_t = typename std::conditional<r, than_, else_>::type;
		template<class T>
		struct remove_const_ref
		{
			using type = typename std::remove_const<typename std::remove_reference<T>::type>::type;
		};

		template<class T>
		using remove_const_ref_t = typename remove_const_ref<T>::type;
		
		template<class From, class To>
		class trace_const_ref
		{
			using c = cond_t<std::is_const<typename std::remove_reference<From>::type>::value, const To, To >;
			using ref = cond_t <
				std::is_rvalue_reference<From>::value,
				c&&,
				cond_t < std::is_lvalue_reference<From>::value, c&, c >> ;
		public:
			using type = ref;
		};
		template<class From, class To>
		using trace_const_ref_t = typename trace_const_ref<From, To>::type;

		
		template<class Class, class Member>
		auto foward_member_ref(typename std::remove_reference<Member>::type&mem)
			->std::enable_if_t<std::is_lvalue_reference<Class>::value,Member&>
		{
			return mem;
		}
		template<class Class, class Member>
		auto foward_member_ref(typename std::remove_reference<Member>::type&mem)
			->std::enable_if_t<!std::is_lvalue_reference<Class>::value, Member&&>
		{
			return std::forward<Member>(mem);
		}

		template<bool,class T>
		struct lazy_enable_if
		{
			using type = typename T::type;
		};
		template<class T>
		struct lazy_enable_if<false,T>
		{};

		template<bool r,class T>
		using lazy_enable_if_t = typename lazy_enable_if<r, T>::type;

		struct ExtensionMemberFunction
		{};

		

	}
}
template<class Lhs, class Rhs>
auto operator|(Lhs&&lhs, Rhs&&rhs)
->std::enable_if_t<
std::is_base_of<tupleple::utility::ExtensionMemberFunction, Rhs>::value
,  decltype(std::declval<Rhs>()(std::declval<Lhs>()))
>
{
	return std::forward<Rhs>(rhs)(std::forward<Lhs>(lhs));
}