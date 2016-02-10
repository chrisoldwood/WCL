/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PROPERTYPAGE.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CPropertyPage class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "PropertyPage.hpp"
#include <prsht.h>

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

CPropertyPage::CPropertyPage(uint nRscID)
	: CDialog(nRscID)
{
	// Property pages are always modeless.
	m_bModal = false;
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

CPropertyPage::~CPropertyPage()
{
}

/******************************************************************************
** Function:	PropPageProc()
**
** Description:	This is the real dialog procedure used for all property pages.
**				It gets the object associated with the handle and calls the
**				real message processing method.
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		TRUE or FALSE based on the message.
**
*******************************************************************************
*/

WCL::DlgResult DIALOGPROC CPropertyPage::PropPageProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	CPropertyPage* pDialog;

	// Get the window object.
	pDialog = static_cast<CPropertyPage*>(CWnd::s_WndMap.Find(hWnd));

	// Do we have a mapping?
	if (pDialog == nullptr)
	{
		// Time to initialise?
		if (iMsg == WM_INITDIALOG)
		{
			// lParam contains property page info.
			PROPSHEETPAGE* pPage = reinterpret_cast<PROPSHEETPAGE*>(lParam);

			// Get object from property page info.
			pDialog = reinterpret_cast<CPropertyPage*>(pPage->lParam);

			//
			// This function can be called recursively so we need to use
			// the program stack to hold the return values for each
			// message whilst it is being precessed.
			//

			// Store the return values for this message.
			BOOL     bMsgHandled = false;
			LRESULT  lMsgResult  = 0;

			// Push the existing messages' return values onto the stack.
			BOOL*	 pbMsgHandled = pDialog->MsgHandledBuffer(&bMsgHandled);
			LRESULT* plMsgResult  = pDialog->MsgResultBuffer (&lMsgResult);

			// Save handle/result.
			pDialog->m_hWnd = hWnd;
			pDialog->MsgHandled(true);
			pDialog->MsgResult (0);

			// Setup Window mapping.
			CWnd::s_WndMap.Add(*pDialog);

			// Initialise child controls.
			pDialog->InitControls();
			pDialog->InitGravityTable();

			// Now call initialise method.
			pDialog->OnCreate(pDialog->ClientRect());

			// Pop the old messages' return values back off the stack.
			pDialog->MsgHandledBuffer(pbMsgHandled);
			pDialog->MsgResultBuffer (plMsgResult);

			return bMsgHandled;
		}
		else
		{
			// Ignore it.
			return FALSE;
		}
	}

	//
	// This function can be called recursively so we need to use
	// the program stack to hold the return values for each
	// message whilst it is being precessed.
	//

	// Store the return values for this message.
	BOOL     bMsgHandled = false;
	LRESULT  lMsgResult  = 0;

	// Push the existing messages' return values onto the stack.
	BOOL*	 pbMsgHandled = pDialog->MsgHandledBuffer(&bMsgHandled);
	LRESULT* plMsgResult  = pDialog->MsgResultBuffer (&lMsgResult);

	// Call real message handler.
	pDialog->WndProc(hWnd, iMsg, wParam, lParam);

	// Pop the old messages' return values back off the stack.
	pDialog->MsgHandledBuffer(pbMsgHandled);
	pDialog->MsgResultBuffer (plMsgResult);

	// Set the return value.
	::SetWindowLongPtr(hWnd, DWLP_MSGRESULT, lMsgResult);

	// Return if msg was handled.
	return bMsgHandled;
}

/******************************************************************************
** Method:		OnCtrlMsg()
**
** Description:	A WM_NOTIFY event has been sent, possibly from the property
**				sheet.
**
** Parameters:	rMsgHdr		The message.
**
** Returns:		Depends on the message.
**
*******************************************************************************
*/

LRESULT CPropertyPage::OnCtrlMsg(NMHDR& rMsgHdr)
{
	// Is a property sheet message?
	switch (rMsgHdr.code)
	{
		case PSN_SETACTIVE:
			OnActivate(true);
			return 0;

		case PSN_KILLACTIVE:
			if (!OnValidate())
				return TRUE;

			OnActivate(false);
			return 0;

		case PSN_APPLY:
			if (!OnOk())
				return PSNRET_INVALID;

			return PSNRET_NOERROR;

		case PSN_QUERYCANCEL:
			OnCancel();
			return 0;

		default:
			break;
	}

	// Pass to base class.
	return CDialog::OnCtrlMsg(rMsgHdr);
}

/******************************************************************************
** Method:		OnValidate()
**
** Description:	The page should validate the data.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPropertyPage::OnValidate()
{
	return true;
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	The page should save the data in the controls.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPropertyPage::OnOk()
{
	return true;
}
