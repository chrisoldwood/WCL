/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDICMDS.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	The CSDICmds class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SDICMDS_HPP
#define SDICMDS_HPP

/******************************************************************************
** 
** This is the base class for SDI application commands.
**
*******************************************************************************
*/

class CSDICmds : public CCmdControl
{
public:
	//
	// Constructors/Destructor.
	//
	CSDICmds();
	~CSDICmds();
	
	//
	// File commands.
	//

	bool NewFile();
	bool OpenFile();
	bool OpenMRUFile(int nIndex);
	bool SaveFile();
	bool SaveFileAs();
	bool CloseFile();
	bool ExitApp();

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SDICMDS_HPP
