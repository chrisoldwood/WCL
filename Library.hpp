/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LIBRARY.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CLibrary class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef LIBRARY_HPP
#define LIBRARY_HPP

/******************************************************************************
** 
** A class to encapsulate a component such as a DLL.
**
*******************************************************************************
*/

class CLibrary
{
public:
	//
	// Constructors/Destructor.
	//
	CLibrary();
	~CLibrary();

	bool Load();
	void Free();

	bool IsLoaded() const;
	
	//
	// Member access.
	//
	HINSTANCE Handle() const;
	CPath& Path();

protected:
	//
	// Members
	//
	HINSTANCE	m_hInstance;
	CPath		m_Path;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HINSTANCE CLibrary::Handle() const
{
	return m_hInstance;
}

inline CPath& CLibrary::Path()
{
	return m_Path;
}

inline bool CLibrary::IsLoaded() const
{
	return (m_hInstance != NULL);
}

#endif //LIBRARY_HPP
