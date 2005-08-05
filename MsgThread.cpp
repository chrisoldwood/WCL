/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MSGTHREAD.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CMsgThread class definition.
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

CMsgThread::CMsgThread()
{
#ifdef _DEBUG
	memset(&m_oMsg, 0, sizeof(MSG));
#endif
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

CMsgThread::~CMsgThread()
{
	ASSERT(m_oMsgFilters.size() == 0);
}

/******************************************************************************
** Method:		Run.
**
** Description:	The main processing loop for the thread. It pulls messages out
**				out the message queue, passes them to any filters and if not
**				handled does the usual stuff.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgThread::Run()
{
#ifdef _DEBUG
	memset(&m_oMsg, 0, sizeof(MSG));
#endif

	// Process message queue until WM_QUIT.
	while (ProcessMsgQueue())
		WaitMessage();

#ifdef _DEBUG
	memset(&m_oMsg, 0, sizeof(MSG));
#endif
}

/******************************************************************************
** Method:		AddMsgFilter()
**
** Description:	Add the filter to the subscribers list.
**
** Parameters:	pFilter		The msg filter.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgThread::AddMsgFilter(IMsgFilter* pFilter)
{
	ASSERT(pFilter != NULL);
	ASSERT(std::find(m_oMsgFilters.begin(), m_oMsgFilters.end(), pFilter) == m_oMsgFilters.end());

	m_oMsgFilters.push_back(pFilter);
}

/******************************************************************************
** Method:		RemoveMsgFilter()
**
** Description:	Remove the filter from the subscribers list.
**
** Parameters:	pFilter		The msg filter.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgThread::RemoveMsgFilter(IMsgFilter* pFilter)
{
	ASSERT(std::find(m_oMsgFilters.begin(), m_oMsgFilters.end(), pFilter) != m_oMsgFilters.end());

	m_oMsgFilters.remove(pFilter);
}

/******************************************************************************
** Method:		ProcessMsgQueue()
**
** Description:	Processes any waiting messages.
**
** Parameters:	None.
**
** Returns:		false if WM_QUIT was seen, else true.
**
*******************************************************************************
*/

bool CMsgThread::ProcessMsgQueue()
{
	// Message waiting?
	while (PeekMessage(&m_oMsg, NULL, NULL, NULL, PM_NOREMOVE))
	{
		// Is WM_QUIT?
		if (!GetMessage(&m_oMsg, NULL, NULL, NULL))
		{
			// Put back on the queue.
			::PostQuitMessage(0);
			return false;
		}

		// Is standard message?
		if ( (m_oMsg.hwnd != NULL) || (m_oMsg.message < WM_USER) )
		{
			// Template shorthands.
			typedef CMsgFilters::const_iterator CIter;

			bool bProcessed = false;
			
			// Give message filters first crack at message.
			for (CIter oIter = m_oMsgFilters.begin(); ((oIter != m_oMsgFilters.end()) && (!bProcessed)); ++oIter)
				bProcessed = (*oIter)->ProcessMsg(m_oMsg);

			// Still not processed?
			if (!bProcessed)
			{
				TranslateMessage(&m_oMsg);
				DispatchMessage(&m_oMsg);
			}
		}
		// Is thread message.
		else
		{
			OnThreadMsg(m_oMsg.message, m_oMsg.wParam, m_oMsg.lParam);
		}
	}

	return true;
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

void CMsgThread::OnThreadMsg(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
}
