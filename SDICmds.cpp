/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDICMDS.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSDICmds class definition.
**
*******************************************************************************
*/

#include "wcl.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CSDICmds::CSDICmds()
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CSDICmds::~CSDICmds()
{
}

/******************************************************************************
** Method:		NewFile()
**
** Description:	Creates a new document, saving the current one first.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::NewFile()
{
	// Close the current file.
	if (!CloseFile())
		return false;

	// Get application object.
	CSDIApp* pApp = CSDIApp::This();
	ASSERT(pApp);

	// Create a new doc and view and attach them.
	pApp->m_pDoc  = pApp->CreateDoc();
	pApp->m_pView = pApp->CreateView(*pApp->m_pDoc);
	pApp->m_pDoc->m_pView = pApp->m_pView;

	// Create the view and attach it to the frame window.
	pApp->FrameWnd().View(pApp->m_pView);

	// Update the UI.
	pApp->m_rCmdControl.UpdateUI();
	pApp->FrameWnd().UpdateTitle();

	return true;
}

/******************************************************************************
** Method:		OpenFile()
**
** Description:	Open an exisitng file, saving the current one first.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::OpenFile()
{
	// Get application object.
	CSDIApp* pApp = CSDIApp::This();
	ASSERT(pApp);

	CPath Path;

	// Get file extensions.
	const char* pszFileExts = pApp->FileExts();
	const char* pszDefExt   = pApp->DefFileExt();

	// Select a filename.
	if (!Path.Select(pApp->m_rMainWnd, CPath::OpenFile, pszFileExts, pszDefExt))
		return false;

	// Close the current file.
	if (!CloseFile())
		return false;

	// Create a new doc and set the path.
	pApp->m_pDoc = pApp->CreateDoc();
	pApp->m_pDoc->Path(Path);

	// Load the document.
	if (!pApp->m_pDoc->Load())
	{
		// Failed, cleanup.
		delete pApp->m_pDoc;
		pApp->m_pDoc = NULL;

		return false;
	}

	// Create a new view and attach the doc.
	pApp->m_pView = pApp->CreateView(*pApp->m_pDoc);
	pApp->m_pDoc->m_pView = pApp->m_pView;

	// Attach the view to the frame window.
	pApp->FrameWnd().View(pApp->m_pView);

	// Update the MRU.
	pApp->m_MRUList.Add(Path);

	// Update the UI.
	pApp->m_rCmdControl.UpdateUI();
	pApp->FrameWnd().UpdateTitle();

	return true;
}

/******************************************************************************
** Method:		OpenMRUFile()
**
** Description:	Open a file from the MRU list.
**
** Parameters:	nIndex		The index of the MRU file to open.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::OpenMRUFile(int nIndex)
{
	// Get application object.
	CSDIApp* pApp = CSDIApp::This();
	ASSERT(pApp);

	// Close the current file.
	if (!CloseFile())
		return false;

	// Get the MRU file path.
	CPath Path = pApp->m_MRUList[nIndex];

	// Create a new doc and set the path.
	pApp->m_pDoc = pApp->CreateDoc();
	pApp->m_pDoc->Path(Path);

	// Load the document.
	if (!pApp->m_pDoc->Load())
	{
		// Failed, cleanup.
		delete pApp->m_pDoc;
		pApp->m_pDoc = NULL;

		return false;
	}

	// Create a new view and attach the doc.
	pApp->m_pView = pApp->CreateView(*pApp->m_pDoc);
	pApp->m_pDoc->m_pView = pApp->m_pView;

	// Attach the view to the frame window.
	pApp->FrameWnd().View(pApp->m_pView);

	// Update the MRU.
	pApp->m_MRUList.Add(Path);

	// Update the UI.
	pApp->m_rCmdControl.UpdateUI();
	pApp->FrameWnd().UpdateTitle();

	return true;
}

/******************************************************************************
** Method:		SaveFile()
**
** Description:	Save the current file, asking the user for a file name if
**				it has not being set yet.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::SaveFile()
{
	// Get application object.
	CSDIApp* pApp = CSDIApp::This();
	ASSERT(pApp);

	ASSERT(pApp->m_pDoc != NULL);

	// File name specified yet?
	if (pApp->m_pDoc->Untitled())
		return SaveFileAs();

	// Save the document.
	if (!pApp->m_pDoc->Save())
		return false;

	// Update the UI.
	pApp->m_rCmdControl.UpdateUI();
	pApp->FrameWnd().UpdateTitle();

	return true;
}

/******************************************************************************
** Method:		SaveFileAs()
**
** Description:	Save the file to a new file name.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::SaveFileAs()
{
	// Get application object.
	CSDIApp* pApp = CSDIApp::This();
	ASSERT(pApp);

	ASSERT(pApp->m_pDoc != NULL);

	CPath Path;

	// Get file extensions.
	const char* pszFileExts = pApp->FileExts();
	const char* pszDefExt   = pApp->DefFileExt();

	// Select a filename.
	if (!Path.Select(pApp->m_rMainWnd, CPath::SaveFile, pszFileExts, pszDefExt))
		return false;

	// Warn user if file exists.
	if ( (Path.Exists())
	  && (pApp->m_rMainWnd.QueryMsg("The file already exists:\n\n%s\n\nOverwrite?", Path) != IDYES) )
		return false;

	// Save the document.
	pApp->m_pDoc->Path(Path);
	if (!pApp->m_pDoc->Save())
		return false;

	// Update the MRU.
	pApp->m_MRUList.Add(Path);

	// Update the UI.
	pApp->m_rCmdControl.UpdateUI();
	pApp->FrameWnd().UpdateTitle();

	return true;
}

/******************************************************************************
** Method:		CloseFile()
**
** Description:	Close the current file, saving it first.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::CloseFile()
{
	// Get application object.
	CSDIApp* pApp = CSDIApp::This();
	ASSERT(pApp);

	// No file open?
	if (pApp->m_pDoc == NULL)
		return true;

	// File modified?
	if (pApp->m_pDoc->Modified())
	{
		// Query user to save changes.
		int nRes = pApp->m_rMainWnd.QueryMsg("Save changes to: %s?", pApp->m_pDoc->Path());

		// Abort?
		if (nRes == IDCANCEL)
			return false;

		// Save changes?
		if ( (nRes == IDYES) && (SaveFile() == false) )
			return false;
	}

	// Detach the view from the frame window and doc.
	pApp->FrameWnd().View(NULL);
	pApp->m_pDoc->m_pView = NULL;

	// Destroy the open view.
	pApp->m_pView->Destroy();
	delete pApp->m_pView;
	pApp->m_pView = NULL;

	// Destroy the open file.
	delete pApp->m_pDoc;
	pApp->m_pDoc = NULL;

	// Update the UI.
	pApp->m_rCmdControl.UpdateUI();
	pApp->FrameWnd().UpdateTitle();

	return true;
}

/******************************************************************************
** Method:		ExitApp()
**
** Description:	Terminate the app.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::ExitApp()
{
	// Close the current file.
	if (!CloseFile())
		return false;

	// Close the main window.
	CSDIApp::This()->m_rMainWnd.Close();

	return true;
}
