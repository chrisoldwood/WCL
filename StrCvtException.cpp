/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRCVTEXCEPTION.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStrCvtException class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStrCvtException::CStrCvtException(int eErrCode)
	: CException(eErrCode)
{
	// Convert error to string.
	switch(eErrCode)
	{
		case E_INVALID_FORMAT:
			m_strErrorText = "Invalid format";
			break;

		case E_INVALID_RANGE:
			m_strErrorText = "Number out of range";
			break;

		// Shouldn't happen!
		default:
			ASSERT_FALSE();
			break;
	}
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStrCvtException::~CStrCvtException()
{
}
