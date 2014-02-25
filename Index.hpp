#pragma once
#include<tuple>


namespace tupleple
{
	namespace index
	{
		template<size_t N>
		struct Index
		{
			static const size_t value = N;
		};

		template<size_t N>
		class make_N_index
		{
			template<class ...T>
			static auto trans(std::tuple<T...>)
				->std::tuple<T..., Index<N - 1>>;
			using res = typename make_N_index<N - 1>::type;
		public:
			using type = decltype(trans(res()));
		};
		template<>
		struct make_N_index<0>
		{
			using type = std::tuple<>;
		};
	}
}