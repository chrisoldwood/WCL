/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TOOLTIP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CToolTip class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TOOLTIP_HPP
#define TOOLTIP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StdWnd.hpp"
#include <commctrl.h>

/******************************************************************************
**
** This is a tooltip control.
**
*******************************************************************************
*/

class CToolTip : public CStdWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CToolTip();
	virtual	~CToolTip();

	//
	// Methods.
	//
	void AddTool(CWnd& oParent, CWnd& oTool, const tchar* pszText);

protected:
	//
	// Members.
	//

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);

	//
	// Internal methods.
	//
	void AddTool(uint nFlags, CWnd& oParent, uint nID, const CRect* prcRect, const tchar* pszText);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CToolTip::AddTool(CWnd& oParent, CWnd& oTool, const tchar* pszText)
{
	AddTool(TTF_IDISHWND | TTF_SUBCLASS, oParent, reinterpret_cast<UINT_PTR>(oTool.Handle()), NULL, pszText);
}

#endif //TOOLTIP_HPP
