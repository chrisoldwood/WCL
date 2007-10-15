/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		AUTOBOOL.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CAutoBool class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef AUTOBOOL_HPP
#define AUTOBOOL_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** A class for toggling a boolean value on/off that is exception safe.
**
*******************************************************************************
*/

class CAutoBool
{
public:
	//
	// Constructors/Destructor.
	//
	CAutoBool(bool* pBool);
	~CAutoBool();
	
protected:
	//
	// Members.
	//
	bool*	m_pBool;		// The bool to toggle.

#ifdef _DEBUG
	bool	m_bInitVal;		// The initial value.
#endif
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CAutoBool::CAutoBool(bool* pBool)
	: m_pBool(pBool)
{
	ASSERT(m_pBool != NULL);

#ifdef _DEBUG
	m_bInitVal = *m_pBool;
#endif

	*m_pBool = !*m_pBool;
}

inline CAutoBool::~CAutoBool()
{
	*m_pBool = !*m_pBool;

#ifdef _DEBUG
	ASSERT(*m_pBool == m_bInitVal);
#endif
}

#endif // AUTOBOOL_HPP
