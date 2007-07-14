////////////////////////////////////////////////////////////////////////////////
//! \file   ComStr.cpp
//! \brief  The ComStr class definition.
//! \author Chris Oldwood

#include "wcl.hpp"
#include "ComStr.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ComStr::ComStr()
	: m_bstr(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction by taking ownership of an exsiting string.

ComStr::ComStr(BSTR bstr)
	: m_bstr(bstr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an ANSI string.

ComStr::ComStr(const char* psz)
	: m_bstr(nullptr)
{
	USES_CONVERSION;

	m_bstr = ::SysAllocString(A2W(psz));

	if (m_bstr == nullptr)
		throw std::bad_alloc();
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a UNICODE string.

ComStr::ComStr(const wchar_t* psz)
	: m_bstr(nullptr)
{
	m_bstr = ::SysAllocString(psz);

	if (m_bstr == nullptr)
		throw std::bad_alloc();
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ComStr::~ComStr()
{
	Release();
}

////////////////////////////////////////////////////////////////////////////////
//! Free the string.

void ComStr::Release()
{
	if (m_bstr != nullptr)
	{
		::SysFreeString(m_bstr);

		m_bstr = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Take ownership of an external string.

void ComStr::Attach(BSTR bstr)
{
	m_bstr = bstr;
}

////////////////////////////////////////////////////////////////////////////////
//! Take external ownership of the string.

BSTR ComStr::Detach()
{
	BSTR bstr = m_bstr;
	m_bstr = nullptr;

	return bstr;
}

//namespace WCL
}
