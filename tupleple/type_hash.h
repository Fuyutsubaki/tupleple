#include<utility>
#include<type_traits>
#include<tupleple\utility\index_tuple.hpp>
#include<typeinfo>
#include<iostream>
namespace tupleple
{
	template<class>struct seq_to_tuple;
	template<size_t...N>
	struct seq_to_tuple<index::Sequence<N...>>
	{
		using type = std::tuple<std::integral_constant<size_t, N>...>;
	};
	template<size_t N>
	using make_index_tuple_t = typename seq_to_tuple<index::make_seq_t<N>>::type;

	template<class...T>
	struct impl :T...{};
	template<class T>
	struct wrap{};

	template<class ...T>
	class type_hash_impl
	{
		using Seq = make_index_tuple_t<sizeof...(T)>;
		template<class...U, class...N>
		static auto trans(std::tuple<U...>&&, std::tuple<N...>const&)
			->impl<std::pair<U, N>...>;
	public:
		using type = decltype(trans(std::declval<std::tuple<wrap<T>...>>(), Seq{}));
	};
	template<class...T>
	struct type_hash
		:type_hash_impl<T...>::type
	{
		template<class K, class V>
		static auto trans(std::pair<K, V>const&)->V;
		template<class U>
		using type = decltype(trans<wrap<U>>(std::declval<type_hash>()));
	};
}

//
//
//
//int main()
//{
//	using namespace tupleple;
//	using Hash = type_hash<void, char, int, int, long, bool, bool, char>;
//	std::cout << Hash::type<void>::value;
//	std::cout << Hash::type<int>::value;
//	std::cout << Hash::type<char>::value;
//	std::cout << Hash::type<long>::value;
//}