/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DIALOG.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CDialog class methods.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Dialog.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "Module.hpp"
#include "Exception.hpp"
#include "CtrlWnd.hpp"
#include "DC.hpp"

/******************************************************************************
**
** Local variables.
**
*******************************************************************************
*/

// Size of sizing grip handle.
const int SIZE_GRIP_SIZE = 12;

/******************************************************************************
** Method:		Default constructor.
**
** Description:	.
**
** Parameters:	iRscID		The dialog template resource ID.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CDialog::CDialog(uint iRscID)
	: CMsgWnd()
	, m_iRscID(iRscID)
	, m_bModal()
	, m_vControls()
	, m_vGravities()
	, m_StartSize()
	, m_pParentWnd(nullptr)
	, m_bNoSizeGrip(false)
	, m_rcOldGrip(0, 0, 0, 0)
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

CDialog::~CDialog()
{
}

/******************************************************************************
** Method:		RunModless()
**
** Description:	Create the dialog as a modeless dialog and display. This method
**				returns straight away as the dialog runs in parallel.
**
** Parameters:	rParent		The dialogs' parent window.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDialog::RunModeless(CWnd& rParent)
{
	// Initalise members.
	m_bModal     = false;
	m_pParentWnd = &rParent;

	ASSERT(rParent.Handle());
	ASSERT(CModule::This().Handle());
	ASSERT(m_iRscID);

	// Create it.
	HWND hWnd = CreateDialogParam(CModule::This().Handle(), MAKEINTRESOURCE(m_iRscID),
									rParent.Handle(), DlgProc, reinterpret_cast<LPARAM>(this));

	ASSERT(hWnd != NULL);

	// If a child dialog, turn off size grip.
	if (WindowStyle() & WS_CHILD)
		m_bNoSizeGrip = true;

	// Okay?
	return (hWnd != NULL);
}

/******************************************************************************
** Method:		RunModal()
**
** Description:	Create the dialog as a modal dialog and display. This method
**				does not return until the dialog is closed.
**
** Parameters:	rParent		The dialogs' parent window.
**
** Returns:		IDOK or IDCANCEL	If closed by user.
**				iReturn == -1		On error.
**
*******************************************************************************
*/

int CDialog::RunModal(CWnd& rParent)
{
	// Initalise members.
	m_bModal     = true;
	m_pParentWnd = &rParent;

	ASSERT((rParent.Handle() != NULL) || (&rParent == &CWnd::g_oDesktop));
	ASSERT(CModule::This().Handle());
	ASSERT(m_iRscID);

	// Create it.
	LRESULT iReturn = DialogBoxParam(CModule::This().Handle(), MAKEINTRESOURCE(m_iRscID),
									rParent.Handle(), DlgProc, reinterpret_cast<LPARAM>(this));

	ASSERT(iReturn != -1);

    // Return
	return static_cast<int>(iReturn);
}

/******************************************************************************
** Method:		EndDialog()
**
** Description:	Close the dialog (Only for modal dialogs).
**
** Parameters:	nResult		The result code to return to RunModal().
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::EndDialog(int nResult)
{
	ASSERT(m_bModal);

	::EndDialog(m_hWnd, nResult);
}

#if (__GNUC__ >= 8) // GCC 8+
// error: format '%hs' expects argument of type 'short int*', but argument 3 has type 'const char*' [-Werror=format=]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif

/******************************************************************************
** Function:	DialogProc()
**
** Description:	This is the real dialog procedure used for all dialogs. It
**				gets the object associated with the handle and calls the real
**				message processing method.
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		TRUE or FALSE based on the message.
**
*******************************************************************************
*/

