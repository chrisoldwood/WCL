/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		URLLABEL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CURLLabel class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef URLLABEL_HPP
#define URLLABEL_HPP

/******************************************************************************
** 
** A STATIC based control with the ability to behave like a hyperlink.
**
*******************************************************************************
*/

class CURLLabel : public CLabel
{
public:
	//
	// Constructors/Destructor.
	//
	CURLLabel();
	~CURLLabel();

	//
	// Methods.
	//
	void Protocol(const char* pszProtocol);
	
protected:
	//
	// Members.
	//
	CString	m_strProtocol;
	CCursor	m_oCursor;
	CFont	m_oFont;

	//
	// Message handlers.
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual void    OnSetCursor(HWND hWnd, uint nHitCode, uint nMouseMsg);
	virtual void    OnClick();
	virtual HBRUSH  OnReflectedCtlClr(uint nCtlClrMsg, HDC hDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CURLLabel::Protocol(const char* pszProtocol)
{
	ASSERT(pszProtocol != NULL);

	m_strProtocol = pszProtocol;
}

#endif //URLLABEL_HPP
