#ifndef TUPLEPLE_UTILITY_BASE_VIEW_HPP
#define TUPLEPLE_UTILITY_BASE_VIEW_HPP
#include<type_traits>
#include<tupleple\utility\mem_forward.hpp>
#include<tupleple\utility\utility.hpp>
#include<tupleple\tuple_traits.hpp>
#include<tupleple\STD_tuple_traits.hpp>
namespace tupleple
{
	namespace utility
	{
		


		//tuple_trait helper
		template<class T>
		struct view_tuple_trait_helper
		{
			using helper = view_tuple_trait_helper<T>;
			using base_type = typename T::base_type;

			using base_simple_type = utility::remove_cv_ref_t<base_type>;
			
			static const size_t base_size = type_list::size<base_simple_type>::value;
			//at
			template<size_t Idx>
			using base_element = type_list::at<Idx, base_simple_type>;
			template<size_t Idx>
			using base_element_t = type_list::at_t<Idx, base_simple_type>;

			
			//base ‚Ì forward
			template<class T>
			struct result_base_forward
			{
				using type = decltype(utility::mem_forward<base_type>(std::declval<T>().base));
			};

			template<class T>
			using result_base_forward_t = typename result_base_forward<T>::type;
			
			template<class T>
			static auto base_forward(typename std::remove_reference<T>::type&x)
				->result_base_forward_t<T>
			{
				return utility::mem_forward<base_type>(std::forward<T>(x).base);
			}
			
			//result_of
			template<size_t Idx, class T>
			using base_result_type_of
				= result_of <Idx, result_base_forward_t<T>>;
			template<size_t Idx, class T>
			using base_result_type_of_t
				= result_of_t <Idx, result_base_forward_t<T>>;

		};

		namespace deteil
		{
			class dummy{};
		}

		template<class Crtp, class Tuple, class Super = deteil::dummy>
		class base_view :protected Super
		{
			friend tuple_trait<Crtp>;
			friend view_tuple_trait_helper<Crtp>;
		protected:
			template<class T, class...R>
			base_view(T&&x, R&&...args)
				:Super(std::forward<R>(args)...)
				, base(std::forward<T>(x))
			{}
			using base_type = Tuple;
			base_type base;
			using isuper = base_view;
		};
	}
}
#endif