/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		LIBRARY.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CLibrary class methods.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Default Constructor
**
** Description:	Resets its members.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CLibrary::CLibrary()
	: m_hInstance(NULL)
{
}

/******************************************************************************
** Method:		Constructor
**
** Description:	.
**
** Parameters:	pszPath		The DLL path.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CLibrary::CLibrary(const char* pszPath)
	: m_hInstance(NULL)
	, m_strPath(pszPath)
{
}

/******************************************************************************
** Method:		Destructor
**
** Description:	Check reasources.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CLibrary::~CLibrary()
{
	Free();
}

/******************************************************************************
** Method:		Load()
**
** Description:	Loads the module.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CLibrary::Load()
{
	m_hInstance = ::LoadLibrary(m_strPath);
	
	return (m_hInstance != NULL);
}

/******************************************************************************
** Method:		Free()
**
** Description:	Unload the module.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CLibrary::Free()
{
	if (m_hInstance != NULL)
	{
		::FreeLibrary(m_hInstance);
		m_hInstance = NULL;
	}
}
