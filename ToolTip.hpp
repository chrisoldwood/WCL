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
	~CToolTip();
	
	//
	// Methods.
	//
	void AddTool(CWnd& oParent, CWnd& oTool, const char* pszText);

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
	void AddTool(uint nFlags, CWnd& oParent, uint nID, const CRect* prcRect, const char* pszText);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CToolTip::AddTool(CWnd& oParent, CWnd& oTool, const char* pszText)
{
	AddTool(TTF_IDISHWND | TTF_SUBCLASS, oParent, (uint)oTool.Handle(), NULL, pszText);
}

#endif //TOOLTIP_HPP
