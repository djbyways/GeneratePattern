#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <cstddef>
#include <algorithm>
#include <cassert>
#include <iostream>

namespace arrays
{
	template<class T>
	class Array
	{
	public:
		typedef T * iterator;
		typedef const T * const_iterator;
		typedef const T& const_reference;
		typedef size_t size_type;

	private:
		T * m_P;
		size_type m_Size;

	public:
#ifdef _AFX
		void Serialize(CArchive& ar)
		{
			if(ar.IsStoring())
			{
				ar << m_Size;
				ar.Write(m_P, m_Size * sizeof(T));
			}
			else
			{
				size_type sz;
				ar >> sz;

				Array<T> tmp(sz);
				ar.Read((void*)tmp.m_P, sz * sizeof(T));

				swap(tmp);
			}
		}
#endif
		const_reference back() const
		{
			assert(size() > 0);
			return *(end() - 1);
		}

		const_reference front() const
		{
			assert(size() > 0);
			return *begin();
		}

		void resize(size_type new_size)
		{
			swap(Array<T>(new_size));
		}

		void swap(Array<T>& other)
		{
			std::swap(m_P, other.m_P);
			std::swap(m_Size, other.m_Size);
		}

		template<class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			resize(last - first);
			std::copy(first, last, begin());
		}

		const_iterator begin() const
		{
			return m_P;
		}

		const_iterator end() const
		{
			return m_P + m_Size;
		}


		iterator begin() 
		{
			return m_P;
		}

		iterator end() 
		{
			return m_P + m_Size;
		}

		Array(size_type sz = 0)
			:	m_P(new T[sz]),	m_Size(sz)
		{
		}

		Array(size_type sz, const T& init)
			:	m_P(new T[sz]),	m_Size(sz)
		{
			std::fill_n(begin(), sz, init);
		}

		Array(size_t sz, const T * src)
			:	m_P(new T[sz]),	m_Size(sz)
		{
			std::copy(src, src + sz, m_P);
		}

		template<class InputIterator>
		Array(InputIterator first, InputIterator last)
		:	m_P(new T[last - first]),	m_Size(last - first)
		{
			std::copy(first, last, m_P);
		}

		~Array()
		{
			delete[] m_P;
		}

		operator T*() const
		{
			return m_P;
		}

		Array<T>& operator=(const Array<T>& rhs)
		{
			assign(rhs.begin(), rhs.end());
			return *this;
		}

		Array(const Array<T>& rhs)
			:	m_P(0),	m_Size(0)
		{
			assign(rhs.begin(), rhs.end());
		}

		size_t size() const
		{
			return m_Size;
		}

		void clear(void)
		{
			swap(Array<T>());
		}

