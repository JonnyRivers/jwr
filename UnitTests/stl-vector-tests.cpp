#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(StlVectorTests)
	{
	public:
		
		TEST_METHOD(StlVectorTestSize)
		{
			std::vector<int> numbers;
			Assert::AreEqual(static_cast<size_t>(0), numbers.size());

			numbers.push_back(1);
			Assert::AreEqual(static_cast<size_t>(1), numbers.size());

			numbers.push_back(5);
			numbers.push_back(3);
			Assert::AreEqual(static_cast<size_t>(3), numbers.size());

			numbers.clear();
			Assert::AreEqual(static_cast<size_t>(0), numbers.size());
		}

		TEST_METHOD(StlVectorTestCapacity)
		{
			std::vector<int> numbers;
			Assert::AreEqual(static_cast<size_t>(0), numbers.capacity());

			numbers.reserve(10);

			numbers.push_back(1);
			Assert::IsTrue(numbers.capacity() >= 10);
		}
	};
}