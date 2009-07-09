/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRCVTEXCEPTION.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStrCvtException class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StrCvtException.hpp"
#include <Core/StringUtils.hpp>

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
{
	// Convert error to string.
	switch(eErrCode)
	{
		case E_INVALID_FORMAT:
			m_strDetails = TXT("Invalid format");
			break;

		case E_INVALID_RANGE:
			m_strDetails = TXT("Number out of range");
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

CStrCvtException::~CStrCvtException() throw()
{
}
