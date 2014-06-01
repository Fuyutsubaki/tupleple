#pragma once

#include"drop.hpp"
#include"ListStyle.hpp"
#include"in.hpp"
#include"cat.hpp"

namespace tupleple
{
	namespace type_list
	{
		template<class list>
		struct unique
		{
			static const size_t N = size<list>::value;
			template<class Idx>
			struct trans
			{
				using mylist = drop_t<Idx::value, list>;
				using head = front_t<mylist>;
				using type = utility::cond_t<
					in<head, tail_t<mylist>>::value
					, List<>
					, List<head>
				>;
			};

			using type = flat_t<map_t<index::make_List_t<N>, trans>>;
		};
		template<class list>
		using unique_t = typename unique<list>::type;
	}













}