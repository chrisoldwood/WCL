/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIAPP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSDIApp class definition.
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

CSDIApp::CSDIApp(CSDIFrame& rFrameWnd, CSDICmds& rCmdControl)
	: CApp(rFrameWnd, rCmdControl)
	, m_pDoc(NULL)
	, m_pView(NULL)
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

CSDIApp::~CSDIApp()
{
	ASSERT(m_pDoc  == NULL);
	ASSERT(m_pView == NULL);
}

/******************************************************************************
** Method:		OnOpen()
**
** Description:	Initialises the application.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDIApp::OnOpen()
{
	// File passed on the command line?
	if (m_strCmdLine.Length() > 0)
	{
		CPath strPath = m_strCmdLine;

		// Delete leading ", if one.
		if (strPath[0] == '"')
			strPath.Delete(0);

		int nLength = strPath.Length();

		// Delete trailing ", if one.
		if ( (nLength > 0) && (strPath[nLength-1] == '"') )
			strPath.Delete(nLength-1);

		static_cast<CSDICmds&>(m_rCmdControl).OpenFile(strPath);

	}

	return true;
}

/******************************************************************************
** Method:		OnClose()
**
** Description:	Terminate the application.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDIApp::OnClose()
{
	return true;
}

