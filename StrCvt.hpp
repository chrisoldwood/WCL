/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRCVT.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CStrCvt class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STRCVT_HPP
#define STRCVT_HPP

/******************************************************************************
** 
** Functions to convert values <-> strings.
**
*******************************************************************************
*/

class CStrCvt
{
public:
	//
	// Formatting methods.
	//
	static CString FormatInt     (int    nValue);
	static CString FormatLong    (long   lValue);
	static CString FormatDouble  (double dValue);
	static CString FormatDate    (time_t tValue);
	static CString FormatDateTime(time_t tValue);

	//
	// Parsing methods.
	//
	static int    ParseInt   (const char* pszString);
	static long   ParseLong  (const char* pszString);
	static double ParseDouble(const char* pszString);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // STRCVT_HPP
