#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include "../lib/vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(JwrVectorTests)
	{
	public:
		
		TEST_METHOD(JwrVectorTestSize)
		{
			jwr::vector<int> numbers;
			Assert::AreEqual(static_cast<size_t>(0), numbers.size());

			numbers.push_back(1);
			Assert::AreEqual(static_cast<size_t>(1), numbers.size());

			numbers.push_back(5);
			numbers.push_back(3);
			Assert::AreEqual(static_cast<size_t>(3), numbers.size());

			numbers.clear();
			Assert::AreEqual(static_cast<size_t>(0), numbers.size());
		}

		TEST_METHOD(JwrVectorTestCapacity)
		{
			jwr::vector<int> numbers;
			Assert::AreEqual(static_cast<size_t>(0), numbers.capacity());

			numbers.reserve(10);

			numbers.push_back(1);
			Assert::IsTrue(numbers.capacity() >= 10);
		}

		class Person
		{
		public:
			Person() {}// TODO - remove this requirement
			Person(const std::string& firstName, const std::string& lastName)
				: m_firstName(firstName), m_lastName(lastName)
			{
			}

			std::string m_firstName;
			std::string m_lastName;
		};

		TEST_METHOD(JwrVectorTestEmplaceBack)
		{
			jwr::vector<Person> people;
			std::string firstName("Neil");
			std::string lastName("Armstrong");
			people.emplace_back(firstName, lastName);

			Assert::AreEqual(static_cast<size_t>(1), people.size());
			Assert::AreEqual(firstName, people[0].m_firstName);
			Assert::AreEqual(lastName, people[0].m_lastName);
		}
	};
}