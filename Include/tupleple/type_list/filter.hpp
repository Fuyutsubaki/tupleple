#pragma once

#include"map.hpp"
#include"cat.hpp"
#include"List.hpp"

namespace tupleple
{
	namespace type_list
	{
		template<class tList,template<class>class Pred>
		struct filter_if
		{
			template<class T>
			struct Trans
			{
				using type = utility::cond_t<Pred<T>::value, List<T>, List<> >;
			};
			using type= flat_t<map_t<tList,Trans>>;
		};

		template<class tList, class T>
		struct filter
		{
			template<class U>
			struct trans
				:std::is_same<U, T>
			{};
			using type = filter_if<tList, trans>;
		};


		template<class tList, template<class>class Pred>
		using filter_if_t = typename filter_if<tList, Pred>::type;
		template<class tList, class T>
		using filter_t = typename filter<tList, T>::type;
	}
	
}