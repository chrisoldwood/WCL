/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRTOK.CPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	CStrTok class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StrTok.hpp"
#include "StrArray.hpp"

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

CStrTok::CStrTok(const tchar* pszString, tchar cSep, int nFlags)
	: m_pszString(pszString)
	, m_strSeps(&cSep, 1)
	, m_nFlags(nFlags)
	, m_eNextToken(END_TOKEN)
{
	if (*pszString != TXT('\0'))
		m_eNextToken = VALUE_TOKEN;
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

CStrTok::CStrTok(const tchar* pszString, const tchar* pszSeps, int nFlags)
	: m_pszString(pszString)
	, m_strSeps(pszSeps)
	, m_nFlags(nFlags)
	, m_eNextToken(END_TOKEN)
{
	if (*pszString != TXT('\0'))
		m_eNextToken = VALUE_TOKEN;
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

	const tchar* pszStart = m_pszString;
	const tchar* pszEnd   = pszStart;

	// Next token is a value?
	if (m_eNextToken == VALUE_TOKEN)
	{
		// Find next separator or EOS.
		while ( (*m_pszString != TXT('\0')) && (tstrchr(m_strSeps, *m_pszString) == nullptr) )
			++m_pszString;

		pszEnd = m_pszString;

		// Stopped on a separator?
		if (*m_pszString != TXT('\0'))
		{
			// Switch state, if returning separators.
			if (m_nFlags & RETURN_SEPS)
			{
				m_eNextToken = SEPARATOR_TOKEN;
			}
			// Skip separators.
			else 
			{
				++m_pszString;

				// Merge consecutive separators?
				if (m_nFlags & MERGE_SEPS)
				{
					while ( (*m_pszString != TXT('\0')) && (tstrchr(m_strSeps, *m_pszString) != nullptr) )
						++m_pszString;
				}
			}
		}
		// Reached EOS.
		else //(*m_pszString == TXT('\0'))
		{
			m_eNextToken = END_TOKEN;
		}
	}
	// Next token is a separator.
	else //(m_eNextToken == SEPARATOR_TOKEN)
	{
		ASSERT(tstrchr(m_strSeps, *m_pszString) != nullptr);

		++m_pszString;

		// Merge consecutive separators?
		if (m_nFlags & MERGE_SEPS)
		{
			while ( (*m_pszString != TXT('\0')) && (tstrchr(m_strSeps, *m_pszString) != nullptr) )
				++m_pszString;
		}

		pszEnd = m_pszString;

		// Switch state back to normal.
		m_eNextToken = VALUE_TOKEN;
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
**				nFlags		The split options (See Flags).
**
** Returns:		The number of fields.
**
*******************************************************************************
*/

size_t CStrTok::Split(const tchar* pszString, tchar cSep, CStrArray& astrFields, uint nFlags)
{
	tchar szSeps[2] = {cSep, TXT('\0')};

	return Split(pszString, szSeps, astrFields, nFlags);
}

/******************************************************************************
** Method:		Split()
**
** Description:	Splits a string into separate fields.
**
** Parameters:	pszString	The string to split.
**				pszSeps		The list of separators.
**				astrFields	The array into which the fields are returned.
**				nFlags		The split options (See Flags).
**
** Returns:		The number of fields.
**
*******************************************************************************
*/

size_t CStrTok::Split(const tchar* pszString, const tchar* pszSeps, CStrArray& astrFields, uint nFlags)
{
	ASSERT(pszString != nullptr);
	ASSERT(pszSeps   != nullptr);

	CStrTok oStrTok(pszString, pszSeps, nFlags);

	// Add all tokens to the array.
	while (oStrTok.MoreTokens())
		astrFields.Add(oStrTok.NextToken());

	return astrFields.Size();
}
