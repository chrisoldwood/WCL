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
		MERGE_SEPS	= 0x0001,	// Merge consecutive separators.
		RETURN_SEPS = 0x0002,	// Return separators as tokens.
	};

	//
	// Helper methods.
	//
	static uint Split(const char* pszString, char cSep,           CStrArray& astrFields, int nFlags = NONE);
	static uint Split(const char* pszString, const char* pszSeps, CStrArray& astrFields, int nFlags = NONE);

protected:
	// Token types.
	enum TokenType
	{
		END_TOKEN		= -1,	// Reached end of tokens.

		VALUE_TOKEN		=  1,	// Parsing value token.
		SEPARATOR_TOKEN =  2,	// Parsing separator list token.
	};

	//
	// Members.
	//
	const char*	m_pszString;	// The string to tokenise.
	CString		m_strSeps;		// The list of separators.
	int			m_nFlags;		// The tokenising flags.
	TokenType	m_eNextToken;	// The next token type expected.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline bool CStrTok::MoreTokens() const
{
	return (m_eNextToken != END_TOKEN);
}

#endif // STRTOK_HPP
