/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRTOK.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStrTok class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStrTok::CStrTok(const char* pszString, char cSep, int nFlags)
	: m_pszString(pszString)
	, m_strSeps(&cSep, 1)
	, m_nFlags(nFlags)
{
}

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStrTok::CStrTok(const char* pszString, const char* pszSeps, int nFlags)
	: m_pszString(pszString)
	, m_strSeps(pszSeps)
	, m_nFlags(nFlags)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStrTok::~CStrTok()
{
}

/******************************************************************************
** Method:		NextToken()
**
** Description:	Returns the next token, either a string or separator list.
**
** Parameters:	None.
**
** Returns:		The next token.
**
*******************************************************************************
*/

CString CStrTok::NextToken()
{
	ASSERT(MoreTokens());

	const char* pszStart = m_pszString;

	// Find next separator.
	while ( (*m_pszString != '\0') && (strchr(m_strSeps, *m_pszString) == NULL) )
		++m_pszString;

	const char* pszEnd = m_pszString;

	// Skip separator.
	if (*m_pszString != '\0')
		++m_pszString;
		
	// Merge consecutive separators?
	if (m_nFlags & MERGE_SEPS)
	{
		// Find end of separators.
		while ( (*m_pszString != '\0') && (strchr(m_strSeps, *m_pszString) != NULL) )
			++m_pszString;
	}

	return CString(pszStart, pszEnd-pszStart);
}

/******************************************************************************
** Method:		Split()
**
** Description:	Splits a string into separate fields.
**
** Parameters:	pszString	The string to split.
**				cSep		The separator.
**				astrFields	The array into which the fields are returned.
**
** Returns:		The number of fields.
**
*******************************************************************************
*/

uint CStrTok::Split(const char* pszString, char cSep, CStrArray& astrFields)
{
	char szSeps[2] = {cSep, '\0'};

	return Split(pszString, szSeps, astrFields);
}

/******************************************************************************
** Method:		Split()
**
** Description:	Splits a string into separate fields.
**
** Parameters:	pszString	The string to split.
**				pszSeps		The list of separators.
**				astrFields	The array into which the fields are returned.
**
** Returns:		The number of fields.
**
*******************************************************************************
*/

uint CStrTok::Split(const char* pszString, const char* pszSeps, CStrArray& astrFields)
{
	ASSERT(pszString != NULL);
	ASSERT(pszSeps   != NULL);

	CStrTok oStrTok(pszString, pszSeps);

	// Add all tokens to the array.
	while (oStrTok.MoreTokens())
		astrFields.Add(oStrTok.NextToken());

	return astrFields.Size();
}
