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
	, m_pCtrlTable(NULL)
	, m_pGravTable(NULL)
	, m_pParentWnd(NULL)
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
	// Free control table.
	if (m_pCtrlTable)
		delete[] m_pCtrlTable;

	// Free gravity table.
	if (m_pGravTable)
		delete[] m_pGravTable;
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
									rParent.Handle(), (DLGPROC)DlgProc, (LPARAM)this);

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
	int iReturn = DialogBoxParam(CModule::This().Handle(), MAKEINTRESOURCE(m_iRscID),
									rParent.Handle(), (DLGPROC)DlgProc, (LPARAM)this);

	ASSERT(iReturn != -1);
    
    // Return 
	return iReturn;
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

BOOL DIALOGPROC DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Store the return values for this message.
	BOOL     bMsgHandled = false;
	LRESULT  lMsgResult  = 0;

	try
	{
		CDialog* pDialog;
		
		// Get the window object.
		pDialog = (CDialog*) CWnd::s_WndMap.Find(hWnd);

		// Do we have a mapping?
		if (pDialog == nullptr)
		{
			// Time to initialise?
			// NB: We will receive other messages first.
			if (iMsg == WM_INITDIALOG)
			{
				// Get object from LPARAM.
				pDialog = (CDialog*)lParam;

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
	catch (const std::exception& e)
	{
		WCL::ReportUnhandledException("Unexpected exception caught in DlgProc()\n\n"
										"Message: H=0x%p M=0x%08X W=0x%08X L=0x%08X\n\n%s",
										hWnd, iMsg, wParam, lParam, e.what());
	}
	catch (...)
	{
		WCL::ReportUnhandledException("Unexpected unknown exception caught in DlgProc()\n\n"
										"Message: H=0x%p M=0x%08X W=0x%08X L=0x%08X",
										hWnd, iMsg, wParam, lParam);
	}

	// Set the return value.
	::SetWindowLong(hWnd, DWL_MSGRESULT, lMsgResult);

	// Return if msg was handled.
	return bMsgHandled;
}

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
	// No table specified?
	if (m_pGravTable == NULL)
		return;

	CTLGRAVITY* pGrav = m_pGravTable;
	int			nWnds = 0;

	// Count the number of entries.
	while (pGrav->iID != 0)
	{
		nWnds++;
		pGrav++;
	}

	// Allocate DWP handle.
	HDWP hDWP = ::BeginDeferWindowPos(nWnds);

	ASSERT(hDWP != NULL);

	// Resize all controls.
	pGrav = m_pGravTable;
	
	while (pGrav->iID != 0)
	{
		CRect rcNewPos;

		// Process controls' left edge.
		if (pGrav->eLeft == LEFT_EDGE)
		{
			rcNewPos.left = pGrav->rcStart.left;
		}
		else // pGrav->eLeft == RIGHT_EDGE
		{
			rcNewPos.left = rNewSize.cx - (m_StartSize.cx - pGrav->rcStart.left);
		}

		// Process controls' top edge.
		if (pGrav->eTop == TOP_EDGE)
		{
			rcNewPos.top = pGrav->rcStart.top;
		}
		else // pGrav->eTop == BOTTOM_EDGE
		{
			rcNewPos.top = rNewSize.cy - (m_StartSize.cy - pGrav->rcStart.top);
		}

		// Process controls' right edge.
		if (pGrav->eRight == LEFT_EDGE)
		{
			rcNewPos.right = pGrav->rcStart.right;
		}
		else // pGrav->eRight == RIGHT_EDGE
		{
			rcNewPos.right = rNewSize.cx - (m_StartSize.cx - pGrav->rcStart.right);
		}

		// Process controls' bottom edge.
		if (pGrav->eBottom == TOP_EDGE)
		{
			rcNewPos.bottom = pGrav->rcStart.bottom;
		}
		else // pGrav->eBottom == BOTTOM_EDGE
		{
			rcNewPos.bottom = rNewSize.cy - (m_StartSize.cy - pGrav->rcStart.bottom);
		}

		// Resize the window.
		::DeferWindowPos(hDWP, pGrav->hWnd, NULL, rcNewPos.left, rcNewPos.top,
							rcNewPos.Width(), rcNewPos.Height(), SWP_NOZORDER | SWP_NOCOPYBITS);

		// Next control.
	    pGrav++;
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
	ASSERT(m_pCtrlTable == NULL);
	ASSERT(pCtrlTable != NULL);

	CTRL* pCtrl     = pCtrlTable;
	int	  iNumCtrls = 0;

	// Count the number of controls.
	while (pCtrl->iID)
	{
		iNumCtrls++;
	    pCtrl++;
	}

	// Allocate memory for the copy.
	m_pCtrlTable = new CTRL[iNumCtrls+1];
	ASSERT(m_pCtrlTable);
	
	pCtrl = pCtrlTable;
	int i = 0;

	// Copy the table.
	while (i < iNumCtrls)
	{
		m_pCtrlTable[i].iID  = pCtrl->iID;
		m_pCtrlTable[i].pWnd = pCtrl->pWnd;
	    pCtrl++;
	    i++;
	}
	
	// Append table terminator.
	m_pCtrlTable[i].iID  = 0;
	m_pCtrlTable[i].pWnd = NULL;
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
	CTRL* pCtrl = m_pCtrlTable;
	
	// For all controls.
	while( (pCtrl) && (pCtrl->iID) )
	{
		uint iID = pCtrl->iID;
		
	    // Attach object to window.
	    pCtrl->pWnd->Create(*this, iID, CtrlHandle(iID));

	    pCtrl++;
	}
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
	ASSERT(m_pGravTable == NULL);
	ASSERT(pGravTable != NULL);

	CTLGRAVITY* pGrav = pGravTable;
	int			iNumCtrls = 0;

	// Count the number of entries.
	while (pGrav->iID)
	{
		iNumCtrls++;
	    pGrav++;
	}

	// Allocate memory for the copy.
	m_pGravTable = new CTLGRAVITY[iNumCtrls+1];
	ASSERT(m_pGravTable != NULL);
	
	pGrav = pGravTable;
	int i = 0;

	// Copy the table.
	while (i < iNumCtrls)
	{
		m_pGravTable[i] = *pGrav;
	    pGrav++;
	    i++;
	}
	
	// Append table terminator.
	m_pGravTable[i].iID  = 0;
	m_pGravTable[i].hWnd = NULL;
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
	// No table specified?
	if (m_pGravTable == NULL)
		return;

	// Get the dialogs initial size.
	m_StartSize = ClientRect().Size();

	CTLGRAVITY* pGrav = m_pGravTable;
	
	// For all controls.
	while( (pGrav) && (pGrav->iID) )
	{
		// Get the controls window handle.
		pGrav->hWnd = ::GetDlgItem(m_hWnd, pGrav->iID);
		ASSERT(pGrav->hWnd != NULL);

		// Get the controls starting position.
		::GetWindowRect(pGrav->hWnd, &pGrav->rcStart);
		::MapWindowPoints(NULL, m_hWnd, (LPPOINT) &pGrav->rcStart, 2);

	    pGrav++;
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
	if ( (m_pGravTable == NULL) || (m_bNoSizeGrip) )
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
	if ( (m_pGravTable != NULL) && (!m_bNoSizeGrip) )
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
