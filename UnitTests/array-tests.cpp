#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

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

	TEST_CLASS(PREFIX_STL_NAME(ArrayTests))
	{
	public:
		TEST_METHOD(PREFIX_STL_NAME(ArrayTestCreationWithClass))
		{
			{
				std::string firstName("Neil");
				std::string lastName("Armstrong");
				STL::array<Person, 1> people{ Person {firstName, lastName} };

				Assert::AreEqual(1u, Person::m_numLiving);
				Assert::AreEqual(static_cast<size_t>(1), people.size());
				Assert::AreEqual(firstName, people[0].m_firstName);
				Assert::AreEqual(lastName, people[0].m_lastName);
			}
			
			Assert::AreEqual(0u, Person::m_numLiving);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestCreationWithPOD))
		{
			STL::array<int, 1> numbers{ 1 };

			Assert::AreEqual(static_cast<size_t>(1), numbers.size());
			Assert::AreEqual(1, numbers[0]);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestAssignmentOperator))
		{
			{
				std::string firstName1("Neil");
				std::string lastName1("Armstrong");
				STL::array<Person, 1> people1{ Person {firstName1, lastName1} };

				std::string firstName2("Buzz");
				std::string lastName2("Aldrin");
				STL::array<Person, 1> people2{ Person {firstName2, lastName2} };

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

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestIterator))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			int forward_extracted_numbers[3];
			int backward_extracted_numbers[3];
			int modified_extracted_numbers[3];

			int extract_index = 0;
			for (STL::array<int, 3>::iterator it = numbers.begin();
				 it != numbers.end(); 
				++it, ++extract_index)
			{
				forward_extracted_numbers[extract_index] = *it;
			}

			extract_index = 2;
			for (STL::array<int, 3>::iterator it = numbers.end(); 
				 it > numbers.begin();
				 --extract_index)
			{
				--it;
				backward_extracted_numbers[extract_index] = *it;
			}

			extract_index = 0;
			for (STL::array<int, 3>::iterator it = numbers.begin();
				it != numbers.end();
				++it, ++extract_index)
			{
				modified_extracted_numbers[extract_index] = *it = extract_index;
			}

			Assert::AreEqual(4, forward_extracted_numbers[0]);
			Assert::AreEqual(9, forward_extracted_numbers[1]);
			Assert::AreEqual(16, forward_extracted_numbers[2]);

			Assert::AreEqual(4, backward_extracted_numbers[0]);
			Assert::AreEqual(9, backward_extracted_numbers[1]);
			Assert::AreEqual(16, backward_extracted_numbers[2]);

			Assert::AreEqual(0, modified_extracted_numbers[0]);
			Assert::AreEqual(1, modified_extracted_numbers[1]);
			Assert::AreEqual(2, modified_extracted_numbers[2]);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestConstIterator))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			int forward_extracted_numbers[3];
			int backward_extracted_numbers[3];

			int extract_index = 0;
			for (STL::array<int, 3>::const_iterator it = numbers.cbegin();
				it != numbers.end();
				++it, ++extract_index)
			{
				forward_extracted_numbers[extract_index] = *it;
			}

			extract_index = 2;
			for (STL::array<int, 3>::const_iterator it = numbers.cend();
				it > numbers.begin();
				--extract_index)
			{
				--it;
				backward_extracted_numbers[extract_index] = *it;
			}

			Assert::AreEqual(4, forward_extracted_numbers[0]);
			Assert::AreEqual(9, forward_extracted_numbers[1]);
			Assert::AreEqual(16, forward_extracted_numbers[2]);

			Assert::AreEqual(4, backward_extracted_numbers[0]);
			Assert::AreEqual(9, backward_extracted_numbers[1]);
			Assert::AreEqual(16, backward_extracted_numbers[2]);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestAt))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
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

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestSubscriptOperator))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };

			Assert::AreEqual(4, numbers[0]);
			Assert::AreEqual(9, numbers[1]);
			Assert::AreEqual(16, numbers[2]);

			numbers[0] = 17;
			numbers[1] = 8;
			numbers[2] = 2;

			Assert::AreEqual(17, numbers[0]);
			Assert::AreEqual(8, numbers[1]);
			Assert::AreEqual(2, numbers[2]);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestFront))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };

			Assert::AreEqual(4, numbers.front());
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestBack))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };

			Assert::AreEqual(16, numbers.back());
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestData))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			int* data = numbers.data();

			Assert::AreEqual(4, data[0]);
			Assert::AreEqual(9, data[1]);
			Assert::AreEqual(16, data[2]);

			data[1] = 11;

			Assert::AreEqual(4, numbers.at(0));
			Assert::AreEqual(11, numbers.at(1));
			Assert::AreEqual(16, numbers.at(2));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestBegin))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			STL::array<int, 3>::iterator iter = numbers.begin();

			Assert::AreEqual(4, *iter);

			*iter = 7;

			Assert::AreEqual(7, numbers.at(0));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestConstBegin))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			STL::array<int, 3>::const_iterator iter = numbers.cbegin();

			Assert::AreEqual(4, *iter);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestEnd))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			STL::array<int, 3>::iterator endIter = numbers.end();
			std::ptrdiff_t distance = std::distance(numbers.begin(), endIter);

			Assert::AreEqual(static_cast<std::ptrdiff_t>(3), distance);

			*(--endIter) = 1;

			Assert::AreEqual(1, numbers.at(2));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestConstEnd))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			STL::array<int, 3>::const_iterator endIter = numbers.cend();
			std::ptrdiff_t distance = std::distance(numbers.cbegin(), endIter);

			Assert::AreEqual(static_cast<std::ptrdiff_t>(3), distance);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestReverseBegin))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			std::reverse_iterator<STL::array<int, 3>::iterator> iter = numbers.rbegin();

			Assert::AreEqual(16, *iter);

			*iter = 7;

			Assert::AreEqual(7, numbers.at(2));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestConstReverseBegin))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			std::reverse_iterator<STL::array<int, 3>::const_iterator> iter = numbers.crbegin();

			Assert::AreEqual(16, *iter);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestReverseEnd))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			std::reverse_iterator<STL::array<int, 3>::iterator> endIter = numbers.rend();
			std::ptrdiff_t distance = std::distance(numbers.rbegin(), endIter);

			Assert::AreEqual(static_cast<std::ptrdiff_t>(3), distance);

			*(--endIter) = 1;

			Assert::AreEqual(1, numbers.at(0));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestConstReverseEnd))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			std::reverse_iterator<STL::array<int, 3>::const_iterator> endIter = numbers.crend();
			std::ptrdiff_t distance = std::distance(numbers.crbegin(), endIter);

			Assert::AreEqual(static_cast<std::ptrdiff_t>(3), distance);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestEmpty))
		{
			STL::array<int, 0> no_numbers;
			STL::array<int, 3> numbers{ {4, 9, 16} };

			Assert::IsTrue(no_numbers.empty());
			Assert::IsFalse(numbers.empty());
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestSize))
		{
			STL::array<int, 0> no_numbers;
			STL::array<int, 3> numbers{ {4, 9, 16} };

			Assert::AreEqual(std::size_t(0), no_numbers.size());
			Assert::AreEqual(std::size_t(3), numbers.size());
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestMaxSize))
		{
			STL::array<int, 0> no_numbers;
			STL::array<int, 3> numbers{ {4, 9, 16} };

			Assert::AreEqual(std::size_t(0), no_numbers.max_size());
			Assert::AreEqual(std::size_t(3), numbers.max_size());
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestFill))
		{
			STL::array<int, 3> numbers{ {4, 9, 16} };
			numbers.fill(666);

			Assert::AreEqual(666, numbers.at(0));
			Assert::AreEqual(666, numbers.at(1));
			Assert::AreEqual(666, numbers.at(2));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestSwap))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> more_numbers{ {2, 4, 9} };

			some_numbers.swap(more_numbers);

			Assert::AreEqual(2, some_numbers.at(0));
			Assert::AreEqual(4, some_numbers.at(1));
			Assert::AreEqual(9, some_numbers.at(2));

			Assert::AreEqual(1, more_numbers.at(0));
			Assert::AreEqual(2, more_numbers.at(1));
			Assert::AreEqual(3, more_numbers.at(2));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestEqualityOperator))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> same_numbers{ {1, 2, 3} };
			STL::array<int, 3> different_numbers{ {2, 4, 9} };

			Assert::IsTrue(some_numbers == same_numbers);
			Assert::IsFalse(some_numbers == different_numbers);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestInequalityOperator))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> same_numbers{ {1, 2, 3} };
			STL::array<int, 3> different_numbers{ {2, 4, 9} };

			Assert::IsFalse(some_numbers != same_numbers);
			Assert::IsTrue(some_numbers != different_numbers);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestLessThanOperator))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> same_numbers{ {1, 2, 3} };
			STL::array<int, 3> immediately_smaller_numbers{ {-3, 2, 3} };
			STL::array<int, 3> eventually_smaller_numbers{ {1, 2, 2} };
			STL::array<int, 3> immediately_greater_numbers{ {6, 2, 3} };
			STL::array<int, 3> eventually_greater_numbers{ {1, 2, 4} };

			Assert::IsFalse(some_numbers < same_numbers);
			Assert::IsFalse(some_numbers < immediately_smaller_numbers);
			Assert::IsFalse(some_numbers < eventually_smaller_numbers);
			Assert::IsTrue(some_numbers < immediately_greater_numbers);
			Assert::IsTrue(some_numbers < eventually_greater_numbers);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestLessThanOrEqualOperator))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> same_numbers{ {1, 2, 3} };
			STL::array<int, 3> immediately_smaller_numbers{ {-3, 2, 3} };
			STL::array<int, 3> eventually_smaller_numbers{ {1, 2, 2} };
			STL::array<int, 3> immediately_greater_numbers{ {6, 2, 3} };
			STL::array<int, 3> eventually_greater_numbers{ {1, 2, 4} };

			Assert::IsTrue(some_numbers <= same_numbers);
			Assert::IsFalse(some_numbers <= immediately_smaller_numbers);
			Assert::IsFalse(some_numbers <= eventually_smaller_numbers);
			Assert::IsTrue(some_numbers <= immediately_greater_numbers);
			Assert::IsTrue(some_numbers <= eventually_greater_numbers);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestGreaterThanOperator))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> same_numbers{ {1, 2, 3} };
			STL::array<int, 3> immediately_smaller_numbers{ {-3, 2, 3} };
			STL::array<int, 3> eventually_smaller_numbers{ {1, 2, 2} };
			STL::array<int, 3> immediately_greater_numbers{ {6, 2, 3} };
			STL::array<int, 3> eventually_greater_numbers{ {1, 2, 4} };

			Assert::IsFalse(some_numbers > same_numbers);
			Assert::IsTrue(some_numbers > immediately_smaller_numbers);
			Assert::IsTrue(some_numbers > eventually_smaller_numbers);
			Assert::IsFalse(some_numbers > immediately_greater_numbers);
			Assert::IsFalse(some_numbers > eventually_greater_numbers);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestGreaterThanOrEqualOperator))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> same_numbers{ {1, 2, 3} };
			STL::array<int, 3> immediately_smaller_numbers{ {-3, 2, 3} };
			STL::array<int, 3> eventually_smaller_numbers{ {1, 2, 2} };
			STL::array<int, 3> immediately_greater_numbers{ {6, 2, 3} };
			STL::array<int, 3> eventually_greater_numbers{ {1, 2, 4} };

			Assert::IsTrue(some_numbers >= same_numbers);
			Assert::IsTrue(some_numbers >= immediately_smaller_numbers);
			Assert::IsTrue(some_numbers >= eventually_smaller_numbers);
			Assert::IsFalse(some_numbers >= immediately_greater_numbers);
			Assert::IsFalse(some_numbers >= eventually_greater_numbers);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestNonMemberGet))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };

			Assert::AreEqual(1, std::get<0>(some_numbers));
			Assert::AreEqual(2, std::get<1>(some_numbers));
			Assert::AreEqual(3, std::get<2>(some_numbers));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestNonMemberSwap))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };
			STL::array<int, 3> more_numbers{ {2, 4, 9} };

			std::swap(some_numbers, more_numbers);

			Assert::AreEqual(2, some_numbers.at(0));
			Assert::AreEqual(4, some_numbers.at(1));
			Assert::AreEqual(9, some_numbers.at(2));

			Assert::AreEqual(1, more_numbers.at(0));
			Assert::AreEqual(2, more_numbers.at(1));
			Assert::AreEqual(3, more_numbers.at(2));
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestTupleSize))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };

			std::size_t size = std::tuple_size<STL::array<int, 3>>::value;

			Assert::AreEqual(static_cast<std::size_t>(3u), size);
		}

		TEST_METHOD(PREFIX_STL_NAME(ArrayTestTupleType))
		{
			STL::array<int, 3> some_numbers{ {1, 2, 3} };

			using T = std::tuple_element<0, decltype(some_numbers)>::type;
			bool is_same_as_int = std::is_same<T, int>::value;
			bool is_same_as_float = std::is_same<T, float>::value;

			Assert::IsTrue(is_same_as_int);
			Assert::IsFalse(is_same_as_float);
		}
	};
}