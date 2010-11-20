/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCEL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CAccel class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ACCEL_HPP
#define ACCEL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
**
** This encapsulates a Windows accelerator table.
**
*******************************************************************************
*/

class CAccel /*: private NotCopyable*/
{
public:
	//
	// Constructors/Destructor.
	//
	CAccel();
	~CAccel();

	void LoadRsc(uint iRscID);

	//
	// Member access.
	//
	HACCEL Handle() const;

	//
	// Message handling.
	//
	bool Translate(HWND hWnd, MSG& rMsg);

protected:
	//
	// Members.
	//
	HACCEL	m_hAccel;

private:
	// NotCopyable.
	CAccel(const CAccel&);
	CAccel& operator=(const CAccel&);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HACCEL CAccel::Handle() const
{
	return m_hAccel;
}

#endif //ACCEL_HPP
