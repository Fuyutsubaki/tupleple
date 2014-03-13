#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"
#include"replicate.hpp"
#include"invoke.hpp"
namespace tupleple
{
	namespace type_list
	{
		namespace impl
		{
			template<class MetaTuple>
			class cat_impl
			{
				using meta_tuple = MetaTuple;
				using seq = index::make_tuple<size<meta_tuple>::value>;

				template<class Idx>
				class trans1
				{
					using tuple = at<Idx::value, meta_tuple>;
					using type = repricate<size<tuple>::value, Idx>;
				};
				template<class Idx>
				class trans2
				{
					using tuple = at<Idx::value, meta_tuple>;
					using type = index::make_tuple<size<tuple>::value>;
				};

				template<class...Tuple>
				struct cat_idx
				{
					using type = decltype(std::tuple_cat(std::declval<Tuple>()...));
				};
				template<size_t ...X, size_t ...Y>
				static auto trans(index::Sequence<X...>, index::Sequence<Y...>)
					->std::tuple<at<Y, at<X, meta_tuple>>...>;
			public:
				using seq_type1 = index::tuple_to_seq<invoke<cat_idx, map<trans1, seq>>>;//ex:)111223333
				using seq_type2 = index::tuple_to_seq<invoke<cat_idx, map<trans2, seq>>>;//ex:)123121234
				
				using type = decltype(trans(seq_type1(), seq_type2()));
			};
			/*template<class ...Tuple>
			struct cat
			{
				using meta_tuple = std::tuple<Tuple...>;
				using seq = index::make_N_index<size<meta_tuple>::value>;
				template<class Idx>
				class trans
				{
					using tuple = at<Idx::value, meta_tuple>;
					using seq = index::make_N_index<size<tuple>::value>;
					template<class local_idx>
					struct trans2
					{
						using type = std::tuple<Idx, local_idx>;
					};
				public:
					using type = map<trans2,seq>;
				};

				using index_type = map<trans, seq>;
				using type = typename decltype(std::tuple_cat(std::declval<Tuple>()...));
			};*/
		}
		template<class MetaTuple>
		using cat = typename impl::cat_impl<MetaTuple>::type;
	}
	namespace deteil
	{
		template<class Meta_Tuple,size_t...A,size_t...B>
		type_list::cat<Meta_Tuple> cat_impl(const Meta_Tuple&meta_tuple, index::Sequence<A...>,index::Sequence<B...>)
		{
			return type_list::cat<Meta_Tuple>(at<B>(at<A>(meta_tuple))...);
		}
	}
	template<class Tuple>
	typename type_list::cat<Tuple> cat(const Tuple&tuple)
	{
		return deteil::cat_impl(tuple, typename type_list::impl::cat_impl<Tuple>::seq_type1(), typename type_list::impl::cat_impl<Tuple>::seq_type2());
	}
}