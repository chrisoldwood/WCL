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
**				out the message queue and dispatches them.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMsgThread::Run()
{
	// Forever.
	for (;;)
	{
		MSG Msg;
	
		// Message waiting?
		if(PeekMessage(&Msg, NULL, NULL, NULL, PM_NOREMOVE))
		{
			// Is WM_QUIT?
			if (!GetMessage(&Msg, NULL, NULL, NULL))
				return;

			bool				bProcessed = false;
			CMsgFilter*			pFilter = NULL;
			CMsgFilters::CIter	Iter(m_MsgFilters);
			
			// Give message filters first crack at message.
			while ( ((pFilter = Iter.Next()) != NULL) && (!bProcessed) )
				bProcessed = pFilter->ProcessMsg(Msg);

			// Still not processed?
			if (!bProcessed)
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		}
		else
		{
			// Yield.
			WaitMessage();
		}
	}
}
