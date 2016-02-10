/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SDICMDS.CPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	CSDICmds class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "SDICmds.hpp"
#include "SDIApp.hpp"
#include "SDIDoc.hpp"
#include "View.hpp"
#include <Core/UniquePtr.hpp>
#include "BusyCursor.hpp"

////////////////////////////////////////////////////////////////////////////////
//! Construction with the main command window.

CSDICmds::CSDICmds(WCL::ICommandWnd& commandWnd)
	: CCmdControl(commandWnd)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction with the main command window and bitmap resource ID.

CSDICmds::CSDICmds(WCL::ICommandWnd& commandWnd, uint bitmapId)
	: CCmdControl(commandWnd, bitmapId)
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
	CSDIApp& oApp = CSDIApp::This();

	// Create a new doc and view and attach them.
	oApp.m_pDoc  = oApp.CreateDoc();
	oApp.m_pView = oApp.CreateView(*oApp.m_pDoc);
	oApp.m_pDoc->m_pView = oApp.m_pView;

	// Create the view and attach it to the frame window.
	oApp.FrameWnd().View(oApp.m_pView);

	OnFileCreated(*oApp.m_pDoc);

	// Update the UI.
	UpdateUI();
	oApp.FrameWnd().UpdateTitle();

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
	CSDIApp& oApp = CSDIApp::This();

	CPath Path;

	// Get file extensions.
	const tchar* pszFileExts = oApp.FileExts();
	const tchar* pszDefExt   = oApp.DefFileExt();

	// Select a filename.
	if (!Path.Select(oApp.m_rMainWnd, CPath::OpenFile, pszFileExts, pszDefExt))
		return false;

	// Open it.
	return OpenFile(Path);
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

bool CSDICmds::OpenMRUFile(size_t nIndex)
{
	// Get application object.
	CSDIApp& oApp = CSDIApp::This();

	// Open it.
	return OpenFile(oApp.m_MRUList[nIndex]);
}

/******************************************************************************
** Method:		OpenFile()
**
** Description:	Core method to open the specified file.
**
** Parameters:	strPath		The files' path.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CSDICmds::OpenFile(const CPath& strPath)
{
	typedef Core::UniquePtr<CSDIDoc> NewDocPtr;

	// Get application object.
	CSDIApp& oApp = CSDIApp::This();

	// Close the current file.
	if (!CloseFile())
		return false;

	CBusyCursor oBusyCursor;

	// Create a new doc and set the path.
	NewDocPtr pDoc(oApp.CreateDoc());

	pDoc->Path(strPath);

	// Load the document.
	if (!pDoc->Load())
		return false;

	// Create a new view and attach the doc.
	oApp.m_pDoc  = pDoc.detach();
	oApp.m_pView = oApp.CreateView(*oApp.m_pDoc);
	oApp.m_pDoc->m_pView = oApp.m_pView;

	// Attach the view to the frame window.
	oApp.FrameWnd().View(oApp.m_pView);

	// Update the MRU.
	oApp.m_MRUList.Add(strPath);

	OnFileOpened(*oApp.m_pDoc);

	// Update the UI.
	UpdateUI();
	oApp.FrameWnd().UpdateTitle();

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
	CSDIApp& oApp = CSDIApp::This();

	ASSERT(oApp.m_pDoc != nullptr);

	// File name specified yet?
	if (oApp.m_pDoc->Untitled())
		return SaveFileAs();

	CBusyCursor oBusyCursor;

	// Save the document.
	if (!oApp.m_pDoc->Save())
		return false;

	OnFileSaved(*oApp.m_pDoc);

	// Update the UI.
	UpdateUI();
	oApp.FrameWnd().UpdateTitle();

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
	CSDIApp& oApp = CSDIApp::This();

	ASSERT(oApp.m_pDoc != nullptr);

	CPath Path;

	// Get file extensions.
	const tchar* pszFileExts = oApp.FileExts();
	const tchar* pszDefExt   = oApp.DefFileExt();

	// Select a filename.
	if (!Path.Select(oApp.m_rMainWnd, CPath::SaveFile, pszFileExts, pszDefExt))
		return false;

	// Warn user if file exists.
	if ( (Path.Exists())
	  && (oApp.m_rMainWnd.QueryMsg(TXT("The file already exists:\n\n%s\n\nOverwrite?"), Path.c_str()) != IDYES) )
		return false;

	CBusyCursor oBusyCursor;

	// Save the document.
	oApp.m_pDoc->Path(Path);
	if (!oApp.m_pDoc->Save())
		return false;

	// Update the MRU.
	oApp.m_MRUList.Add(Path);

	OnFileSaved(*oApp.m_pDoc);

	// Update the UI.
	UpdateUI();
	oApp.FrameWnd().UpdateTitle();

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
	CSDIApp& oApp = CSDIApp::This();

	// No file open?
	if (oApp.m_pDoc == nullptr)
		return true;

	// File modified?
	if (oApp.m_pDoc->Modified())
	{
		// Query user to save changes.
		int nRes = oApp.m_rMainWnd.QueryMsg(TXT("Save changes to: %s?"), oApp.m_pDoc->Path().c_str());

		// Abort?
		if (nRes == IDCANCEL)
			return false;

		// Save changes?
		if ( (nRes == IDYES) && (SaveFile() == false) )
			return false;
	}

	OnFileClosed(*oApp.m_pDoc);

	// Detach the view from the frame window and doc.
	oApp.FrameWnd().View(nullptr);
	oApp.m_pDoc->m_pView = nullptr;

	// Destroy the open view.
	oApp.m_pView->Destroy();
	delete oApp.m_pView;
	oApp.m_pView = nullptr;

	// Destroy the open file.
	delete oApp.m_pDoc;
	oApp.m_pDoc = nullptr;

	// Update the UI.
	UpdateUI();
	oApp.FrameWnd().UpdateTitle();

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
	CSDIApp::This().m_rMainWnd.Close();

	return true;
}

/******************************************************************************
** Method:		OnFileCreated()
**				OnFileOpened()
**				OnFileSaved()
**				OnFileClosed()
**
** Description:	Template methods called when a file operation has happened.
**
** Parameters:	oDoc	The doc affected.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSDICmds::OnFileCreated(CSDIDoc& oDoc)
{
	OnFileOpened(oDoc);
}

void CSDICmds::OnFileOpened(CSDIDoc& /*oDoc*/)
{
}

void CSDICmds::OnFileSaved(CSDIDoc& /*oDoc*/)
{
}

void CSDICmds::OnFileClosed(CSDIDoc& /*oDoc*/)
{
}
