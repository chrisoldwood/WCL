/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDIFRAME.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CSDIFrame class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SDIFRAME_HPP
#define SDIFRAME_HPP

/******************************************************************************
** 
** This is the base class for an SDI applications' main window.
**
*******************************************************************************
*/

class CSDIFrame : public CFrameWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CSDIFrame(uint iIconID);
	~CSDIFrame();

	//
	// Methods.
	//
	void View(CView* pView);

	void UpdateTitle();

protected:
	//
	// Members.
	//
	CView*	m_pView;	// The only doc view.

	// Child window IDs.
	enum
	{
		IDC_VIEW = 100
	};

	//
	// Message processors (Overriden from the base class).
	//
	virtual void OnResize(int iFlag, const CSize& rNewSize);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SDIFRAME_HPP
