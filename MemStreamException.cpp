/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTREAMEXCEPTION.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMemStreamException class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

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

CMemStreamException::CMemStreamException(int eErrCode)
{
	m_nErrorCode = eErrCode;

	// Convert error to string.
	switch(eErrCode)
	{
		case E_OPEN_FAILED:
			m_strErrorText.Format("An error occured opening a memory stream");
			break;

		case E_CREATE_FAILED:
			m_strErrorText.Format("An error occured creating a memory stream");
			break;

		case E_READ_FAILED:
			m_strErrorText.Format("An error occured reading from a memory stream");
			break;

		case E_WRITE_FAILED:
			m_strErrorText.Format("An error occured writing to a memory stream");
			break;

		case E_SEEK_FAILED:
			m_strErrorText.Format("An error occured seeking to a memory stream position");
			break;

		// Shouldn't happen!
		default:
			ASSERT(false);
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

CMemStreamException::~CMemStreamException()
{
}
