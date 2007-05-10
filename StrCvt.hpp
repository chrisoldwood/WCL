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
	static int    ParseInt   (const char* pszString, int nFlags = PARSE_ANY_FORMAT);
	static uint   ParseUInt  (const char* pszString, int nFlags = PARSE_ANY_FORMAT);
	static long   ParseLong  (const char* pszString, int nFlags = PARSE_ANY_FORMAT);
	static double ParseDouble(const char* pszString, int nFlags = PARSE_ANY_FORMAT);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // STRCVT_HPP
