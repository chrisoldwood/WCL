/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APP.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CApp class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "App.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <commctrl.h>
#include "FrameWnd.hpp"

#ifdef _MSC_VER
// Linker directives.
// NB: Required for building with VC++ Express.
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "advapi32")
#pragma comment(lib, "comctl32")
#pragma comment(lib, "ole32")
#endif

/******************************************************************************
**
** Class members.
**
*******************************************************************************
*/

//! The singleton EXE component object.
CApp* CApp::g_pThis = NULL;

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

CApp::CApp(CFrameWnd& rFrameWnd, WCL::ICmdController& controller)
	: m_strTitle()
	, m_rMainWnd(rFrameWnd)
	, m_controller(controller)
	, m_Module()
	, m_MainThread()
	, m_strCmdLine()
	, m_iCmdShow(SW_SHOW)
	, m_oComCtl32()
	, m_DefaultFont()
	, m_MidToneBrush()
	, m_LightPen(), m_LightestPen()
	, m_DarkPen(),  m_DarkestPen()
{
	ASSERT(g_pThis == nullptr);

	g_pThis = this;

	// Report memory leaks.
	Core::enableLeakReporting(true);
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
	ASSERT(g_pThis == this);

	g_pThis = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//! Check if the app singleton is valid.

bool CApp::IsValid()
{
	return (g_pThis != nullptr);
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
	ASSERT(g_pThis != nullptr);

	return *g_pThis;
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
	// If not set yet, default title to application filename.
	if (m_strTitle.Empty())
		m_strTitle = CPath::Application().FileName().ToUpper();

	const DWORD dwMinMajor = 4;
	const DWORD dwMinMinor = 71;

	DWORD dwMajor, dwMinor;

	// Get COMCTL32.DLL version.
	if (!m_oComCtl32.IsLoaded() || !m_oComCtl32.GetVersion(dwMajor, dwMinor))
	{
		FatalMsg(TXT("This application requires at least v%u.%u of COMCTL32.DLL."), dwMinMajor, dwMinMinor);
		return false;
	}

	// Check COMCTL32.DLL version.
	if ( (dwMajor < dwMinMajor) || ((dwMajor == dwMinMajor) && (dwMinor < dwMinMinor)) )
	{
		FatalMsg(TXT("This application requires at least v%u.%u of COMCTL32.DLL."), dwMinMajor, dwMinMinor);
		return false;
	}

	DWORD dwICC = ICC_DATE_CLASSES | ICC_LISTVIEW_CLASSES | ICC_PROGRESS_CLASS | ICC_TAB_CLASSES;

	// Initialise COMCTL32.DLL window classes.
	if (!m_oComCtl32.Initialise(dwICC))
	{
		FatalMsg(TXT("Failed to initialise COMCTL32.DLL"));
		return false;
	}

	// Call application method.
	if (!OnOpen())
		return false;

	return true;
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

int CApp::AlertMsg(const tchar* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);

	// Format message.
	strMsg.FormatEx(pszMsg, args);

	return MessageBox(m_rMainWnd.Handle(), strMsg, m_strTitle, MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
}

int CApp::NotifyMsg(const tchar* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);

	// Format message.
	strMsg.FormatEx(pszMsg, args);

	return MessageBox(m_rMainWnd.Handle(), strMsg, m_strTitle, MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}

int CApp::QueryMsg(const tchar* pszMsg, ...) const
{
	CString strMsg;

	// Setup arguments.
	va_list	args;
	va_start(args, pszMsg);

	// Format message.
	strMsg.FormatEx(pszMsg, args);

	return MessageBox(m_rMainWnd.Handle(), strMsg, m_strTitle, MB_YESNOCANCEL | MB_ICONQUESTION | MB_TASKMODAL);
}

int CApp::FatalMsg(const tchar* pszMsg, ...) const
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

void CALLBACK CApp::TimerProc(HWND /*hWnd*/, UINT /*uMsg*/, WCL::TimerID nTimerID, DWORD /*dwTime*/)
{
	ASSERT(g_pThis != nullptr);

	// Forward to instance method.
	g_pThis->OnTimer(nTimerID);
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

void CApp::OnTimer(WCL::TimerID /*nTimerID*/)
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
