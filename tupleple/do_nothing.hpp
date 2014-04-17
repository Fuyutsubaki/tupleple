#pragma once
#include"tuple.hpp"

namespace tupleple
{
	
	namespace hogehoge
	{
		
		template<class tag, class ...Tuples>
		class basic_hoge
		{
			std::tuple<Tuples...> base;
		public:
			friend tuple_trait<basic_hoge>;
			template<class ...R>
			basic_hoge(R&&...args)
				: base(std::forward<R>(args)...)
			{}
		};
		struct do_nothing_tag{};
		template<class Tuple>
		using do_nothing = basic_hoge<do_nothing_tag, Tuple>;

		template<class Tuple>
		struct tuple_trait<do_nothing<Tuple>>
		{
			using base = utility::remove_const_ref_t<Tuple>;
			static const size_t value = type_list::size<base>::value;

			template<size_t N>
			struct element
			{
				using type = type_list::at_t<N,base>;
			};
			template<class T>
			static void get(T&&x)
			{
				//
			}
		};
	}

}