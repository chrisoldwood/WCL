/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STRTOK.HPP
** COMPONENT:	Windows C++ Library
** DESCRIPTION:	The CStrTok class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STRTOK_HPP
#define STRTOK_HPP

/******************************************************************************
** 
** A string tokeniser.
** NB: This does not copy the string being tokenised.
**
*******************************************************************************
*/

class CStrTok
{
public:
	//
	// Constructors/Destructor.
	//
	CStrTok(const char* pszString, char        cSep,    int nFlags = NONE);
	CStrTok(const char* pszString, const char* pszSeps, int nFlags = NONE);
	~CStrTok();

	//
	// Methods.
	//
	bool    MoreTokens() const;
	CString NextToken();

	//
	// Flags.
	//
	enum Flags
	{
		NONE		= 0x0000,	// Defaults.
		MERGE_SEPS	= 0x0001,	// Merge consecutive seps.
	};

	//
	// Helper methods.
	//
	static uint Split(const char* pszString, char cSep,           CStrArray& astrFields);
	static uint Split(const char* pszString, const char* pszSeps, CStrArray& astrFields);

protected:
	//
	// Members.
	//
	const char*	m_pszString;	// The string to tokenise.
	CString		m_strSeps;		// The list of separators.
	int			m_nFlags;		// The tokenising flags.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline bool CStrTok::MoreTokens() const
{
	return (*m_pszString != '\0');
}

#endif // STRTOK_HPP
