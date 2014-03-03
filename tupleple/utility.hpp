#pragma once
#include<tuple>

namespace tupleple
{
	namespace utility
	{
		namespace impl
		{
			template<bool r, class than_, class else_>
			struct if_impl
			{
				using type = than_;
			};
			template<class than_, class else_>
			struct if_impl<false, than_, else_>
			{
				using type = else_;
			};
		}
		template<bool r, class than_, class else_>
		using cond = typename impl::if_impl<r, than_, else_>::type;
	}
}