		bool empty(void) const
		{
			return size() == 0;
		}
};

	template<class T>
	class Array2d
	{
	public:
		inline void clear()
		{
			resize(0, 0);
		}
		
		void swap(Array2d<T>& A)
		{
			std::swap(m_Dim1, A.m_Dim1);
			std::swap(m_Dim2, A.m_Dim2);
			std::swap(m_pData, A.m_pData);
		}
		
#if defined(_AFX) && defined(_DEBUG)
		void Dump(CDumpContext& dc) const
		{
			for(int i = 0; i < m_Dim1; i++)
			{
				for(int j = 0; j < m_Dim2; j++)
					dc << (*this)[i][j] << "\t";
				dc << "\n";
			}
		}
		
		//friend CDumpContext& operator<<(CDumpContext& dc, Array2d<T>& a);
#endif
		
#ifdef _AFX
		void Serialize(CArchive& ar)
		{
			if(ar.IsStoring())
			{
				ar << dim1() << dim2();
				ar.Write(m_pData, dim1() * dim2() * sizeof(T));
			}
			else
			{
				size_type d1, d2;
				ar >> d1 >> d2;

				Array2d<T> tmp(d1, d2);
				ar.Read((void*)tmp.m_pData, tmp.dim1() * tmp.dim2() * sizeof(T));

				swap(tmp);
			}
		}
#endif

		typedef size_t size_type;
		typedef T value_type;

		inline size_type dim1() const
		{
			return m_Dim1;
		}

		inline size_type dim2() const
		{
			return m_Dim2;
		}
		
		inline ~Array2d()
		{
			delete[] m_pData;
		}
		
		inline Array2d(size_type dim1 = 0, size_type dim2 = 0, 
			const T * const * ppInit = NULL)
			:	m_Dim1(0),	m_Dim2(0),	m_pData(NULL)
		{
			resize(dim1, dim2) = ppInit;
		}
		
		inline Array2d(size_type dim1, size_type dim2, const T * pInit)
			:	m_Dim1(0),	m_Dim2(0),	m_pData(0)
		{
			resize(dim1, dim2);
			std::copy(pInit, pInit + dim1 * dim2, m_pData);
		}

		inline Array2d(size_type dim1, size_type dim2, 
			const T& Init)
			:	m_Dim1(0),	m_Dim2(0),	m_pData(NULL)
		{
			resize(dim1, dim2);
			std::fill(m_pData, m_pData + m_Dim2 * m_Dim1, Init);
		}
		
		inline Array2d(const Array2d<T>& A)
			:	m_Dim1(0),	m_Dim2(0),	m_pData(NULL)
		{
			*this = A;
		}
		
		inline Array2d<T>& operator=(const Array2d<T>& A)
		{
			resize(A.m_Dim1, A.m_Dim2);  
			std::copy(A.m_pData, A.m_pData + dim1() * dim2(), m_pData);
			return *this;
		}
		
		inline Array2d<T>& resize(size_type dim1, size_type dim2)
		{
			if(dim2 * dim1 != m_Dim2 * m_Dim1)
			{
				T * new_data = new T[dim1 * dim2];
				delete[] m_pData;
				m_pData = new_data;
				m_Dim1 = dim1;
				m_Dim2 = dim2;
			}

			return *this;
		}
		
		inline Array2d<T>& operator=(const T * const * ppInit)
		{
			if(ppInit)
				for(unsigned i = 0; i < m_Dim1; i++)
					if(ppInit[i])
						std::copy(ppInit[i], ppInit[i] + m_Dim2, m_pData + i * m_Dim2);

			return *this;
		}

		T * operator[](size_type index)
		{
			assert(index < dim1());
			return m_pData + index * m_Dim2;
		}

		const T * operator[](size_type index) const
		{
			assert(index < dim1());
			return m_pData + index * m_Dim2;
		}

		class const_iterator
		{
			Array2d<T>& m_Arr;
			int m_Index;

		public:
			const_iterator(Array2d<T>& arr, int index)
				:	m_Arr(arr),	m_Index(index)
			{
			}

			const T * operator*() const
			{
				assert(m_Index < m_Arr.dim1());
				return m_Arr[m_Index];
			}

			bool operator==(const const_iterator& rhs) const
			{
				return &m_Arr == &rhs.m_Arr && m_Index == rhs.m_Index;
			}

			bool operator!=(const const_iterator& rhs) const
			{
				return !(*this == rhs);
			}

			const_iterator& operator++()
			{
				m_Index++;
				return *this;
			}

			const_iterator operator++(int)
			{
				const iterator tmp = *this;
				m_Index++;
				return tmp;
			}

			const_iterator operator+(int diff)
			{
				return const_iterator(m_Arr, m_Index + diff);
			}
		};

		class iterator
		{
			Array2d<T>& m_Arr;
			int m_Index;

		public:
			operator const_iterator() const
			{
				return const_iterator(m_Arr, m_Index);
			}

			iterator(Array2d<T>& arr, int index)
				:	m_Arr(arr),	m_Index(index)
			{
			}

			T * operator*() const
			{
				assert(m_Index < m_Arr.dim1());
				return m_Arr[m_Index];
			}

			bool operator==(const iterator& rhs) const
			{
				return &m_Arr == &rhs.m_Arr && m_Index == rhs.m_Index;
			}

			bool operator!=(const iterator& rhs) const
			{
				return !(*this == rhs);
			}

			iterator& operator++()
			{
				m_Index++;
				return *this;
			}

			iterator operator++(int)
			{
				const iterator tmp = *this;
				m_Index++;
				return tmp;
			}

			iterator operator+(int diff)
			{
				return iterator(m_Arr, m_Index + diff);
			}
		};

		iterator begin()
		{
			return iterator(*this, 0);
		}

		iterator end()
		{
			return iterator(*this, dim1());
		}

		const_iterator begin() const
		{
			return const_iterator(*this, 0);
		}

		const_iterator end() const
		{
			return const_iterator(*this, dim1());
		}

	private:
		T * m_pData;
		size_type m_Dim1;
		size_type m_Dim2;
	};	
}

#if defined(_AFX) && defined(_DEBUG)
template<class T>
inline CDumpContext& operator<<(CDumpContext& dc, const arrays::Array2d<T>& a)
{
	a.Dump(dc);
	return dc;
}
#endif

template<class T>
std::ostream& operator<<(std::ostream& os, const arrays::Array2d<T>& a)
{
	for(int i = 0; i < a.dim1(); i++)
	{
		std::copy(a[i], a[i] + a.dim2(), std::ostream_iterator<T>(os, "\t"));
		os << endl;
	}

	return os;
}

#endif