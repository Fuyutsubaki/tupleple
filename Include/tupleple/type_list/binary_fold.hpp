#pragma once
#include"drop.hpp"
#include"take.hpp"
#include"ListStyle.hpp"



namespace tupleple
{
	namespace type_list
	{
		template<class List, template<class...>class Binary_func,class Default, class = void>
		struct binary_fold
		{
			static const size_t N = size<List>::value;
			using taked = take_t<N / 2, List>;
			using L = typename binary_fold<taked, Binary_func, Default>::type;
			using droped = typename drop<N / 2, List>::type;
			using R = typename binary_fold<droped, Binary_func, Default>::type;
		public:
			using type = typename Binary_func<L, R>::type;
		};
		template<class List, template<class...>class Binary_func, class Default>
		struct binary_fold<List, Binary_func, Default, typename std::enable_if<size<List>::value == 1>::type>
		{
			using type = front_t<List>;
		};
		template<class List, template<class...>class Binary_func, class Default>
		struct binary_fold<List, Binary_func, Default, typename std::enable_if<size<List>::value == 0>::type>
		{
			using type = Default;
		};

		template<class List, template<class...>class Binary_func, class Default>
		using binary_fold_t = typename binary_fold<List, Binary_func, Default>::type;



		template<class List, template<class...>class Binary_struct, class = void>
		class binary_fold_struct
		{
			static const size_t N = size<List>::value;
			using L = typename binary_fold_struct<take_t<N / 2, List>, Binary_struct>::type;
			using R = typename binary_fold_struct<drop_t<N / 2, List>, Binary_struct>::type;
		public:
			using type = Binary_struct<L, R>;
		};
		template<class List, template<class...>class Binary_func>
		struct binary_fold_struct<List, Binary_func, typename std::enable_if<size<List>::value == 1>::type>
		{
			using type = front_t<List>;
		};
		
		template<class List, template<class...>class Binary_func>
		using binary_fold_struct_t = typename binary_fold_struct<List, Binary_func>::type;
	}
}