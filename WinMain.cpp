/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WINMAIN.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	Application entry point.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Function: 	WinMain()
**
** Description:	This is the entry point to the Windows app.
**
** Parameters:	hCurrInst	The current instance.
**				hPrevInst	The previous instance (NULL if none).
**				lpszCmdLine	The command line.
**				iCmdShow	The initial state of the window.
**
** Returns:		TRUE		For a premature exit.
**				FALSE		For a normal exit.
**
*******************************************************************************
*/

extern "C" int PASCAL WinMain(HINSTANCE hCurrInst, HINSTANCE hPrevInst, 
								LPSTR lpszCmdLine, int iCmdShow)
{
	// Get application object.
	CApp* pApp = CApp::This();
	ASSERT(pApp);

	// Initialise members.
	pApp->m_hInstance  = hCurrInst;
	pApp->m_strCmdLine = lpszCmdLine;	
	pApp->m_iCmdShow   = iCmdShow;

	// Register custom controls.

	// Open, run and close the app...
	pApp->Open();
	pApp->Run();
	pApp->Close();

	return FALSE;
}
