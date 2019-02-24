#pragma once

#include <xmemory>

namespace jwr
{
	template <class T, std::size_t N>
	struct array
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
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
	private:
		T m_data[N];
	};
}