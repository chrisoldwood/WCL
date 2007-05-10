/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATUSBARICON.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CStatusBarIcon class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATUSBARICON_HPP
#define STATUSBARICON_HPP

/******************************************************************************
** 
** A status bar field which contains an icon.
**
*******************************************************************************
*/

class CStatusBarIcon : public CStatusBarPanel
{
public:
	//
	// Constructors/Destructor.
	//
	CStatusBarIcon();
	virtual	~CStatusBarIcon();
	
	//
	// Methods.
	//
	void ClearIcon(bool bForcePaint = false);
	void SetIcon(const CTransparentBmp& oBitmap, int nIndex, bool bForcePaint = false);

protected:
	//
	// Members.
	//
	const CTransparentBmp*	m_pBitmap;
	int						m_nIndex;

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnPaint(CDC& rDC);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // STATUSBARICON_HPP
