#pragma once

namespace jwr
{

template <class T>
class vector
{
public:
	vector() : m_begin(nullptr), m_contentEnd(nullptr), m_allocEnd(nullptr)
	{

	}

	size_t capacity() const
	{
		return (m_allocEnd - m_begin);
	}

	size_t size() const
	{
		return (m_contentEnd - m_begin);
	}

	void push_back(const T& item)
	{
		if (m_contentEnd == m_allocEnd)
			grow(size() + 1);

		*m_contentEnd = item;
		++m_contentEnd;
	}

	void reserve(size_t minCapacity)
	{
		grow(minCapacity);
	}

	void clear()
	{
		m_contentEnd = m_begin;
	}
private:
	T* m_begin;
	T* m_contentEnd;
	T* m_allocEnd;

	void grow(size_t minCapacity)
	{
		// Determine capacity
		size_t oldSize = size();
		size_t newCapacity = oldSize;
		while (newCapacity < minCapacity)
		{
			if (newCapacity < 2)
				newCapacity = 2;
			else
				newCapacity = newCapacity + (newCapacity / 2);
		}

		// Allocate
		T* newBegin = new T[newCapacity];
		
		// Copy
		for (size_t i = 0 ; i < size() ; ++i)
		{
			newBegin[i] = m_begin[i];
		}

		// Cleanup
		delete[] m_begin;

		// Set ne pointers
		m_begin = newBegin;
		m_contentEnd = newBegin + oldSize;
		m_allocEnd = newBegin + newCapacity;
	}
};

}