#pragma once
#include<iostream>
#include<tuple>


namespace tupleple{
	namespace debug
	{
		template<size_t N,class ...R>
		void element_output(const std::tuple<R...>&tuple)
		{
			std::cout << std::get<N>(tuple) << "\t:" << typeid(std::tuple_element<N, std::tuple<R...>>::type).name() << std::endl;
		} 
	}
}