/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ASSERT.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	Debugging output functions.
**
*******************************************************************************
*/

#include "wcl.hpp"
#include <stdio.h>
#include <stdarg.h>

/******************************************************************************
** Function:	AssertFail()
**
** Description:	This is called when an ASSERT fails. It displays a message box
**				with details about why and where the assert failed. If asked
**				it will also cause an INT 3 to kick in the debugger.
**
** Parameters:	pszExpression	A string representation of the ASSERT.
**				pszFile			The file in which it occurs.
**				iLine			The line where it occurs.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void AssertFail(const char* pszExpression, const char*pszFile, uint iLine)
{
	static char	szMsg[256];

	// First create the full message.
	wsprintf((LPSTR)szMsg, (LPSTR)"Code:\t%s\nFile:\t%s\nLine:\t%d\n\nDebug?", 
				(LPCSTR)pszExpression, (LPCSTR)pszFile, iLine);
	
	// Now display the message.
	if (MessageBox(NULL, (LPCSTR)szMsg, "ASSERT FAILED", MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		// Cause an INT 3.
		DebugBreak();
	}
}

/******************************************************************************
** Function:	TraceEx()
**
** Description:	This is a printf() style function for outputing debugging
**				messages. It uses vsprintf() and so is restricted to the types
**				it can handle.
**
** Parameters:	pszFormat	The format of the output string.
**				...			Variable number of arguments.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void TraceEx(const char* pszFormat, ...)
{
	static char	szMsg[256];

	// Setup arguments.
	va_list	args;
	va_start(args, pszFormat);
	
	// Form message.
	vsprintf((char*)szMsg, pszFormat, args);
	
	// Display.
	OutputDebugString((LPCSTR)szMsg);
}
