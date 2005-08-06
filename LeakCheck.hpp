/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LEAKCHECK.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CLeakCheck class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LEAKCHECK_HPP
#define LEAKCHECK_HPP

/******************************************************************************
** 
** Utility class used to dump out any memory leaks on application exit.
**
*******************************************************************************
*/

class CLeakCheck
{
public:
	//
	// Constructors/Destructor.
	//
	CLeakCheck();
	~CLeakCheck();
	
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

inline CLeakCheck::CLeakCheck()
{
}

inline CLeakCheck::~CLeakCheck()
{
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}

#endif // LEAKCHECK_HPP
