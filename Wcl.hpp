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
** Standard headers.
**
*******************************************************************************
*/

#define STRICT

#include "Pragmas.hpp"
#include <windows.h>
#include <windowsx.h>
#include <stddef.h>
#include <string.h>
#include <commctrl.h>

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

// Core classes.
#include "Point.hpp"
#include "Size.hpp"
#include "Rect.hpp"
#include "String.hpp"
#include "Path.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "DateTime.hpp"

// Core collection classes.
#include "Array.hpp"
#include "PtrArray.hpp"
#include "StrArray.hpp"
#include "List.hpp"
#include "PtrList.hpp"
#include "Map.hpp"
#include "HandleMap.hpp"
#include "IntPtrMap.hpp"
#include "StrPtrMap.hpp"

// Exception classes.
#include "Exception.hpp"
#include "STreamException.hpp"
#include "FileException.hpp"
#include "MemStreamException.hpp"

// Specific collections.
#include "WndMap.hpp"
#include "MsgFilter.hpp"

// Persistance classes.
#include "IniFile.hpp"
#include "Stream.hpp"
#include "File.hpp"
#include "MemStream.hpp"
#include "Clipboard.hpp"
#include "Doc.hpp"

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

// Base window classes.
#include "Wnd.hpp"
#include "MsgWnd.hpp"
#include "PopupWnd.hpp"
#include "Dialog.hpp"
#include "CtrlWnd.hpp"
#include "StdWnd.hpp"

// Built-in controls classes
#include "Label.hpp"
#include "ListBox.hpp"
#include "ComboBox.hpp"
#include "EditBox.hpp"
#include "CheckBox.hpp"
#include "RadioBtn.hpp"
#include "Button.hpp"
#include "ListView.hpp"
#include "DateTimePicker.hpp"
#include "ProgressBar.hpp"
#include "UpDownBtns.hpp"
#include "TabCtrl.hpp"

// Custom controls classes.
#include "CmdBtn.hpp"
#include "PathEditBox.hpp"
#include "DecimalBox.hpp"
#include "HintBar.hpp"
#include "StatusBar.hpp"
#include "ToolBar.hpp"
#include "TabWndHost.hpp"

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

// Process classes.
#include "Thread.hpp"
#include "MsgThread.hpp"
#include "Library.hpp"
#include "CmdCtrl.hpp"
#include "App.hpp"

// SDI app classes.
#include "SDIDoc.hpp"
#include "SDIFrame.hpp"
#include "SDICmds.hpp"
#include "SDIApp.hpp"

#endif //WCL_HPP
