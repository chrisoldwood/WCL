/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		DLL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CDll class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef DLL_HPP
#define DLL_HPP

/******************************************************************************
** 
** This is base class from which the dll component class is derived.
**
*******************************************************************************
*/

class CDll
{
public:
	//
	// Constructors/Destructor.
	//
	CDll();
	~CDll();
	
	// Global access to the dll object.
	static CDll& This();

	//
	// Members.
	//
	CModule		m_Module;

protected:
	//
	// Members.
	//

	//
	// Startup and Shutdown template methods.
	// (Overriden in the derived class).
	//
	virtual	bool OnLoad();
	virtual	bool OnUnload();

private:
	//
	// Startup and shutdown methods.
	// (Called from DllMain).
	//
	bool Load();
	void Unload();

	friend BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //DLL_HPP
