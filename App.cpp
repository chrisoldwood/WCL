/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CApp class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <stdio.h>
#include <stdarg.h>

/******************************************************************************
**
** Linker directives.
**
*******************************************************************************
*/

#pragma comment(lib, "comctl32.lib")	// For COMCTL32.DLL support.

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

//The application object.
static CApp* pThis = NULL;

/******************************************************************************
** Method:		Default Constructor
**
** Description:	It just saves a copy of itself so that access to it can be 
**				obtained from anywhere.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CApp::CApp(CFrameWnd& rFrameWnd, CCmdControl& rCmdControl)
	: m_rMainWnd(rFrameWnd)
	, m_rCmdControl(rCmdControl)
	, m_hInstance(NULL)
	, m_iCmdShow(SW_SHOW)
{
	pThis = this;
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	Removes access to the application object.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CApp::~CApp()
{
	pThis = NULL;

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}

/******************************************************************************
** Method:		This()
**
** Description:	Get a pointer to the application object.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CApp* CApp::This()
{
	return pThis;
}

/******************************************************************************
** Method:		Open()
**
** Description:	Called by WinMain when the application is started.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CApp::Open()
{
	m_strTitle = "";

	// Initialise COMCTL32.DLL classes.
	INITCOMMONCONTROLSEX ComCtrls;

	ComCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	ComCtrls.dwICC  = ICC_DATE_CLASSES   | ICC_LISTVIEW_CLASSES
					| ICC_PROGRESS_CLASS | ICC_TAB_CLASSES;

	if (!InitCommonControlsEx(&ComCtrls))
	{
		AlertMsg("Failed to initialise COMCTL32.DLL");
		return false;
	}

	bool bOK = OnOpen();

	// Initialisation failed?
	if (!bOK)
		PostQuitMessage(0);

	return bOK;
}

/******************************************************************************
** Method:		Run()
**
** Description:	Called by WinMain to start the main processing.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

void CApp::Run()
{
	m_MainThread.Run();
}

/******************************************************************************
** Method:		Close()
**
** Description:	Called by WinMain just before terminating the application.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CApp::Close()
{
	OnClose();

	// Free strings.
	m_strTitle   = "";
	m_strCmdLine = "";
}

/******************************************************************************
** Method:		OnOpen()
**				OnClose()
**
** Description:	Default versions of the template methods called by the Open()
**				and Close() methods during application startup and shutdown.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CApp::OnOpen()
{
	return true;
}

bool CApp::OnClose()
{
	return true;
}

/******************************************************************************
** Methods:		AlertMsg()
**				NotifyMsg()
**				QueryMsg()
**				FatalMsg()
**
** Description:	Displays a message box with no parent window.
**
** Parameters:	pszMsg			The message format.
**				...				Variable number of arguments.
**
** Returns:		Result from MessageBox() if appropriate.
**
*******************************************************************************
*/

int CApp::AlertMsg(const char* pszMsg, ...) const
{
	int		nMsgLen = strlen(pszMsg);
	CString strMsg;

	strMsg.BufferSize(nMsgLen > 256 ? nMsgLen : 256);

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Form message.
	vsprintf((char*)(const char *)strMsg, pszMsg, args);
	
	return MessageBox(NULL, strMsg, m_strTitle, MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
}

int CApp::NotifyMsg(const char* pszMsg, ...) const
{
	int		nMsgLen = strlen(pszMsg);
	CString strMsg;

	strMsg.BufferSize(nMsgLen > 256 ? nMsgLen : 256);

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Form message.
	vsprintf((char*)(const char *)strMsg, pszMsg, args);
	
	return MessageBox(NULL, strMsg, m_strTitle, MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}

int CApp::QueryMsg(const char* pszMsg, ...) const
{
	int		nMsgLen = strlen(pszMsg);
	CString strMsg;

	strMsg.BufferSize(nMsgLen > 256 ? nMsgLen : 256);

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Form message.
	vsprintf((char*)(const char *)strMsg, pszMsg, args);
	
	return MessageBox(NULL, strMsg, m_strTitle, MB_YESNOCANCEL | MB_ICONQUESTION | MB_TASKMODAL);
}

int CApp::FatalMsg(const char* pszMsg, ...) const
{
	int		nMsgLen = strlen(pszMsg);
	CString strMsg;

	strMsg.BufferSize(nMsgLen > 256 ? nMsgLen : 256);

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Form message.
	vsprintf((char*)(const char *)strMsg, pszMsg, args);
	
	return MessageBox(NULL, strMsg, m_strTitle, MB_OK | MB_ICONSTOP | MB_TASKMODAL);
}
