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

#if _MSC_VER > 1000
#pragma once
#endif

#include "CmdCtrl.hpp"

// Forward declarations.
class CSDIDoc;
class CPath;

/******************************************************************************
** 
** This is the base class for SDI application commands.
**
*******************************************************************************
*/

class CSDICmds : public CCmdControl
{
public:
	//! Construction with the main command window.
	CSDICmds(WCL::ICommandWnd& commandWnd);

	//! Construction with the main command window and bitmap resource ID.
	CSDICmds(WCL::ICommandWnd& commandWnd, uint bitmapId);

	virtual	~CSDICmds();
	
	//
	// File commands.
	//
	bool NewFile();
	bool OpenFile();
	bool OpenMRUFile(size_t nIndex);
	bool OpenFile(const CPath& strPath);
	bool SaveFile();
	bool SaveFileAs();
	bool CloseFile();
	bool ExitApp();

protected:
	//
	// Members.
	//

	//
	// Template methods..
	//
	virtual void OnFileCreated(CSDIDoc& oDoc);
	virtual void OnFileOpened(CSDIDoc& oDoc);
	virtual void OnFileSaved(CSDIDoc& oDoc);
	virtual void OnFileClosed(CSDIDoc& oDoc);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SDICMDS_HPP
