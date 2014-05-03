#pragma once
#include"tuple.hpp"
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

namespace tupleple
{
	namespace view
	{
		struct map_tag{};
		template<class Tuple, class Func>
		using map_view = utility::basic_view<map_tag,Tuple, Func>;
		

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
		using View = view::map_view<Tuple, Func>;
	public:
		static const size_t size = type_list::size<base>::value;
		template<size_t N>
		struct element
		{
			using type = typename std::result_of<Func(type_list::at_t<N, base>)>::type;
		};
		template<size_t Idx,class T>
		static auto get(T&&tuple)
			->decltype(View::second(std::forward<T>(tuple))(View::first(std::forward<T>(tuple)) | at<Idx>()))
		{
			return View::second(std::forward<T>(tuple))(View::first(std::forward<T>(tuple)) | at<Idx>());
		}
		
	};
}