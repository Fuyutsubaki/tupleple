#pragma once

#include<utility>
#include<type_traits>

template<class...>
struct type_map
{};

template<class...Key, class...Val>
struct type_map<std::pair<Key, Val>...>
	:std::pair<Key, Val>...
{
	struct is_unique
		:std::common_type<Key>...
	{};
	template<class K, class V>
	static auto trans(std::pair<K, V>const&, is_unique = is_unique{})->V;
	template<class T>
	using type = decltype(trans<T>(std::declval<type_map>()));
};


/*
struct R{};
struct G{};
struct B{};
using Map = type_map<
	std::pair<R, B>
	, std::pair<G, R>
	, std::pair<B, G>
>;

using Color = Map::type<R>;
static_assert(std::is_same<Color, B>::value, "F**K");

*/