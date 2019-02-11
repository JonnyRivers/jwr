#pragma once

#include <xmemory>

namespace jwr
{

template <class T>
class vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;

	vector() : m_begin(nullptr), m_contentEnd(nullptr), m_allocEnd(nullptr)
	{

	}

	reference at(size_t index)
	{
		if (index >= size())
			throw std::out_of_range("index out of range");

		return m_begin[index];
	}

	const_reference at(size_t index) const
	{
		if (index >= size())
			throw std::out_of_range("index out of range");

		return m_begin[index];
	}

	reference back()
	{
		return *(m_contentEnd - 1);
	}

	const_reference back() const
	{
		return *(m_contentEnd - 1);
	}

	iterator begin()
	{
		return m_begin;
	}

	const_iterator begin() const
	{
		return m_begin;
	}

	bool empty() const noexcept
	{
		return (m_contentEnd == m_begin);
	}

	size_t capacity() const
	{
		return (m_allocEnd - m_begin);
	}

	void clear()
	{
		m_contentEnd = m_begin;
	}

	template<class... A>
	void emplace_back(A&&... args)
	{
		if (m_contentEnd == m_allocEnd)
			grow(size() + 1);

		::new (static_cast<void*>(m_contentEnd)) T(std::forward<A>(args)...);
		++m_contentEnd;
	}

	reference operator[](size_t index)
	{
		return m_begin[index];
	}

	const_reference operator[](size_t index) const
	{
		return m_begin[index];
	}

	void push_back(const_reference item)
	{
		if (m_contentEnd == m_allocEnd)
			grow(size() + 1);

		*m_contentEnd = item;
		++m_contentEnd;
	}

	void reserve(size_t minCapacity)
	{
		if (capacity() >= minCapacity)
			return;

		grow(minCapacity);
	}

	size_t size() const
	{
		return (m_contentEnd - m_begin);
	}
	
private:
	iterator m_begin;
	iterator m_contentEnd;
	iterator m_allocEnd;

	void grow(size_t minCapacity)
	{
		// Determine capacity
		size_t oldSize = size();
		size_t newCapacity = oldSize;
		if (newCapacity < 2)
			newCapacity = 2;
		else
			newCapacity = newCapacity + (newCapacity / 2);

		if(newCapacity < minCapacity)
			newCapacity = minCapacity;

		// Allocate (should be deferred to an allocator)
		size_t allocSize = newCapacity * sizeof(T);
		T* newBegin = reinterpret_cast<T*>(new unsigned char[allocSize]);
		
		// Copy
		for (size_t i = 0 ; i < size() ; ++i)
		{
			newBegin[i] = m_begin[i];
		}

		// Cleanup
		delete[] m_begin;

		// Set new pointers
		m_begin = newBegin;
		m_contentEnd = newBegin + oldSize;
		m_allocEnd = newBegin + newCapacity;
	}
};

}