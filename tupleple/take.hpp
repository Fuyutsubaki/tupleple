#pragma once 
#include<tuple>
#include"Index.hpp"
#include"to_tuple.hpp"

/*
	auto x=tupleple::take<2>(std::make_tuple(1,2,3,4));
*/
namespace tupleple
{
	namespace type_list
	{
		namespace impl{
			template<size_t N, class Tuple>
			struct take_impl
			{
				using indexs_type = index::make_seq<N>;
				using type = type_list::to_tuple<indexs_type, Tuple>;
			};
		}
		template<size_t N, class Tuple>
		using take = typename impl::take_impl<N, Tuple>::type;
	}
	

	template<size_t N,class Tuple>
	inline auto take(const Tuple&tuple)
		->type_list::take<N, Tuple>
	{
		using Idxs = typename type_list::impl::take_impl<N, Tuple>::indexs_type;
		return to_tuple(Idxs(), tuple);
	}

	namespace adapter
	{
		template<size_t N, class c_ref_Tuple>
		struct take_adapter
		{
			template<class T>
			take_adapter(T&&tuple)
			:base_tuple(std::forward<T>(tuple))
			{}
			c_ref_Tuple&& base_tuple;
		};
		namespace impl
		{
			template<size_t N>
			class take_foward{};
			
			template<class Tuple,size_t N>
			take_adapter<N, Tuple> operator|(Tuple&&tuple, take_foward<N>)
			{
				return take_adapter<N, Tuple>(tuple);
			}
		}
		template<size_t N>
		inline impl::take_foward<N> take(){ return impl::take_foward <N>(); }
	}
	template <size_t N, class c_ref_Tuple>
	class tuple_trait<adapter::take_adapter<N, c_ref_Tuple>>
	{
	public:
		static const size_t size = N;
		template<size_t K>
		struct element
		{
			using type = type_list::at<K, utility::remove_const_ref<c_ref_Tuple>>;
		};
		template<size_t Idx,class T>
		static auto get(T&&tuple)
			->utility::trace_const_ref<T, typename element<Idx>::type>&&
		{
			return at<Idx>(std::forward<utility::trace_const_ref<T, c_ref_Tuple>>(tuple.base_tuple));
		}
	};
}