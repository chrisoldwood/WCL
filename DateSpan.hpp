/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DATESPAN.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDateSpan class declarations.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_DATESPAN_HPP
#define WCL_DATESPAN_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This class is used to represent the distance between two dates in days.
**
*******************************************************************************
*/

class CDateSpan
{
public:
	//
	// Constructors/Destructor.
	//
	CDateSpan();
	CDateSpan(WCL::Days nDays);
	
	// Accessors.
	WCL::Days Days() const;

protected:
	//
	// Members.
	//
	WCL::Days	m_nSpan;

	//
	// Friends.
	//
	friend class CDate;
};

/******************************************************************************
**
** Implementation of CDateSpan inline functions.
**
*******************************************************************************
*/

inline CDateSpan::CDateSpan()
	: m_nSpan(0)
{
}

inline CDateSpan::CDateSpan(WCL::Days nDays)
	: m_nSpan(nDays)
{
}

inline WCL::Days CDateSpan::Days() const
{
	return m_nSpan;
}

#endif // WCL_DATESPAN_HPP
