#pragma once
#include<tuple>

namespace tupleple
{
	namespace utility
	{
		template<bool r,class than_,class else_>
		struct if_
		{
			using type = than_;
		};
		template<class than_, class else_>
		struct if_<false,than_,else_>
		{
			using type = else_;
		};
	}
}