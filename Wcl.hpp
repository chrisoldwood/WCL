/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		WCL.HPP
** COMPONENT:	Windows C++ Library.
** DESCRIPTION:	Wrapper to include all the core library headers.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef WCL_HPP
#define WCL_HPP

/******************************************************************************
**
** Build targets.
**
*******************************************************************************
*/

#define STRICT						// Use proper handle types.
#define VC_EXTRALEAN				// Trim <windows.h>

#define WINVER			0x0400		// Windows 95+
#define _WIN32_WINNT	0x0400		// Windows NT 4.0+
#define _WIN32_WINDOWS	0x0400		// Windows 95+
#define _WIN32_IE		0x0400		// Internet Explorer 4.0+

/******************************************************************************
**
** Standard headers.
**
*******************************************************************************
*/

#include "Pragmas.hpp"
#include <windows.h>
#include <windowsx.h>
#include <stddef.h>
#include <string.h>
#include <commctrl.h>
#include <time.h>
#include <malloc.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

/******************************************************************************
**
** Library specific headers.
**
*******************************************************************************
*/

// Core data types.
#include "WclTypes.hpp"
#include "WclRsc.h"

// Debugging functions.
#include "Assert.hpp"

// Core data classes.
#include "Point.hpp"
#include "Size.hpp"
#include "Rect.hpp"
#include "String.hpp"
#include "Path.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "DateTime.hpp"
#include "Buffer.hpp"

// Core collection classes.
#include "Array.hpp"
#include "TArray.hpp"
#include "StrArray.hpp"
#include "List.hpp"
#include "TList.hpp"
#include "PtrList.hpp"
#include "Map.hpp"
#include "MapIter.hpp"
#include "TMap.hpp"
#include "TMapIter.hpp"
#include "HandleMap.hpp"
#include "IntPtrMap.hpp"
#include "StrPtrMap.hpp"
#include "TTree.hpp"
#include "TTreeIter.hpp"

// Exception classes.
#include "Exception.hpp"
#include "StrCvtException.hpp"
#include "StreamException.hpp"
#include "FileException.hpp"
#include "MemStreamException.hpp"

// Specific collections.
#include "WndMap.hpp"
#include "MsgFilter.hpp"

// Persistance classes.
#include "StrCvt.hpp"
#include "FileFinder.hpp"
#include "IniFile.hpp"
#include "RegKey.hpp"
#include "Stream.hpp"
#include "File.hpp"
#include "MemStream.hpp"
#include "Clipboard.hpp"
#include "Doc.hpp"

// Networking classes.
#include "NetFinder.hpp"

// GUI classes.
#include "Accel.hpp"
#include "Menu.hpp"
#include "PopupMenu.hpp"
#include "FrameMenu.hpp"
#include "BusyCursor.hpp"

// GDI classes.
#include "Bitmap.hpp"
#include "TransparentBmp.hpp"
#include "Pen.hpp"
#include "Brush.hpp"
#include "LogFont.hpp"
#include "Font.hpp"
#include "DC.hpp"
#include "MemDC.hpp"
#include "Printer.hpp"
#include "PrinterDC.hpp"
#include "ScreenDC.hpp"
#include "CmdBmp.hpp"
#include "Cursor.hpp"
#include "Icon.hpp"
#include "ImageList.hpp"

// Base window classes.
#include "Wnd.hpp"
#include "MsgWnd.hpp"
#include "PopupWnd.hpp"
#include "Dialog.hpp"
#include "CtrlWnd.hpp"
#include "StdWnd.hpp"

// Built-in controls classes
#include "StaticCtrl.hpp"
#include "IconCtrl.hpp"
#include "Label.hpp"
#include "ListBox.hpp"
#include "ComboBox.hpp"
#include "EditBox.hpp"
#include "CheckBox.hpp"
#include "RadioBtn.hpp"
#include "Button.hpp"
#include "ListView.hpp"
#include "CheckBoxList.hpp"
#include "DateTimePicker.hpp"
#include "ProgressBar.hpp"
#include "UpDownBtns.hpp"
#include "TabCtrl.hpp"
#include "ToolTip.hpp"

// Custom controls classes.
#include "CmdBtn.hpp"
#include "PathEditBox.hpp"
#include "DecimalBox.hpp"
#include "HintBar.hpp"
#include "StatusBarPanel.hpp"
#include "StatusBar.hpp"
#include "StatusBarLabel.hpp"
#include "StatusBarIcon.hpp"
#include "ToolBar.hpp"
#include "TabWndHost.hpp"
#include "URLLabel.hpp"

// Special dialog classes.
#include "PropertyPage.hpp"
#include "PropertySheet.hpp"

// View window classes.
#include "MainDlg.hpp"
#include "View.hpp"
#include "SplitWnd.hpp"

// Top-level window classes.
#include "FrameWnd.hpp"
#include "DlgFrame.hpp"

// Misc classes.
#include "HelpFile.hpp"
#include "MRUList.hpp"
#include "SysInfo.hpp"
#include "TrayIcon.hpp"
#include "StrTok.hpp"
#include "AutoBool.hpp"

// Threading classes.
#include "IThreadLock.hpp"
#include "CriticalSection.hpp"
#include "Event.hpp"
#include "AutoThreadLock.hpp"
#include "Thread.hpp"
#include "MsgThread.hpp"
#include "MainThread.hpp"
#include "ThreadJob.hpp"
#include "WorkerThread.hpp"
#include "ThreadPool.hpp"

// Process classes.
#include "Library.hpp"
#include "CmdCtrl.hpp"

// Module classes.
#include "ComCtl32.hpp"
#include "Module.hpp"
#include "App.hpp"
#include "Dll.hpp"

// SDI app classes.
#include "SDIDoc.hpp"
#include "SDIFrame.hpp"
#include "SDICmds.hpp"
#include "SDIApp.hpp"

#endif //WCL_HPP
