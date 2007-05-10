////////////////////////////////////////////////////////////////////////////////
//! \file   ComException.cpp
//! \brief  The ComException class definition.
//! \author Chris Oldwood

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

namespace WCL
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor. The pszOperation parameter is used as the prefix for
//! the message and the error code is appended.

ComException::ComException(HRESULT hResult, const char* pszOperation)
	: CException(hResult)
	, m_hResult(hResult)
{
	m_strErrorText.Format("%s [0x%08X - %s]", pszOperation, hResult, CApp::FormatError(hResult));
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ComException::~ComException()
{
}

//namespace WCL
}
