#pragma once
#include<functional>
#include<list>

namespace test
{
	struct Test
	{
	public:
		using call_back = std::function<void()>;
	private:
		static std::list<call_back>&
			get()
		{
			static std::list<call_back> list;
			return list;
		}
	public:
		static auto getList()->std::list<call_back>const &
		{
			return get();
		}
		static bool push_test(const call_back&test)
		{
			get().push_back(test);
			return true;
		}
	};

	namespace deteil
	{
		template<class T>
		struct ThrowTest
		{
			ThrowTest()
			:is_init_success(Test::push_test([]{T{}.test(); }))
			{}
			bool is_init_success;
		};
		template<class T>
		struct ThrowTestHolder
		{
			 static volatile deteil::ThrowTest<T> ater;
			 void check(bool r)
			 {
				
				 if (!(ater.is_init_success&&r))throw std::exception();
			 }
		};
		template<class T>
		deteil::ThrowTest<T>volatile ThrowTestHolder<T>::ater;
		
		template<class T, bool use>
		struct TestCase_impl
			:ThrowTestHolder<T>
		{
			virtual void test() = 0;
		};
		template<class T>
		struct TestCase_impl<T, false>
		{};
	}

	template<class CRTP>
	struct TestCase
		:deteil::TestCase_impl<CRTP, true>
	{};
}