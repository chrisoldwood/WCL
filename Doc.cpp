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
** Methods:		operator <<()
**				operator >>()
**
** Description:	Operators to read/write from/to a stream.
**
** Parameters:	rStream		The stream containg the document.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDoc::operator <<(CStream& rStream)
{
	ASSERT(false);
}

void CDoc::operator >>(CStream& rStream)
{
	ASSERT(false);
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

		*this << File;

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

		*this >> File;

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
