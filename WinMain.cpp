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

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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

extern "C" int WINAPI WinMain(HINSTANCE hCurrInst, HINSTANCE hPrevInst, 
								LPSTR lpszCmdLine, int iCmdShow)
{
	// Get application object.
	CApp& oApp = CApp::This();

	// Initialise members.
	oApp.m_Module.m_hInstance = hCurrInst;
	oApp.m_strCmdLine         = lpszCmdLine;	
	oApp.m_iCmdShow           = iCmdShow;

	// Open, run and close the app...
	if (oApp.Open())
		oApp.Run();

	oApp.Close();

	return FALSE;
}
