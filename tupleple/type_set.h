#pragma once


#include<type_traits>









template<class T, size_t N>
struct Data
	: std::common_type<T>
{};

template<class...T>
struct type_set
	:T...
{};
struct hoge{};

using type = type_set<Data<char, 0>, Data<char, 1>, Data<hoge, 2>>;
static_assert(std::is_base_of<std::common_type<char>, type>::value, "CCCCCCCCCCCCCC");
