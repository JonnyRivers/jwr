#pragma once

#include <xmemory>

namespace jwr
{
	template <class T>
	class unordered_set
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T& reference;
		typedef const T& const_reference;
	};
}