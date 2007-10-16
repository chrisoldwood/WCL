/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MAINTHREAD.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMainThread class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "MainThread.hpp"
#include "App.hpp"

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

CMainThread::CMainThread()
{
	m_hThread = NULL;
	m_dwID    = ::GetCurrentThreadId();
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

CMainThread::~CMainThread()
{
}

/******************************************************************************
** Method:		Run.
**
** Description:	The main processing loop for the thread.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMainThread::Run()
{
	// Forward to base class.
	CMsgThread::Run();
}

/******************************************************************************
** Method:		OnThreadMsg()
**
** Description:	Message handler for general thread messages.
**
** Parameters:	Standard thread message parameters.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMainThread::OnThreadMsg(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	// Forward to Application object.
	CApp::This().OnThreadMsg(nMsg, wParam, lParam);
}
