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
#ifndef WCL_STRCVT_HPP
#define WCL_STRCVT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

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
	static CString FormatUInt    (uint   nValue);
	static CString FormatLong    (long   lValue);
	static CString FormatDouble  (double dValue);
	static CString FormatDate    (time_t tValue);
	static CString FormatDateTime(time_t tValue);
	static CString FormatError   (DWORD dwError = ::GetLastError());

	// Parser flags.
	enum ParseFlags
	{
		PARSE_ANY_FORMAT	= 0x0000,	// Determine format (see 'strtol').
		PARSE_OCTAL_ONLY	= 0x0008,	// Allow octal only.
		PARSE_DECIMAL_ONLY	= 0x000A,	// Allow decimal only.
		PARSE_HEX_ONLY		= 0x0010,	// Allow hex only.
	};

	//
	// Parsing methods.
	//
	static int    ParseInt   (const tchar* pszString, int nFlags = PARSE_ANY_FORMAT);
	static uint   ParseUInt  (const tchar* pszString, int nFlags = PARSE_ANY_FORMAT);
	static long   ParseLong  (const tchar* pszString, int nFlags = PARSE_ANY_FORMAT);
	static double ParseDouble(const tchar* pszString, int nFlags = PARSE_ANY_FORMAT);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // WCL_STRCVT_HPP
