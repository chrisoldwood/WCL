/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		HINTBAR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CHintBar class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef HINTBAR_HPP
#define HINTBAR_HPP

/******************************************************************************
** 
** This is a child window used to display hints.
**
*******************************************************************************
*/

class CHintBar : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CHintBar();

	//
	// Member setting.
	//
	void Hint(uint iRscID);
	void Hint(const char* pszHint);
	
protected:
	//
	// Members.
	//
	char m_szHint[128];
	
	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual	void OnPaint(CDC& rDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //HINTBAR_HPP