WCL::DlgResult DIALOGPROC CDialog::DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Store the return values for this message.
	BOOL     bMsgHandled = false;
	LRESULT  lMsgResult  = 0;

	try
	{
		CDialog* pDialog;

		// Get the window object.
		pDialog = static_cast<CDialog*>(CWnd::s_WndMap.Find(hWnd));

		// Do we have a mapping?
		if (pDialog == nullptr)
		{
			// Time to initialise?
			// NB: We will receive other messages first.
			if (iMsg == WM_INITDIALOG)
			{
				// Get object from LPARAM.
				pDialog = reinterpret_cast<CDialog*>(lParam);

				//
				// This function can be called recursively so we need to use
				// the program stack to hold the return values for each
				// message whilst it is being precessed.
				//

				// Push the existing messages' return values onto the stack.
				BOOL*	 pbMsgHandled = pDialog->MsgHandledBuffer(&bMsgHandled);
				LRESULT* plMsgResult  = pDialog->MsgResultBuffer (&lMsgResult);

				// Save handle/result.
				pDialog->m_hWnd = hWnd;
				pDialog->MsgHandled(true);
				pDialog->MsgResult (0);

				// Setup Window mapping.
				CWnd::s_WndMap.Add(*pDialog);

				// Centre only if modal.
				if (pDialog->m_bModal)
					pDialog->Centre();

				// Initialise child controls.
				pDialog->InitControls();
				pDialog->InitGravityTable();

				// Now call initialise method.
				pDialog->OnCreate(pDialog->ClientRect());

				// Pop the old messages' return values back off the stack.
				pDialog->MsgHandledBuffer(pbMsgHandled);
				pDialog->MsgResultBuffer (plMsgResult);
			}
		}
		else
		{
			//
			// This function can be called recursively so we need to use
			// the program stack to hold the return values for each
			// message whilst it is being precessed.
			//

			// Push the existing messages' return values onto the stack.
			BOOL*	 pbMsgHandled = pDialog->MsgHandledBuffer(&bMsgHandled);
			LRESULT* plMsgResult  = pDialog->MsgResultBuffer (&lMsgResult);

			// Call real message handler.
			pDialog->WndProc(hWnd, iMsg, wParam, lParam);

			// Pop the old messages' return values back off the stack.
			pDialog->MsgHandledBuffer(pbMsgHandled);
			pDialog->MsgResultBuffer (plMsgResult);
		}
	}
	catch (const Core::Exception& e)
	{
		WCL::ReportUnhandledException(	TXT("Unexpected exception caught in DlgProc()\n\n")
										TXT("Message: H=0x%p M=0x%08X W=0x%08X L=0x%08lX\n\n%s"),
										hWnd, iMsg, wParam, lParam, e.twhat());
	}
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException(	TXT("Unexpected exception caught in DlgProc()\n\n")
										TXT("Message: H=0x%p M=0x%08X W=0x%08X L=0x%08lX\n\n%hs"),
										hWnd, iMsg, wParam, lParam, e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException(	TXT("Unexpected unknown exception caught in DlgProc()\n\n")
										TXT("Message: H=0x%p M=0x%08X W=0x%08X L=0x%08lX"),
										hWnd, iMsg, wParam, lParam);
	}

	// Set the return value.
	::SetWindowLongPtr(hWnd, DWLP_MSGRESULT, lMsgResult);

	// Return if msg was handled.
	return bMsgHandled;
}

#if (__GNUC__ >= 8) // GCC 8+
#pragma GCC diagnostic pop
#endif

/******************************************************************************
** Method:		DialogProc()
**
** Description:	This is the virtual dialog procedure that processes all the
**				messages and calls the appropriate virtual function. It also
**				does some default processing.
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CDialog::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Child control message.
		case WM_COMMAND:
			// Running modal?
			if (m_bModal)
			{
				// Check for termination.
				if ( (wParam == IDOK) && (OnOk()) )
				{
					EndDialog(IDOK);
					break;
				}
				else if ( (wParam == IDCANCEL) && (OnCancel()) )
				{
					EndDialog(IDCANCEL);
					break;
				}
			}
			return CMsgWnd::WndProc(hWnd, iMsg, wParam, lParam);

		// Call the default handler.
		default:
			return CMsgWnd::WndProc(hWnd, iMsg, wParam, lParam);
	}

	MsgHandled(true);
	MsgResult (0);

	return 0;
}

/******************************************************************************
** Method:		DefaultWndProc()
**
** Description:	This is the handler for all non-handled messages. It calls
**				DefWindowProc().
**
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CDialog::DefaultWndProc(HWND /*hWnd*/, UINT /*iMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	// Message not processed.
	MsgHandled(false);
	MsgResult (0);

	return 0;
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Forwards the create call to the "normal" dialog initialisation
**				method. The framework will override this to handle special
**				initialisation that needs to be done before the derived class'.
**
** Parameters:	rcClient	The client area of the dialog.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::OnCreate(const CRect& /*rcClient*/)
{
	// Forward to normal dialog init method.
	OnInitDialog();
}

