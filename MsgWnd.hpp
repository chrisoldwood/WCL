/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MSGWND.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CMsgWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MSGWND_HPP
#define MSGWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Wnd.hpp"

// Forward declarations.
class CPoint;
class CDC;

/******************************************************************************
** 
** This is a Wnd derived class that provides a base class for all message
** based windows. It provides the defualt handlers for all messages common to
** all windows.
**
*******************************************************************************
*/

class CMsgWnd : public CWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CMsgWnd();

	//
	// Scroll bar methods.
	//
	int HorzScrollPos(int iPos, bool bRepaint = true);
	int VertScrollPos(int iPos, bool bRepaint = true);
	int HorzScrollPos();
	int VertScrollPos();
	void HorzScrollRange(int iMin, int iMax, bool bRepaint = true);
	void VertScrollRange(int iMin, int iMax, bool bRepaint = true);
	
protected:
	/////////////////////////////////////////////////////////////////
	// Structure to define an entry in the control msg table.
	/////////////////////////////////////////////////////////////////

	// Pointer to generic message handler.
	typedef LRESULT (CMsgWnd::*PFNMSGHANDLER)(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	// Pointer to WM_COMMAND style control message handler.
	typedef void (CMsgWnd::*PFNCMDMSGHANDLER)();

	// Pointer to WM_NOTIFY style control message handler.
	typedef LRESULT (CMsgWnd::*PFNNFYMSGHANDLER)(NMHDR& rMsgHdr);
	
	struct CTRLMSG
	{
		uint			m_iMsgType;			// WM_COMMAND or WM_NOTIFY.
		uint			m_iCtrlID;			// ID of control.
		uint			m_iMsgID;			// Event message ID.
		PFNMSGHANDLER	m_pfnMsgHandler;	// Message handler method.
	};
	
	//
	// Members.
	//
	CTRLMSG*	m_pCtrlMsgTable;
	
	//
	// General message handlers.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefaultWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) = 0;

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnActivate(bool bActivating);
	virtual	void OnEraseBackground(CDC& rDC);
	virtual	void OnPaint(CDC& rDC);
	virtual void OnResize(int iFlag, const CSize& NewSize);
	virtual void OnTimer(uint iTimerID);
	virtual	void OnShow(bool bShowing);
	virtual void OnDestroy();
	virtual void OnNCDestroy();
	virtual void OnHorizScroll(uint iCode, uint iPos);
	virtual void OnVertScroll(uint iCode, uint iPos);
	virtual void OnCmdMsg(uint iID);
	virtual void OnCtrlMsg(uint iID, uint iMsg, HWND hControl);
	virtual LRESULT OnCtrlMsg(NMHDR& rMsgHdr);
	virtual void OnReflectedCtrlMsg(uint iMsg);
	virtual void OnReflectedCtrlMsg(NMHDR& rMsgHdr);
	virtual void OnMeasureItem(uint iID, uint iItem, uint& iWidth, uint& iHeight);
	virtual void OnDrawItem(uint iID, uint iAction, uint iState, CDC& rDC, uint iItem, const CRect& rcItem);
	virtual void OnSetCursor(HWND hWnd, uint nHitCode, uint nMouseMsg);
	virtual void OnCtlColour(uint nCtlClrMsg, HDC hDC, HWND hCtlWnd);
	virtual HBRUSH OnReflectedCtlClr(uint nCtlClrMsg, HDC hDC);
	virtual void OnHelp(HELPINFO& oInfo);
	virtual void OnUserMsg(uint nMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnAppMsg(uint nMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnRegisteredMsg(uint nMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnHitTest(const CPoint& ptCursor);

	//
	// Access to window data.
	//
    WNDPROC	WindowProc(WNDPROC lpfnWndProc);

	//
	// Access to message result members.
	//
	void MsgHandled(BOOL    bHandled);
	void MsgResult (LRESULT lResult);

	BOOL*    MsgHandledBuffer(BOOL*    pbBuffer);
	LRESULT* MsgResultBuffer (LRESULT* plBuffer);

private:
	//
	// Members.
	//
	BOOL*		m_pbMsgHandled;		// Was message handled?
	LRESULT*	m_plMsgResult;		// Message result code.
};

/******************************************************************************
** 
** Macros used to ease the definition of the control message table.
**
*******************************************************************************
*/

#define DEFINE_CTRLMSG_TABLE		static CTRLMSG CtrlMsgs[] = {

#define CMD_CTRLMSG(id, msgid, fn)	{ (WM_COMMAND), (id), (msgid), (PFNMSGHANDLER) (fn) },

#define NFY_CTRLMSG(id, msgid, fn)	{ (WM_NOTIFY),  (id), (msgid), (PFNMSGHANDLER) (fn) },

#define END_CTRLMSG_TABLE			{           0,     0,       0, (PFNMSGHANDLER) (NULL) } }; \
									m_pCtrlMsgTable = CtrlMsgs;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CMsgWnd::HorzScrollPos(int iPos, bool bRepaint)
{
	return ::SetScrollPos(m_hWnd, SB_HORZ, iPos, bRepaint);
}

inline int CMsgWnd::VertScrollPos(int iPos, bool bRepaint)
{
	return ::SetScrollPos(m_hWnd, SB_VERT, iPos, bRepaint);
}

inline int CMsgWnd::HorzScrollPos()
{
	return ::GetScrollPos(m_hWnd, SB_HORZ);
}

inline int CMsgWnd::VertScrollPos()
{
	return ::GetScrollPos(m_hWnd, SB_VERT);
}

inline void CMsgWnd::HorzScrollRange(int iMin, int iMax, bool bRepaint)
{
	::SetScrollRange(m_hWnd, SB_HORZ, iMin, iMax, bRepaint);
}

inline void CMsgWnd::VertScrollRange(int iMin, int iMax, bool bRepaint)
{
	::SetScrollRange(m_hWnd, SB_VERT, iMin, iMax, bRepaint);
}

inline WNDPROC CMsgWnd::WindowProc(WNDPROC lpfnWndProc)
{
	return (WNDPROC) ::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)lpfnWndProc);
}

inline void CMsgWnd::MsgHandled(BOOL bHandled)
{
	ASSERT(m_pbMsgHandled != NULL);

	*m_pbMsgHandled = bHandled;
}

inline void CMsgWnd::MsgResult(LRESULT lResult)
{
	ASSERT(m_plMsgResult != NULL);

	*m_plMsgResult = lResult;
}

inline BOOL* CMsgWnd::MsgHandledBuffer(BOOL* pbBuffer)
{
	BOOL* pbOldBuffer = m_pbMsgHandled;

	m_pbMsgHandled = pbBuffer;

	return pbOldBuffer;
}

inline LRESULT* CMsgWnd::MsgResultBuffer (LRESULT* plBuffer)
{
	LRESULT* plOldBuffer = m_plMsgResult;

	m_plMsgResult = plBuffer;

	return plOldBuffer;
}

#endif //MSGWND_HPP
