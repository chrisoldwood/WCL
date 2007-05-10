/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MODULE.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CModule class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MODULE_HPP
#define MODULE_HPP

/******************************************************************************
** 
** This class holds the instance handle of an EXE or DLL module.
**
*******************************************************************************
*/

class CModule
{
public:
	//
	// Constructors/Destructor.
	//
	CModule();
	~CModule();
	
	//
	// Member access.
	//
	HINSTANCE Handle() const;

	// Global access to the object.
	static CModule& This();

	//
	// Methods.
	//

	//! Get the full path to the module.
	CPath Path() const;

protected:
	//
	// Members.
	//
	HINSTANCE	m_hInstance;

	friend int  WINAPI WinMain(HINSTANCE hCurrInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int iCmdShow);
	friend BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline HINSTANCE CModule::Handle() const
{
	return m_hInstance;
}

#endif //MODULE_HPP