/******************************************************************************
** Method:		OnInitDialog()
**
** Description:	Default implementation of dialog initialisation method.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::OnInitDialog()
{
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	The OK button was pressed. Ask if the dialog can close.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDialog::OnOk()
{
	return true;
}

/******************************************************************************
** Method:		OnCancel()
**
** Description:	The Cancel button was pressed. Ask if the dialog can close.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CDialog::OnCancel()
{
	return true;
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	Resize the controls if a gravity table has been setup.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::OnResize(int /*iFlag*/, const CSize& rNewSize)
{
	// No controls to reposition?
	if (m_vGravities.empty())
		return;

	// Allocate DWP handle.
	HDWP hDWP = ::BeginDeferWindowPos(static_cast<int>(m_vGravities.size()));

	ASSERT(hDWP != NULL);

	// Resize all controls.
	for (Gravities::const_iterator it = m_vGravities.begin(); it != m_vGravities.end(); ++it)
	{
		CRect rcNewPos;

		// Process controls' left edge.
		if (it->eLeft == LEFT_EDGE)
		{
			rcNewPos.left = it->rcStart.left;
		}
		else // it->eLeft == RIGHT_EDGE
		{
			rcNewPos.left = rNewSize.cx - (m_StartSize.cx - it->rcStart.left);
		}

		// Process controls' top edge.
		if (it->eTop == TOP_EDGE)
		{
			rcNewPos.top = it->rcStart.top;
		}
		else // it->eTop == BOTTOM_EDGE
		{
			rcNewPos.top = rNewSize.cy - (m_StartSize.cy - it->rcStart.top);
		}

		// Process controls' right edge.
		if (it->eRight == LEFT_EDGE)
		{
			rcNewPos.right = it->rcStart.right;
		}
		else // it->eRight == RIGHT_EDGE
		{
			rcNewPos.right = rNewSize.cx - (m_StartSize.cx - it->rcStart.right);
		}

		// Process controls' bottom edge.
		if (it->eBottom == TOP_EDGE)
		{
			rcNewPos.bottom = it->rcStart.bottom;
		}
		else // it->eBottom == BOTTOM_EDGE
		{
			rcNewPos.bottom = rNewSize.cy - (m_StartSize.cy - it->rcStart.bottom);
		}

		// Resize the window.
		::DeferWindowPos(hDWP, it->hWnd, NULL, rcNewPos.left, rcNewPos.top,
							rcNewPos.Width(), rcNewPos.Height(), SWP_NOZORDER | SWP_NOCOPYBITS);
	}

	::EndDeferWindowPos(hDWP);

	// Repaint sizing grip.
	Invalidate(CRect(CPoint(rNewSize.cx-SIZE_GRIP_SIZE, rNewSize.cy-SIZE_GRIP_SIZE), CSize(SIZE_GRIP_SIZE+1, SIZE_GRIP_SIZE+1)), true);
	Invalidate(&m_rcOldGrip, true);
}

