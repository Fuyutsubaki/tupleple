#pragma once
#include"Index.hpp"
#include"map.hpp"
#include"tuple.hpp"
namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			template<size_t N, class T>
			class replicicate_impl
			{
				template<class>
				struct trans{ using type = T; };
			public:
				using index_type = index::make_tuple<N>;
				using type = map<trans, index_type>;
			};
		}
		template<size_t N, class T>
		using replicicate = typename impl::replicicate_impl<N, T>::type;
	}

	namespace deteil
	{
		template<class,class T>
		inline const T& do_nothing(const T&x)
		{
			return x;
		}
		template<size_t N, class T,class ...Idx>
		inline type_list::replicicate<N, T> replicicate_impl(const T&x,std::tuple<Idx...>)
		{
			return type_list::replicicate<N, T>(do_nothing<Idx>(x)...);
		}
	}
	template<size_t N, class T>
	type_list::replicicate<N, T> replicicate(const T&x)
	{
		return deteil::replicicate_impl<N>(x, index::make_tuple<N>());
	}
}