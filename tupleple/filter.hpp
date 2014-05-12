#pragma once

#include"Index.hpp"
#include"tuple.hpp"
#include"map.hpp"
#include"utility.hpp"
#include"cat.hpp"

/*
	auto result=tupleple::filter<std::is_integral>(std::make_tuple(42, 3.14, 'A', 1.4f));
*/
namespace tupleple
{
	
	namespace view
	{
		template<class Tuple,template<class>class Pred>
		struct filter_view
		{
			Tuple base;
			friend tuple_trait<view::filter_view< Tuple, Meta>>;
		public:
			filter_view(Tuple&&tuple)
				:base(std::forward<Tuple>(tuple))
			{}
		};
	}
	template<class Tuple, template<class>class Pred>
	class tuple_trait<view::filter_view<Tuple, Pred>>
	{
		using R = index::map_t<Tuple, Pred>;




		static const size_t size = 0xDEADC0DE;
		using index = ;
		template<size_t N>
		struct element
		{
			using type = Tuple;
		};



	};



}