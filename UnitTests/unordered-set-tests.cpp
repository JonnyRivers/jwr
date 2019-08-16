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
			
		}

		std::string m_firstName;
		std::string m_lastName;
	};

	struct PersonHasher
	{
		std::size_t operator()(const Person& person) const noexcept
		{
			std::size_t h1 = std::hash<std::string>{}(person.m_firstName);
			std::size_t h2 = std::hash<std::string>{}(person.m_lastName);
			return h1 ^ (h2 << 1);
		}
	};

	TEST_CLASS(PREFIX_STL_NAME(UnorderedSetTests))
	{
	public:
		TEST_METHOD(PREFIX_STL_NAME(UnorderedSetTestCreationWithClass))
		{
			{
				std::string firstName("Neil");
				std::string lastName("Armstrong");
				STL::unordered_set<Person, PersonHasher> people;
			}
		}
	};
}