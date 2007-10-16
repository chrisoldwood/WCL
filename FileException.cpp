/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FILEEXCEPTION.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CFileException class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FileException.hpp"
#include "Path.hpp"

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

CFileException::CFileException(int eErrCode, const CPath& rPath)
{
	// Convert error to string.
	switch(eErrCode)
	{
		case E_OPEN_FAILED:
			m_strErrorText.Format("Failed to open file:\n\n%s", rPath);
			break;

		case E_CREATE_FAILED:
			m_strErrorText.Format("Failed to create file:\n\n%s", rPath);
			break;

		case E_READ_ONLY:
			m_strErrorText.Format("Failed to open file:\n\n%s\n\nThe file is read-only", rPath);
			break;

		case E_PATH_INVALID:
			m_strErrorText.Format("Failed to open file:\n\n%s\n\nThe file does not exist", rPath);
			break;

		case E_FORMAT_INVALID:
			m_strErrorText.Format("The file format is incorrect for:\n\n%s", rPath);
			break;

		case E_VERSION_INVALID:
			m_strErrorText.Format("The file version is unsupported for:\n\n%s", rPath);
			break;

		case E_READ_FAILED:
			m_strErrorText.Format("An error occured reading from:\n\n%s", rPath);
			break;

		case E_WRITE_FAILED:
			m_strErrorText.Format("An error occured writing to:\n\n%s", rPath);
			break;

		case E_SEEK_FAILED:
			m_strErrorText.Format("An error occured seeking in:\n\n%s", rPath);
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

CFileException::~CFileException()
{
}
