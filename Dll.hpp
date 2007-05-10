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
	virtual ~CDll();
	
	// Global access to the dll object.
	static CDll& This();

	//
	// Members.
	//
	CLeakCheck		m_oLeakChecker;		// Dumps memory leaks.
	CModule		m_Module;

protected:
	//
	// Members.
	//

	//
	// DllMain template methods.
	// (Overriden in the derived class).
	//
	virtual	void OnLoad();
	virtual	void OnUnload();
	virtual	void OnThreadAttached();
	virtual	void OnThreadDetached();	

private:
	//
	// Startup and shutdown methods.
	// (Called from DllMain).
	//
	void Load();
	void Unload();
	void ThreadAttached();
	void ThreadDetached();	

	friend BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved);

	//
	// Class members.
	//

	//! The singleton DLL component object.
	static CDll* g_pThis;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //DLL_HPP
