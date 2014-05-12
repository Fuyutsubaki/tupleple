#pragma once
#include"tuple.hpp"
#include<type_traits>
#include"Index.hpp"
#include"STD_tuple_traits.hpp"
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

namespace tupleple
{
	namespace type_list
	{
		template<class Tuple, template<class>class F>
		class map
		{
			template<size_t ...Idx>
			static auto trans(index::Sequence<Idx...>)
				->std::tuple<typename F< at_t<Idx, Tuple> >::type ...>;
			using seq = index::make_tuple_size_seq_t<Tuple>;
		public:
			using type = decltype(trans(seq()));
		};
		template<class Tuple, template<class>class F>
		using map_t = typename map<Tuple, F>::type;
	}
	namespace index
	{
		template<class Tuple, template<class>class F>
		class map
		{
			template<size_t ...Idx>
			static auto trans(index::Sequence<Idx...>)
				->Sequence<(F< type_list::at_t<Idx, Tuple> >::value) ...>;
			using seq = index::make_tuple_size_seq_t<Tuple>;
		public:
			using type = decltype(trans(seq()));
		};
		template<class Tuple, template<class>class F>
		using map_t = typename map<Tuple, F>::type;
	}
	namespace view
	{
		template<class Tuple,class Functor>
		struct map_view
		{
			Tuple base;
			Functor func;
			friend tuple_trait<view::map_view<Tuple, Functor>>;
		public:
			map_view(Tuple&&tuple,Functor&&func)
				:base(std::forward<Tuple>(tuple))
				, func(std::forward<Functor>(func))
			{}
		};

		template<class Func>
		struct map_foward :utility::ExtensionMemberFunction
		{
			map_foward(Func&&func)
			:func_(std::forward<Func>(func))
			{}
			template<class Tuple>
			map_view<Tuple, Func> operator()(Tuple&&tuple)
			{
				return{ std::forward<Tuple>(tuple), std::forward<Func>(func_) };
			}
		private:
			Func func_;
		};

		template<class Func>
		map_foward<Func> map(Func&&func)
		{
			return{ std::forward<Func>(func) };
		}
	}



	template<class Tuple,class Func>
	class tuple_trait<view::map_view<Tuple, Func>>
	{
		using base = utility::remove_cv_ref_t<Tuple>;
	public:
		static const size_t size = type_list::size<base>::value;

		template<size_t N>
		using element
			= utility::remove_cv_ref_t<typename std::result_of<Func(type_list::at_t<N, base>)>::type>;

		template<size_t N, class T>
		using result_of
			= std::result_of<Func(type_list::result_of_t<N, utility::result_of_forward_mem_t<T, Tuple>>)>;

		template<size_t N, class T>
		static auto get(T&&x)
			->type_list::result_of_t<N, T>
		{
			return
				utility::forward_mem<T, Func>(x.func)
				(
					utility::forward_mem<T, Tuple>(x.base) | at<N>()
				);
		}
	};
}