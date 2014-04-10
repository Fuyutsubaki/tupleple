#pragma once
#include<tuple>
#include"tuple.hpp"
#include"Index.hpp"
#include<type_traits>
/*
using tuple = std::tuple<char, int, void*>;
using r = tupleple::type_list::map<std::add_pointer, tuple>;
*/

/*
struct Func
{
	template<class T>
	std::pair<T, size_t> operator()(T x)const
	{
		return std::pair<T, size_t>(x, sizeof(x));
	}
};

int main()
{
	using namespace tupleple;
	auto r = std::make_tuple('X', 3) | view::map(Func()) | at<0>();
}
*/
//element‚ÌÀ‘•‚ªÅ‘åŒö–ñ”Š´

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class T>class Transform>
		class map
		{
			using seq = index::make_tuple_size_seq_t<Tuple>;

			template<size_t ...N>
			static auto trans(index::Sequence<N...>)
				->std::tuple<typename Transform<at_t<N, Tuple>>::type...>;
		public:
			using type = decltype(trans(seq()));
		};
		template<class Tuple, template<class T>class Transform>
		using map_t = typename map<Tuple, Transform>::type;
	}

	namespace view
	{
		template<class Tuple, class Func>
		class map_view
		{
			friend tuple_trait<map_view>;
		public:
			map_view(Tuple&&tuple, Func&&func)
				:func(std::forward<Func>(func))
				, base(std::forward<Tuple>(tuple))
			{}
		private:
			Func&&func;
			Tuple&&base;
		};
		template<class Func>
		struct map_foward
		{
			map_foward(Func&&func)
			:func_(std::forward<Func>(func))
			{}
			template<class Tuple>
			friend map_view<Tuple, Func> operator|(Tuple&&tuple, map_foward&&this_)
			{
				return map_view<Tuple, Func>(std::forward<Tuple>(tuple),std::forward<Func>(this_.func_));
			}
		private:
			Func&&func_;
		};
		template<class Func>
		map_foward<Func> map(Func&&func)
		{
			return map_foward<Func>(std::forward<Func>(func));
		}
	}
	template<class Tuple,class Func>
	class tuple_trait<view::map_view<Tuple, Func>>
	{
		using base = utility::remove_const_ref_t<Tuple>;
	public:
		static const size_t size = type_list::size<base>::value;
		template<size_t N>
		struct element
		{
			using type = utility::remove_const_ref_t<typename std::result_of<Func(Tuple)>::type>;
		};
		template<size_t Idx,class T>
		static auto get(T&&tuple)
			->decltype(tuple.func(utility::foward_member_ref<T, Tuple>(tuple.base) | at<Idx>()))
		{
			return tuple.func(utility::foward_member_ref<T, Tuple>(tuple.base) | at<Idx>());
		}
		
	};
}