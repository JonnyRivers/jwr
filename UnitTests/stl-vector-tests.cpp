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
		TEST_METHOD(StlVectorTestAt)
		{
			std::vector<int> numbers;
			try
			{
				numbers.at(0);
				Assert::Fail();
			}
			catch(std::out_of_range) {}

			numbers.push_back(2);
			numbers.push_back(12);

			Assert::AreEqual(2, numbers.at(0));
			Assert::AreEqual(12, numbers.at(1));
		}

		TEST_METHOD(StlVectorTestBack)
		{
			std::vector<int> numbers;
			numbers.push_back(3);
			numbers.push_back(7);

			Assert::AreEqual(7, numbers.back());
		}

		TEST_METHOD(StlVectorTestBegin)
		{
			std::vector<int> numbers;
			numbers.push_back(3);
			numbers.push_back(7);

			std::vector<int>::const_iterator begin = numbers.begin();
			Assert::AreEqual(3, *begin);
		}

		TEST_METHOD(StlVectorTestCapacity)
		{
			std::vector<int> numbers;
			Assert::AreEqual(static_cast<size_t>(0), numbers.capacity());

			numbers.reserve(10);

			numbers.push_back(1);
			Assert::IsTrue(numbers.capacity() >= 10);
		}
		
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

		class Person
		{
		public:
			Person(const std::string& firstName, const std::string& lastName)
				: m_firstName(firstName), m_lastName(lastName)
			{
			}

			std::string m_firstName;
			std::string m_lastName;
		};

		TEST_METHOD(StlVectorTestEmplaceBack)
		{
			std::vector<Person> people;
			std::string firstName("Neil");
			std::string lastName("Armstrong");
			people.emplace_back(firstName, lastName);

			Assert::AreEqual(static_cast<size_t>(1), people.size());
			Assert::AreEqual(firstName, people[0].m_firstName);
			Assert::AreEqual(lastName, people[0].m_lastName);
		}

		TEST_METHOD(StlVectorTestSubscriptOperator)
		{
			std::vector<int> numbers;
			numbers.push_back(1);
			numbers.push_back(3);
			numbers.push_back(6);

			Assert::AreEqual(1, numbers[0]);
			Assert::AreEqual(3, numbers[1]);
			Assert::AreEqual(6, numbers[2]);

			numbers[0] = 8;
			numbers[2] = 4;
			numbers[1] = 2;

			Assert::AreEqual(8, numbers[0]);
			Assert::AreEqual(2, numbers[1]);
			Assert::AreEqual(4, numbers[2]);
		}
	};
}