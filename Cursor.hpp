/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CURSOR.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CCursor class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CURSOR_HPP
#define CURSOR_HPP

/******************************************************************************
** 
** This class wraps a standard GDI cursor.
**
*******************************************************************************
*/

class CCursor
{
public:
	//
	// Constructors/Destructor.
	//
	CCursor();
	~CCursor();

	void LoadRsc(const char* pszRsc);
	
	//
	// Member access.
	//
	HCURSOR Handle() const;

protected:
	//
	// Members.
	//
	HCURSOR	m_hCursor;
	bool	m_bOwner;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline void CCursor::LoadRsc(const char* pszRsc)
{
	m_hCursor = ::LoadCursor(NULL, pszRsc);
	m_bOwner  = false;

	ASSERT(m_hCursor != NULL);
}

inline HCURSOR CCursor::Handle() const
{
	return m_hCursor;
}

#endif //CURSOR_HPP
