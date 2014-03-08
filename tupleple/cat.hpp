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
		namespace flex
		{
			template<class MetaTuple>
			class cat
			{
				using meta_tuple = MetaTuple;
				using seq = index::make_N_index<size<meta_tuple>::value>;
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
					using type = index::make_N_index<size<tuple>::value>;
				};

				template<class...Tuple>
				struct cat_idx
				{
					using type = decltype(std::tuple_cat(std::declval<Tuple>()...));
				};
				template<class ...Idx0, class ...Idx1>
				static auto trans(std::tuple<Idx0...>, std::tuple<Idx1...>)
					->std::tuple<index::at_helper<Idx1, index::at_helper<Idx0, meta_tuple>>...>;
			public:
				using index_type1 = invoke<cat_idx, map<trans1, seq>>;//ex:)111223333
				using index_type2 = invoke<cat_idx, map<trans2, seq>>;//ex:)123121234
				
				using type = decltype(trans(index_type1(), index_type2()));
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
		using cat = typename flex::cat<MetaTuple>::type;
	}
	namespace deteil
	{
		template<class Meta_Tuple,class...Idx0,class...Idx1>
		type_list::cat<Meta_Tuple> cat_impl(const Meta_Tuple&meta_tuple, std::tuple<Idx0...>, std::tuple<Idx1...>)
		{
			return type_list::cat<Meta_Tuple>(at<Idx1::value>(at<Idx0::value>(meta_tuple))...);
		}
	}
	template<class Tuple>
	typename type_list::flex::cat<Tuple>::type cat(const Tuple&tuple)
	{
		return deteil::cat_impl(tuple, typename type_list::flex::cat<Tuple>::index_type1(), typename type_list::flex::cat<Tuple>::index_type2());
	}
}