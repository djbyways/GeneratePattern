#ifndef MLTYPES_H
#define MLTYPES_H

#include <cassert>
#include <numeric>
#include <functional>
#include <valarray>
#include <vector>
#include <complex>

/*
#include <afx.h>

#undef min
#undef max
  */

extern "C"
{
#include <mathlink.h>
}

#pragma warning(push)
#pragma warning( disable : 4290 ) 

namespace MathLink
{
	class Error
	{
	public:
		const char* Message() const;
		Error(MLINK link);
	private:
		const char * m_Message;
		long m_Code;
	};

	class RealList
	{
	private:
		MLINK m_Link;
		long m_Size;
		double * m_pData;
	public:
		~RealList();
		RealList(MLINK link) throw(Error);

		inline operator const double*() const
		{
			return m_pData;
		}

		inline size_t Length() const
		{
			return m_Size;
		}
	};

	class RealArray
	{
	private:
		MLINK m_Link;
		long m_D;
		char ** m_Heads;
		long * m_Dims;
		double * m_pData;
	public:
		inline size_t TotalElements() const
		{
			return std::accumulate(m_Dims, m_Dims + m_D, 1, std::multiplies<long>());
		}

		inline size_t Level() const
		{
			return m_D;
		}

		inline size_t Dims(int l) const
		{
			assert(l >= 0 && l < m_D);
			return m_Dims[l];
		}

		~RealArray();
		RealArray(MLINK link) throw(Error);
		
		inline operator const double*() const
		{
			return m_pData;
		}

		inline double operator()(size_t i, size_t j) const
		{
			assert(Level() == 2);
			assert(i < Dims(0));
			assert(j < Dims(1));

			return m_pData[i * Dims(1) + j];
		}
	};
	
	class Real
	{
	private:
		double m_Value;
	public:
		Real(MLINK link)
		{
			if(!MLGetReal(link, &m_Value))
				throw Error(link);
		}

		operator double() const
		{
			return m_Value;
		}
	};
	
	inline void MLEvaluateString(MLINK link, charp_ct ch)
	{
		if(!::MLEvaluateString(link, ch))
			throw Error(link);
	}

	inline void MLPutReal(MLINK mlp, double_nt d)
	{
		if(!::MLPutReal(mlp, d))
			throw Error(mlp);
	}

	inline void MLPutReal(double_nt d)
	{
		::MLPutReal(stdlink, d);
	}

	inline void MLPutSymbol(MLINK mlp, kcharp_ct s)
	{
		if(!::MLPutSymbol(mlp, s))
			throw Error(mlp);
	}

	inline void MLPutSymbol(kcharp_ct s)
	{
		::MLPutSymbol(stdlink, s);
	}

	inline void PutFunction(MLINK mlp, kcharp_ct s, long_st argc)
	{
		if(!::MLPutFunction(mlp, s, argc))
			throw Error(mlp);
	}

	// Obsolete
	inline void MLPutFunction(MLINK mlp, kcharp_ct s, long_st argc)
	{
		PutFunction(mlp, s, argc);
	}
	
	inline void PutFunction(kcharp_ct s, long_st argc)
	{
		PutFunction(stdlink, s, argc);
	}

	// Obsolete
	inline void MLPutFunction(kcharp_ct s, long_st argc)
	{
		PutFunction(stdlink, s, argc);
	}

	inline void MLPutInteger(MLINK mlp, int_nt i)
	{
		if(!::MLPutInteger(mlp, i))
			throw Error(mlp);
	}

	inline void MLPutInteger(int_nt i)
	{
		::MLPutInteger(stdlink, i);
	}

	template<class T>
	inline void Put(const std::complex<T>& c)
	{
		PutFunction("Complex", 2);
		MLPutReal(c.real());
		MLPutReal(c.imag());
	}

	inline void MLPutRealList(MLINK mlp, const double * pdata, size_t n)
	{
		if(!::MLPutRealList(mlp, const_cast<double *>(pdata), n))
			throw Error(mlp);
	}

	inline void MLPutRealList(const double * pdata, size_t n)
	{
		MLPutRealList(stdlink, pdata, n);
	}

	inline void MLPutRealList(MLINK mlp, const std::valarray<double>& data)
	{
		double * tmp = new double[data.size()];
		for(size_t i = 0; i < data.size(); i++)
			tmp[i] = data[i];
		
		try
		{
			::MLPutRealList(mlp, tmp, data.size());
		}
		catch(...)
		{
			delete tmp;
			throw;
		}
		
		delete tmp;
	}

	inline void MLPutRealList(MLINK mlp, const std::vector<double>& data)
	{
		double * tmp = new double[data.size()];
		std::copy(data.begin(), data.end(), tmp);
		
		::MLPutRealList(mlp, tmp, data.size());

		delete[] tmp;
	}

	inline void MLPutRealList(const std::vector<double>& data)
	{
		MLPutRealList(stdlink, data);
	}
	
	inline std::string MLGetSymbol(MLINK mlp = stdlink)
	{
		const char * s;
		if(!::MLGetSymbol(mlp, &s))
			throw Error(mlp);
		std::string r = s;
		::MLDisownSymbol(mlp, s);
		return r;
	}

	class Bool
	{
		bool m_Value;

	public:
		Bool(MLINK mlp = stdlink)
		:	m_Value(!MLGetSymbol().compare("True"))
		{
		}

		operator bool() const
		{
			return m_Value;
		}
	};

	template<class T>
	class OutputIterator
	{
		MLINK m_Link;

	public:
		OutputIterator(MLINK link = stdlink)
			:	m_Link(link)
		{
		}

		OutputIterator<T>& operator++()
		{
			return *this;
		}

		OutputIterator<T>& operator++(int)
		{
			return *this;
		}

		OutputIterator<T>& operator*()
		{
			return *this;
		}

		OutputIterator<T>& operator=(const T&);
	};
}

namespace MLTypes
{
	using namespace MathLink;
}

#pragma warning(pop)
#endif