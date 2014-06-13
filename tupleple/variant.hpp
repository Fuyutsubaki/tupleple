#pragma once

#include<array>
#include<tupleple\type_list\filter.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\STD_tuple_traits.hpp>

namespace tupleple
{
	template<class...Types>
	struct variant
	{
		variant(std::size_t N)
		:which_(N)
		{}
		std::size_t which_;
		static const std::size_t type_size = sizeof...(Types);
		
		std::size_t which()
		{
			return which_;
		}
	};
	
	template<class T>
	struct is_variant
		:std::false_type
	{};
	template<class ...T>
	struct is_variant<variant<T...>>
		:std::true_type
	{};

	namespace deteil
	{
		template<class Result_type, class>struct variant_apply;
		template<class Result_type, class H,class ...N>
		struct variant_apply<Result_type, type_list::List<H,N...>>
		{
			using result_type = Result_type;
			static const std::size_t index = typename type_list::front< type_list::List<H, N...>>::type::value;
			using Rest = variant_apply<result_type, type_list::tail_t<type_list::List<H, N...>>>;

			template<std::size_t N, class Arg>
			struct tansmat
			{
				static result_type func(Arg &&x)
				{
					static const std::size_t size = type_list::size<utility::remove_cv_ref_t<Arg>>::value;

					return Implt(index::make_seq_t<size>{}, std::forward<Arg>(x));
					std::cout << "which=" << N << '\t' << "idx=" << index << std::endl;
				}
				template<std::size_t I>
				struct trans
				{
					template<class T>static T&&apply(T&&x)
					{
						return std::forward<T>(x);
					}
				};
				template<>
				struct trans<N>
				{
					template<class T>static T&&apply(T&&x)
					{
						std::cout << "ƒJƒb!!";
						return std::forward<T>(x);
					}
				};

				template<std::size_t...Idx>
				static result_type Implt(index::Sequence<Idx...>, Arg &&x)
				{
					return Rest::apply(std::forward_as_tuple(trans<Idx>::apply(x | at<Idx>())...));
				}
			};

			template<class Arg>
			static result_type apply(Arg&&arg)
			{
				using type = utility::remove_cv_ref_t<type_list::at_t<index, utility::remove_cv_ref_t< Arg>>>;
				return Impl(index::make_seq_t<type::type_size>{}, (arg | at<index>()).which(), std::forward<Arg>(arg));
			}

			template<class Arg,std::size_t...Idxs>
			static result_type Impl(index::Sequence<Idxs...>,int which, Arg&&arg)
			{
				using f = result_type(*)(Arg&&);
				static const std::array<f, sizeof...(Idxs)> list = { tansmat<Idxs, Arg>::func... };
				return list[which](std::forward<Arg>(arg));
			}
		};
		template<class Result_type>
		struct variant_apply<Result_type, type_list::List<>>
		{
			using result_type = Result_type;
			template<class Arg>
			static result_type apply(Arg&&arg)
			{
				return ;
			}
		};
		template<class T>
		struct filter_is_variantIdx
		{
			using list = index::make_List_t<type_list::size<T>::value>;
			template<class Idx>
			struct Impl
				:is_variant<type_list::at_t<Idx::value, T>>
			{};
			using type = type_list::filter_if_t<list, Impl>;
		};
	}
	template<class result_type,class...T>
	result_type variant_apply(T&&...args)
	{
		using list = typename deteil::filter_is_variantIdx<type_list::List<utility::remove_cv_ref_t<T>...>>::type;
		deteil::variant_apply<result_type, list>::apply(std::forward_as_tuple(std::forward<T>(args)...));
	}



}
