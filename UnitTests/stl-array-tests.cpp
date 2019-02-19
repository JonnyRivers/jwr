#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	class Person
	{
	public:
		Person(const std::string& firstName, const std::string& lastName)
			: m_firstName(firstName), m_lastName(lastName)
		{
			++m_numLiving;
		}

		~Person()
		{
			--m_numLiving;
		}

		std::string m_firstName;
		std::string m_lastName;

		static unsigned int m_numLiving;
	};

	unsigned int Person::m_numLiving = 0;

	TEST_CLASS(StlArrayTests)
	{
	public:
		TEST_METHOD(StlArrayTestCreationWithClass)
		{
			{
				std::string firstName("Neil");
				std::string lastName("Armstrong");
				std::array<Person, 1> people{ Person {firstName, lastName} };

				Assert::AreEqual(1u, Person::m_numLiving);
				Assert::AreEqual(static_cast<size_t>(1), people.size());
				Assert::AreEqual(firstName, people[0].m_firstName);
				Assert::AreEqual(lastName, people[0].m_lastName);
			}
			
			Assert::AreEqual(0u, Person::m_numLiving);
		}

		TEST_METHOD(StlArrayTestCreationWithPOD)
		{
			std::array<int, 1> numbers{ 1 };

			Assert::AreEqual(static_cast<size_t>(1), numbers.size());
			Assert::AreEqual(1, numbers[0]);
		}

		TEST_METHOD(StlArrayTestAssignmentOperator)
		{
			{
				std::string firstName1("Neil");
				std::string lastName1("Armstrong");
				std::array<Person, 1> people1{ Person {firstName1, lastName1} };

				std::string firstName2("Buzz");
				std::string lastName2("Aldrin");
				std::array<Person, 1> people2{ Person {firstName2, lastName2} };

				people1 = people2;

				Assert::AreEqual(2u, Person::m_numLiving);// Two copies of Buzz
				Assert::AreEqual(static_cast<size_t>(1), people1.size());
				Assert::AreEqual(firstName2, people1[0].m_firstName);
				Assert::AreEqual(lastName2, people1[0].m_lastName);
				Assert::AreEqual(static_cast<size_t>(1), people2.size());
				Assert::AreEqual(firstName2, people2[0].m_firstName);
				Assert::AreEqual(lastName2, people2[0].m_lastName);
			}

			Assert::AreEqual(0u, Person::m_numLiving);
		}

		TEST_METHOD(StlArrayTestAt)
		{
			std::array<int, 3> numbers{ {4, 9, 16} };
			try
			{
				numbers.at(3);
				Assert::Fail();
			}
			catch (std::out_of_range) {}

			Assert::AreEqual(4, numbers.at(0));
			Assert::AreEqual(9, numbers.at(1));
			Assert::AreEqual(16, numbers.at(2));
		}
	};
}