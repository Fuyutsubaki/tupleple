#pragma once

#include<array>
#include<tupleple\type_list\filter.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\STD_tuple_traits.hpp>
#include<tupleple\apply.hpp>
#include<tupleple\type_list\unique.hpp>
#include<type_traits>
namespace tupleple
{
	namespace deteil
	{
		template<class...T>
		struct make_strage : std::aligned_union<0, T...>{};
	}
	template<class...Types>
	struct variant
	{
		using list = type_list::unique_t<type_list::List<Types...>>;
		
		using strage_type = type_list::apply_t<list, deteil::make_strage>;
		static const std::size_t type_size = type_list::size<list>::value;
		
		template<std::size_t I>
		using data_type = type_list::at<I, list>;

		strage_type strage_;
		std::size_t which_;

		template<class Idx, class T>
		variant(Idx, T&&x)
			:which_(Idx::value)
		{
			data<Idx::value>() = x;
		}

		template<std::size_t I>
		typename data_type<I>::type& data()
		{
			return *reinterpret_cast<typename data_type<I>::type*>(&strage_);
		}

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
		struct variant_apply<Result_type, type_list::List<H, N...>>
		{
			using result_type = Result_type;
			static const std::size_t index = typename type_list::front< type_list::List<H, N...>>::type::value;
			using Rest = variant_apply<result_type, type_list::tail_t<type_list::List<H, N...>>>;

			template<std::size_t Which, class Func, class Arg>
			struct tansmat
			{
				static result_type func(Func&&func, Arg &&x)
				{
					static const std::size_t size = type_list::size<utility::remove_cv_ref_t<Arg>>::value;
					return Implt(index::make_seq_t<size>{}, std::forward<Func>(func), std::forward<Arg>(x));
				}
				template<std::size_t>
				struct trans
				{
					template<class T>static T&&apply(T&&x)
					{
						return std::forward<T>(x);
					}
				};
				template<>
				struct trans<index>
				{
					template<class T>static auto apply(T&&x)
						->decltype(x.template data<Which>())
					{
						return x.template data<Which>();
					}
				};

				template<std::size_t...Idx>
				static result_type Implt(index::Sequence<Idx...>, Func&&func, Arg &&x)
				{
					return Rest::apply(std::forward<Func>(func), std::forward_as_tuple(trans<Idx>::apply(x | at<Idx>())...));
				}
			};

			template<class Func, class Arg>
			static result_type apply(Func&&func, Arg&&arg)
			{
				using type = utility::remove_cv_ref_t<type_list::at_t<index, utility::remove_cv_ref_t<Arg>>>;
				return Impl(index::make_seq_t<type::type_size>{}, 
					std::forward<Func>(func),(arg | at<index>()).which(), std::forward<Arg>(arg));
			}

			template<class Func,class Arg,std::size_t...Idxs>
			static result_type Impl(index::Sequence<Idxs...>, Func&& func, int which, Arg&&arg)
			{
				using f = result_type(*)(Func&&, Arg&&);
				static const std::array<f, sizeof...(Idxs)> list = { tansmat<Idxs, Func, Arg>::func... };
				return list[which](std::forward<Func>(func), std::forward<Arg>(arg));
			}
		};
		template<class Result_type>
		struct variant_apply<Result_type, type_list::List<>>
		{
			template<class Func,class Arg>
			static Result_type apply(Func&&func, Arg&&arg)
			{
				return tupleple::apply(std::forward<Arg>(arg), std::forward<Func>(func));
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
	template<class result_type,class Func,class...T>
	result_type variant_apply(Func&&func, T&&...args)
	{
		using list = typename deteil::filter_is_variantIdx<type_list::List<utility::remove_cv_ref_t<T>...>>::type;
		return deteil::variant_apply<result_type, list>::apply(std::forward<Func>(func), std::forward_as_tuple(std::forward<T>(args)...));
	}
}
