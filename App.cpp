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

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

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

// The application object.
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
	, m_iCmdShow(SW_SHOW)
	, m_pComCtl32(NULL)
{
	m_pComCtl32 = new CComCtl32();

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

	delete m_pComCtl32;

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}

/******************************************************************************
** Method:		This()
**
** Description:	Get the application object.
**
** Parameters:	None.
**
** Returns:		The app object.
**
*******************************************************************************
*/

CApp& CApp::This()
{
	ASSERT(pThis != NULL);

	return *pThis;
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
	// Default title to app filename.ext.
	m_strTitle = CPath::Application().FileName().ToUpper();

	const DWORD dwMinMajor = 4;
	const DWORD dwMinMinor = 71;

	DWORD dwMajor, dwMinor;

	// Get COMCTL32.DLL version.
	if (!m_pComCtl32->IsLoaded() || !m_pComCtl32->GetVersion(dwMajor, dwMinor))
	{
		FatalMsg("This application requires at least v%u.%u of COMCTL32.DLL.", dwMinMajor, dwMinMinor);
		return false;
	}

	// Check COMCTL32.DLL version.
	if ( (dwMajor < dwMinMajor) || ((dwMajor == dwMinMajor) && (dwMinor < dwMinMinor)) )
	{
		FatalMsg("This application requires at least v%u.%u of COMCTL32.DLL.", dwMinMajor, dwMinMinor);
		return false;
	}

	DWORD dwICC = ICC_DATE_CLASSES | ICC_LISTVIEW_CLASSES | ICC_PROGRESS_CLASS | ICC_TAB_CLASSES;

	// Initialise COMCTL32.DLL window classes.
	if (!m_pComCtl32->Initialise(dwICC))
	{
		FatalMsg("Failed to initialise COMCTL32.DLL");
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
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Format message.
	strMsg.FormatEx(pszMsg, args);
	
	return MessageBox(m_rMainWnd.Handle(), strMsg, m_strTitle, MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
}

int CApp::NotifyMsg(const char* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Format message.
	strMsg.FormatEx(pszMsg, args);
	
	return MessageBox(m_rMainWnd.Handle(), strMsg, m_strTitle, MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}

int CApp::QueryMsg(const char* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Format message.
	strMsg.FormatEx(pszMsg, args);
	
	return MessageBox(m_rMainWnd.Handle(), strMsg, m_strTitle, MB_YESNOCANCEL | MB_ICONQUESTION | MB_TASKMODAL);
}

int CApp::FatalMsg(const char* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);
	
	// Format message.
	strMsg.FormatEx(pszMsg, args);
	
	return MessageBox(m_rMainWnd.Handle(), strMsg, m_strTitle, MB_OK | MB_ICONSTOP | MB_TASKMODAL);
}

/******************************************************************************
** Method:		FormatError()
**
** Description:	Converts a system error code to a string.
**
** Parameters:	dwError		The error code.
**
** Returns:		The error as string.
**
*******************************************************************************
*/

CString CApp::FormatError(DWORD dwError)
{
	CString strError;
	char*   pszError;

	// Format string using default language.
	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&pszError, 0, NULL);

	// Copy message and free buffer.
	strError = pszError;
	::LocalFree(pszError);

	// Trim excess whitespace.
	strError.Trim();

	return strError;
}

/******************************************************************************
** Method:		TimerProc()
**
** Description:	The timer callback function.
**
** Parameters:	See TimerProc.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CALLBACK CApp::TimerProc(HWND /*hWnd*/, UINT /*uMsg*/, UINT nTimerID, DWORD /*dwTime*/)
{
	ASSERT(pThis != NULL);

	// Forward to instance method.
	pThis->OnTimer(nTimerID);
}

/******************************************************************************
** Method:		OnTimer()
**
** Description:	Default timer event handler.
**
** Parameters:	nTimerID	The timer ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CApp::OnTimer(uint /*nTimerID*/)
{
}

/******************************************************************************
** Method:		OnThreadMsg()
**
** Description:	Default handler for main thread messages.
**
** Parameters:	See PostThreadMessage().
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CApp::OnThreadMsg(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
}
