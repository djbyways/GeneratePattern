#include "MLTypes.h"

namespace MathLink
{
	RealList::RealList(MLINK link)
		:	m_Link(link)
	{
		if(!MLGetRealList(link, &m_pData, &m_Size))
			throw Error(link);
	}
	
	RealList::~RealList()
	{
		MLDisownRealList(m_Link, m_pData, m_Size);		
	}
	
	RealArray::RealArray(MLINK link)
		:	m_Link(link)
	{
		if(!MLGetRealArray(link, &m_pData, &m_Dims, &m_Heads, &m_D))
			throw Error(link);
	}
	
	RealArray::~RealArray()
	{
		MLDisownRealArray(m_Link, m_pData, m_Dims, m_Heads, m_D);
	}
	
	Error::Error(MLINK link)
		:	m_Code(MLError(link)), m_Message(MLErrorMessage(link))
	{
		//TRACE1("MathLink error: %s\n", m_Message);
	}

	const char* Error::Message() const
	{
		return m_Message;
	}
}
