#pragma once
#include<type_traits>


namespace tupleple
{
	template<class T>
	struct is_view
	{
		static const bool value = false;
	};
}