/******************************************************************************
** Method:		ControlTable()
**
** Description:	Set up the control table.
**
** Parameters:	pCtrlTable	The control table.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::ControlTable(CTRL* pCtrlTable)
{
	ASSERT(m_vControls.empty());
	ASSERT(pCtrlTable != nullptr);

	size_t nCount = 0;

	// Count the number of controls.
	for (CTRL* pCtrl = pCtrlTable; pCtrl->iID; ++pCtrl)
		++nCount;

	m_vControls.resize(nCount);

	// Copy the table.
	std::copy(pCtrlTable, pCtrlTable+nCount, m_vControls.begin());
}

/******************************************************************************
** Method:		InitControls()
**
** Description:	Iterate over the control table and setup their ID and window
**				handles.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::InitControls()
{
	// Attach the window handles to the controls.
	for (Controls::const_iterator it = m_vControls.begin(); it != m_vControls.end(); ++it)
	    it->pWnd->Create(*this, it->iID, CtrlHandle(it->iID));
}

/******************************************************************************
** Method:		GravityTable()
**
** Description:	Set up the control gravity table.
**
** Parameters:	pGravTable	The control gravity table.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::GravityTable(CTLGRAVITY* pGravTable)
{
	ASSERT(m_vGravities.empty());
	ASSERT(pGravTable != nullptr);

	size_t nCount = 0;

	// Count the number of entries.
	for (CTLGRAVITY* pGrav = pGravTable; pGrav->iID; ++pGrav)
		++nCount;

	m_vGravities.resize(nCount);

	// Copy the table.
	std::copy(pGravTable, pGravTable+nCount, m_vGravities.begin());
}

/******************************************************************************
** Method:		InitGravityTable()
**
** Description:	Iterate over the control gravity table and setup their inital
**				rects.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::InitGravityTable()
{
	// No controls to initialise?
	if (m_vGravities.empty())
		return;

	// Get the dialogs initial size.
	m_StartSize = ClientRect().Size();

	// For each moveable control...
	for (Gravities::iterator it = m_vGravities.begin(); it != m_vGravities.end(); ++it)
	{
		// Get the controls window handle.
		it->hWnd = ::GetDlgItem(m_hWnd, it->iID);
		ASSERT(it->hWnd != NULL);

		// Get the controls starting position.
		::GetWindowRect(it->hWnd, &it->rcStart);
		::MapWindowPoints(NULL, m_hWnd, reinterpret_cast<LPPOINT>(&it->rcStart), 2);
	}
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the sizing grip, if one enabled.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::OnPaint(CDC& rDC)
{
	// Not resizable OR size grip disabled?
	if (m_vGravities.empty() || m_bNoSizeGrip)
		return;

	// Get window dimensions.
	CRect rcClient = ClientRect();

	// Get bottom right co-ordinates.
	CPoint ptCorner(rcClient.right-1, rcClient.bottom-1);

	// Create pens.
	CPen oDarkPen (PS_SOLID, 0, ::GetSysColor(COLOR_BTNSHADOW));
	CPen oLightPen(PS_SOLID, 0, ::GetSysColor(COLOR_BTNHIGHLIGHT));
	CPen oFacePen (PS_SOLID, 0, ::GetSysColor(COLOR_BTNFACE));

	// For all lines.
	for (int i = 0; i < 12; ++i)
	{
		// Select the required pen.
		if ((i % 4) == 3)
			rDC.Select(oLightPen);
		else if ( ((i % 4) == 1) || ((i % 4) == 2) )
			rDC.Select(oDarkPen);
		else
			rDC.Select(oFacePen);

		// Draw the line.
		rDC.Line(ptCorner.x-i-1, ptCorner.y, ptCorner.x, ptCorner.y-i-1);
	}

	// Save grip position for later.
	m_rcOldGrip = CRect(CPoint(ptCorner.x-12, ptCorner.y-12), CSize(13, 13));

#ifdef _DEBUG
	// Passify BoundsChecker.
	rDC.Select(CPen(NULL_PEN));
#endif
}

/******************************************************************************
** Method:		OnHitTest()
**
** Description:	Checks if the mouse is on the sizing grip.
**
** Parameters:	ptCursor	The mouse position in screen coordinates.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CDialog::OnHitTest(const CPoint& ptCursor)
{
	// Resizable AND size grip enabled?
	if (!m_vGravities.empty() && !m_bNoSizeGrip)
	{
		CPoint ptClient = ptCursor;

		// Convert mouse coordinates to client.
		::ScreenToClient(m_hWnd, &ptClient);

		// Is in sizing grip rect?
		if (ptClient.IsIn(m_rcOldGrip))
		{
			MsgHandled(true);
			MsgResult (HTBOTTOMRIGHT);
			return;
		}
	}

	// Handle in base class.
	CMsgWnd::OnHitTest(ptCursor);
}
