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
		struct remove_cv_ref
		{
			using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
		};

		template<class T>
		using remove_cv_ref_t = typename remove_cv_ref<T>::type;
		
		struct ExtensionMemberFunction
		{};
	}
}
template<class Lhs, class Rhs, 
	typename std::enable_if<std::is_base_of<tupleple::utility::ExtensionMemberFunction, Rhs>::value>::type* =nullptr>
typename std::result_of<Rhs(Lhs)>::type operator|(Lhs&&lhs, Rhs&&rhs)
{
	return std::forward<Rhs>(rhs)(std::forward<Lhs>(lhs));
}
