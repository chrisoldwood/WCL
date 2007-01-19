/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TRAYICON.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CTrayIcon class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TRAYICON_HPP
#define TRAYICON_HPP

/******************************************************************************
** 
** A class to encapsulate a system tray icon.
**
*******************************************************************************
*/

class CTrayIcon
{
public:
	//
	// Constructors/Destructor.
	//
	CTrayIcon();
	~CTrayIcon();

	//
	// Properties.
	//
	bool IsVisible() const;

	//
	// Methods.
	//
	void Add(const CWnd& oWnd, uint nTrayID, uint nMsgID, uint nRscID, const char* pszToolTip = NULL);
	void Modify(uint nRscID, const char* pszToolTip);
	void ModifyIcon(uint nRscID);
	void ModifyToolTip(const char* pszToolTip);
	void Remove();

protected:
	//
	// Members.
	//
	HWND	m_hWnd;
	uint	m_nTrayID;
	uint	m_nMsgID;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline bool CTrayIcon::IsVisible() const
{
	return (m_hWnd != NULL);
}

inline void CTrayIcon::ModifyIcon(uint nRscID)
{
	Modify(nRscID, NULL);
}

inline void CTrayIcon::ModifyToolTip(const char* pszToolTip)
{
	Modify(NULL, pszToolTip);
}

#endif // TRAYICON_HPP
