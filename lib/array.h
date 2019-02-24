#pragma once

#include <xmemory>

namespace jwr
{
	template <class T, std::size_t N>
	class _array_const_iterator
	{
	public:
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;

		_array_const_iterator(pointer ptr) : m_ptr(ptr) {}

		constexpr reference operator*() const
		{
			return (*m_ptr);
		}

		constexpr pointer operator->() const
		{
			return m_ptr;
		}

		constexpr _array_const_iterator& operator++()
		{	// preincrement
			++m_ptr;
			return *this;
		}

		constexpr _array_const_iterator operator++(int)
		{	// postincrement
			_array_const_iterator temp = *this;
			++m_ptr;
			return (temp);
		}

		constexpr _array_const_iterator& operator--()
		{	// predecrement
			--m_ptr;
			return *this;
		}

		constexpr _array_const_iterator operator--(int)
		{	// postdecrement
			_array_const_iterator temp = *this;
			--m_ptr;
			return (temp);
		}

	private:
		pointer m_ptr;
	};

	template <class T, std::size_t N>
	class _array_iterator : public _array_const_iterator<T, N>
	{
	public:
		using my_base = _array_const_iterator;
		using pointer = T*;
		using reference = T&;

		_array_iterator(pointer ptr) : my_base(ptr) {}

		constexpr reference operator*() const
		{
			return (const_cast<reference>(*m_ptr));
		}

		constexpr pointer operator->() const
		{
			return const_cast<pointer>(m_ptr);
		}

		constexpr _array_iterator& operator++()
		{	// preincrement
			++m_ptr;
			return *this;
		}

		constexpr _array_iterator operator++(int)
		{	// postincrement
			_array_iterator temp = *this;
			++m_ptr;
			return (temp);
		}

		constexpr _array_iterator& operator--()
		{	// predecrement
			--m_ptr;
			return *this;
		}

		constexpr _array_iterator operator--(int)
		{	// postdecrement
			_array_iterator temp = *this;
			--m_ptr;
			return (temp);
		}
	};

	template <class T, std::size_t N>
	struct array
	{
	public:
		typedef _array_iterator<T, N> iterator;
		typedef _array_const_iterator<T, N> const_iterator;
		typedef T& reference;
		typedef const T& const_reference;

		constexpr reference at(size_t index)
		{
			if (index >= N)
				throw std::out_of_range("index out of range");

			return m_data[index];
		}

		constexpr const_reference at(size_t index) const
		{
			if (index >= N)
				throw std::out_of_range("index out of range");

			return m_data[index];
		}

		constexpr reference operator[](size_t index)
		{
			return m_data[index];
		}

		constexpr const_reference operator[](size_t index) const
		{
			return m_data[index];
		}

		constexpr reference front()
		{
			return m_data[0];
		}

		constexpr const_reference front() const
		{
			return m_data[0];
		}

		constexpr reference back()
		{
			return m_data[N - 1];
		}

		constexpr const_reference back() const
		{
			return m_data[N - 1];
		}

		constexpr T* data()
		{
			return m_data;
		}

		constexpr const T* data() const
		{
			return m_data;
		}

		constexpr iterator begin() noexcept
		{
			return _array_iterator(m_data);
		}

		constexpr const_iterator begin() const noexcept
		{
			return _array_const_iterator(m_data);
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return _array_const_iterator(m_data);
		}

		constexpr iterator end() noexcept
		{
			return _array_iterator(m_data + N);
		}

		constexpr const_iterator end() const noexcept
		{
			return _array_const_iterator(m_data + N);
		}

		constexpr const_iterator cend() const noexcept
		{
			return _array_const_iterator(m_data + N);
		}
	private:
		T m_data[N];
	};
}