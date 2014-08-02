#pragma once

#include<array>
#include<tupleple\type_list\filter.hpp>
#include<tupleple\index_tuple\index_TypeList.hpp>
#include<tupleple\STD_tuple_traits.hpp>
#include<tupleple\apply.hpp>
#include<tupleple\type_list\unique.hpp>
#include"type_map.h"
#include<type_traits>
#include<new>

namespace tupleple
{
template<class...Types>
struct variant;

namespace deteil
{
	template<class T>
	struct is_variant
		:std::false_type
	{};
	template<class ...T>
	struct is_variant<variant<T...>>
		:std::true_type
	{};

	template<std::size_t Which, class Func, class Arg, class result_type, std::size_t index, class Next>
	struct make_func
	{
		static result_type func(Func&&func, Arg &&x)
		{
			static const std::size_t size = type_list::size<utility::remove_cv_ref_t<Arg>>::value;
			return Impl(index::make_seq_t<size>{}, std::forward<Func>(func), std::forward<Arg>(x));
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
			->decltype(std::declval<T>().template data<Which>())
			{
				return std::forward<T>(x).template data<Which>();
			}
		};

		template<std::size_t...Idx>
		static result_type Impl(index::Sequence<Idx...>, Func&&func, Arg &&x)
		{
			return Next::apply(std::forward<Func>(func), std::forward_as_tuple(trans<Idx>::apply(std::get<Idx>(x))...));
		}
	};

	//戻り値の型,variantの位置
	template<class Result_type, class variant_idxs>struct variant_apply;
	template<class result_type, class H, class ...N>
	struct variant_apply<result_type, type_list::List<H, N...>>
	{
		static const std::size_t index = typename type_list::front< type_list::List<H, N...>>::type::value;
			
		template<class Func, class Arg>
		static result_type apply(Func&&func, Arg&&arg)
		{
			using type = utility::remove_cv_ref_t<type_list::at_t<index, utility::remove_cv_ref_t<Arg>>>;
			return Impl(index::make_seq_t<type::type_size>{}, 
				std::forward<Func>(func),(arg | at<index>()).which(), std::forward<Arg>(arg));
		}
		using Rest = variant_apply<result_type, type_list::tail_t<type_list::List<H, N...>>>;
		template<class Func,class Arg,std::size_t...Idxs>
		static result_type Impl(index::Sequence<Idxs...>, Func&& func, int which, Arg&&arg)
		{
			using f = result_type(*)(Func&&, Arg&&);
			const std::array<f, sizeof...(Idxs)> list = { make_func<Idxs, Func, Arg, result_type, index, Rest>::func... };
			return list[which](std::forward<Func>(func), std::forward<Arg>(arg));
		}
	};
	template<class result_type>
	struct variant_apply<result_type, type_list::List<>>
	{
		template<class Func,class Arg>
		static result_type apply(Func&&func, Arg&&arg)
		{
			//tupleを関数に適用している
			return tupleple::apply(std::forward<Arg>(arg), std::forward<Func>(func));
		}
	};

	//variantの位置を調べる
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



template<class...Types>
struct variant
{
	//重複要素を削除したTypeList
	using list = type_list::unique_t<type_list::List<Types...>>;

	//ストレージ型
	template<class...T>
	struct make_strage : std::aligned_union<0, T...>{};
	using strage_type = type_list::apply_t<list, make_strage>;

	//要素数
	static const std::size_t type_size = type_list::size<list>::value;

	//type → which
	using type_to_which =
		type_list::apply_struct_t<typename type_list::zip_struct<std::pair, list, index::make_List_t<type_size>>::type, type_map>;

	//which → type
	template<std::size_t I>
	using data_type = type_list::at<I, list>;

	//ストレージとwhich
	strage_type strage_;
	std::size_t which_;

	//whichのデータ型を返す
	template<std::size_t Which>
	typename data_type<Which>::type& data()
	{
		return *reinterpret_cast<typename data_type<Which>::type*>(&strage_);
	}
	template<std::size_t Which>
	const typename data_type<Which>::type& data()const
	{
		return *reinterpret_cast<const typename data_type<Which>::type*>(&strage_);
	}

	//現在保持してる型のwhich
	std::size_t which()const
	{
		return which_;
	}


	template<class T, class Idx = type_to_which::type<utility::remove_cv_ref_t<T>>>
	explicit variant(T&&x)
		:which_(Idx::value)
	{
		new(&data<Idx::value>())T(std::forward<T>(x));
	}

	struct Destroy
	{
		template<class T>
		void operator()(T&x)
		{
			x.~T();
		}
	};
	~variant()
	{
		variant_apply<void>(Destroy{}, *this);
	}
};
}
