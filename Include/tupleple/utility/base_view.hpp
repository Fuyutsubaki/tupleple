#ifndef TUPLEPLE_UTILITY_BASE_VIEW_HPP
#define TUPLEPLE_UTILITY_BASE_VIEW_HPP



namespace tupleple
{
	namespace impl
	{
		namespace deteil
		{
			class dummy{};
		}
		
		template<class Crtp,class Tuple , class Super = deteil::dummy>
		class base_view :protected Super
		{
			friend tuple_trait<Crtp>;
		protected:
			template<class T, class...R>
			base_view(T&&x, R&&...args)
				:Super(std::forward<R>(args)...)
				, base(std::forward<T>(x))
			{}
			Tuple base;
			using isuper = base_view;
		};
	}
}
#endif