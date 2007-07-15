/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DOC.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDoc class definition.
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

CDoc::CDoc()
	: m_Path("Untitled")
{
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

CDoc::~CDoc()
{
}

/******************************************************************************
** Methods:		Read()
**				Write()
**
** Description:	Template Methods to read/write from/to a stream.
**
** Parameters:	rStream		The stream containg the document.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDoc::Read(WCL::IInputStream& /*rStream*/)
{
	ASSERT_FALSE();
}

void CDoc::Write(WCL::IOutputStream& /*rStream*/)
{
	ASSERT_FALSE();
}

/******************************************************************************
** Methods:		Load()
**				Save()
**
** Description:	Methods to control the loading and saving of a document within
**				a file specified by the path member.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDoc::Load()
{
	try
	{
		CFile File;

		// Open, read and close.
		File.Open(m_Path, GENERIC_READ);

		Read(File);

		File.Close();
	}
	catch(CFileException& rException)
	{
		// Notify user.
		CApp::This().m_rMainWnd.AlertMsg(rException.ErrorText());
		return false;
	}

	return true;
}

bool CDoc::Save()
{
	try
	{
		CFile File;

		// Open, write and close.
		File.Create(m_Path);

		Write(File);

		File.Close();
	}
	catch(CFileException& rException)
	{
		// Notify user.
		CApp::This().m_rMainWnd.AlertMsg(rException.ErrorText());
		return false;
	}

	return true;
}
