/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ASSERT.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	Debugging macros.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ASSERT_HPP
#define ASSERT_HPP

// Debug version?
#ifdef _DEBUG

/******************************************************************************
**
**	These are the implmentations for a debug version.
**
*******************************************************************************
*/

// Prototype for the actual ASSERT function.
void AssertFail(const char* pszExpression, const char* pszFile, uint iLine);

// Basic assert macro.
#define ASSERT(x)		if (x) {} else AssertFail(#x, __FILE__, __LINE__)

// Basic trace message.
#define	TRACE(x)		OutputDebugString(x)

// Prototype for the real TRACE fucntion.
void TraceEx(const char* pszFormat, ...);

// Printf style trace messaging.
#define TRACE1(x,a)				TraceEx(x, a)
#define TRACE2(x,a,b)			TraceEx(x, a, b)
#define TRACE3(x,a,b,c)			TraceEx(x, a, b, c)
#define TRACE4(x,a,b,c,d)		TraceEx(x, a, b, c, d)
#define TRACE5(x,a,b,c,d,e)		TraceEx(x, a, b, c, d, e)

#else // NDEBUG

/******************************************************************************
**
**	These are the implmentations for a release version. They all compile to
**	nothing at all.
**
*******************************************************************************
*/

#define ASSERT(x)

#define	TRACE(x)
#define TRACE1(x,a)
#define TRACE2(x,a,b)
#define TRACE3(x,a,b,c)
#define TRACE4(x,a,b,c,d)
#define TRACE5(x,a,b,c,d,e)

#endif // _DEBUG

#endif //ASSERT_HPP
