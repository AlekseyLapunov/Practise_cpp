#pragma once

namespace diy
{
	template<typename container>
	class iterator;

	template <typename T>
	class vector
	{
	public:
		using ValueType = T;
		using iter = iterator<vector<T>>;

	private:
		static const size_t initialSize = 2;

	public:
		vector()
		{
			reAlloc(initialSize);
		}

		~vector()
		{
			clear();
			::operator delete(m_data, m_capacity * sizeof(T));
		}

		void pushBack(const T& value)
		{
			if (m_size >= m_capacity)
			{
				reAlloc(m_capacity + m_capacity / 2);
			}

			m_data[m_size] = value;
			m_size++;
		}

		void pushBack(T&& value)
		{
			if (m_size >= m_capacity)
			{
				reAlloc(m_capacity + m_capacity / 2);
			}

			m_data[m_size] = std::move(value);
			m_size++;
		}

		template <typename... Args>
		T& emplaceBack(Args&&... args)
		{
			if (m_size >= m_capacity)
			{
				reAlloc(m_capacity + m_capacity / 2);
			}

			new(&m_data[m_size]) T(std::forward<Args>(args)...);
			m_size++;

			return m_data[m_size];
		}

		void popBack()
		{
			if (m_size > 0)
			{
				m_size--;
				m_data[m_size].~T();
			}
		}

		void clear()
		{
			for (size_t i = 0; i < m_size; i++)
			{
				m_data[i].~T();
			}

			m_size = 0;
		}

		T& operator[](size_t index)
		{
			if (index >= m_size)
			{
			}

			return m_data[index];
		}

		const T& operator[](size_t index) const
		{
			if (index >= m_size)
			{
			}

			return m_data[index];
		}

		size_t size() const
		{
			return m_size;
		}

	public:
		iter begin()
		{
			return iter(m_data);
		}

		iter end()
		{
			return iter(m_data + m_size);
		}

	private:
		void reAlloc(size_t newCapacity)
		{
			T* newBlock = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

			if (newCapacity < m_size)
				m_size = newCapacity;

			for (size_t i = 0; i < m_size; i++)
			{
				new (&newBlock[i]) T(std::move(m_data[i]));
			}

			for (size_t i = 0; i < m_size; i++)
			{
				m_data[i].~T();
			}

			::operator delete(m_data, m_capacity * sizeof(T));

			m_data = newBlock;
			m_capacity = newCapacity;
		}

	private:
		T* m_data = nullptr;

		size_t m_size = 0;
		size_t m_capacity = 0;
	}; // class vector

	template <typename vector>
	class iterator
	{
		using T = typename vector::ValueType;
	public:
		iterator(T* ptr) : m_ptr(ptr)
		{}

		iterator& operator++()
		{
			m_ptr++;
			return *this;
		}

		iterator& operator++(int)
		{
			iterator iter = *this;
			++(*this);
			return iter;
		}

		iterator& operator--()
		{
			m_ptr--;
			return *this;
		}

		iterator& operator--(int)
		{
			iterator iter = *this;
			--(*this);
			return iter;
		}

		T& operator[](int index)
		{
			return *(m_ptr + index);
		}

		T* operator->()
		{
			return m_ptr;
		}

		T& operator*()
		{
			return *m_ptr;
		}

		bool operator== (const iterator& other) const
		{
			return m_ptr == other.m_ptr;
		}

		bool operator!= (const iterator& other) const
		{
			return m_ptr != other.m_ptr;
		}

	private:
		T* m_ptr;
	}; // class iterator

}// namespace diy
