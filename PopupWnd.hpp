/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		POPUPWND.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CPopupWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef POPUPWND_HPP
#define POPUPWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "MsgWnd.hpp"

/******************************************************************************
** 
** This is a CMsgWnd derived class that provides defualt handlers for all
** messages common to overlapped and child windows. It is used for all
** non-dialog based windows.
**
*******************************************************************************
*/

class CPopupWnd : public CMsgWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CPopupWnd();

	virtual bool Create();
	virtual bool Create(DWORD dwExStyle, DWORD dwStyle);

protected:
	///////////////////////////////////////////////////////
	// Structure used to hold the CreateWindow() params.
	///////////////////////////////////////////////////////
	struct WNDCREATE
	{
		DWORD			dwExStyle;			// Extended style flags.
		const tchar*	pszClassName;		// Class name.
		const tchar*	pszTitle;			// Title.
		DWORD			dwStyle;			// Normal style flags.
		CRect			rcPos;				// Initial position.
		HWND			hParent;			// Parent window.
		HMENU			hMenu;				// Menu handle or child ID.
		void*			lpCreation;			// Window creation params or NULL.
	};

	//
	// Members.
	//
	WNDPROC	m_lpfnOldWndProc;	// The original wndproc.

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual bool Register(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);
	virtual bool Create(WNDCREATE& rCreate);

	//
	// General message handlers.
	//
	friend LRESULT WINDOWPROC PopupWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefaultWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//
	// Message processors.
	//
	virtual void OnActivate(bool bActivating);
	virtual void OnFocus();
	virtual void OnFocusLost();
	virtual void OnLeftButtonDown(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnLeftButtonUp(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnLeftButtonDblClick(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnRightButtonDown(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnRightButtonUp(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnRightButtonDblClick(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnMouseMove(const CPoint& ptCursor, uint iKeyFlags);
	virtual void OnKeyDown(WORD wKey, DWORD dwFlags);
	virtual void OnKeyUp(WORD wKey, DWORD dwFlags);
	virtual void OnChar(WORD wKey, DWORD dwFlags);
	virtual void OnSelectMenu(uint iFlags, uint iItemID, HMENU hMenu);

	virtual void OnShowMenuItemHint(uint iItemID);
	virtual void OnShowMenuPopupHint(HMENU hMenu);
	virtual void OnShowSystemMenuHint();
	virtual void OnShowDefaultMenuHint();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //POPUPWND_HPP
