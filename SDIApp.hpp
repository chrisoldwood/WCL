/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIAPP.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CSDIApp class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SDIAPP_HPP
#define SDIAPP_HPP

/******************************************************************************
** 
** This is the application base class for SDI applications.
**
*******************************************************************************
*/

class CSDIApp : public CApp
{
public:
	//
	// Constructors/Destructor.
	//
	CSDIApp(CSDIFrame& rFrameWnd, CSDICmds& rCmdControl);
	~CSDIApp();

	//
	// Template methods for getting doc and view specifics.
	//
	virtual CSDIDoc*    CreateDoc() const = 0;
	virtual CView*      CreateView(CDoc& rDoc) const = 0;
	virtual const char* FileExts() const = 0;
	virtual const char* DefFileExt() const = 0;

	// Typed access to the app objects.
	static CSDIApp* This();
	CSDIFrame& FrameWnd();

	//
	// Members.
	//
	CSDIDoc*	m_pDoc;		// The open document.
	CView*		m_pView;	// The open documents' view.
	CMRUList	m_MRUList;	// The list of recently opened docs.

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CSDIApp* CSDIApp::This()
{
	return static_cast<CSDIApp*>(CApp::This());
}

inline CSDIFrame& CSDIApp::FrameWnd()
{
	return static_cast<CSDIFrame&>(m_rMainWnd);
}

#endif //SDIAPP_HPP
