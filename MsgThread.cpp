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
** Method:		ProcessMsgQueue.
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

		bool				bProcessed = false;
		CMsgFilter*			pFilter = NULL;
		CMsgFilters::CIter	Iter(m_MsgFilters);
		
		// Give message filters first crack at message.
		while ( ((pFilter = Iter.Next()) != NULL) && (!bProcessed) )
			bProcessed = pFilter->ProcessMsg(m_oMsg);

		// Still not processed?
		if (!bProcessed)
		{
			TranslateMessage(&m_oMsg);
			DispatchMessage(&m_oMsg);
		}
	}

	return true;
}
