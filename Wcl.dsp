# Microsoft Developer Studio Project File - Name="Wcl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Wcl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Wcl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Wcl.mak" CFG="Wcl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Wcl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Wcl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Win32/Wcl", UAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Wcl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX"wcl.hpp" /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Wcl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /WX /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX"wcl.hpp" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Wcl - Win32 Release"
# Name "Wcl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Accel.cpp
# End Source File
# Begin Source File

SOURCE=.\App.cpp
# End Source File
# Begin Source File

SOURCE=.\Array.cpp
# End Source File
# Begin Source File

SOURCE=.\Assert.cpp
# End Source File
# Begin Source File

SOURCE=.\Bitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\Brush.cpp
# End Source File
# Begin Source File

SOURCE=.\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\BusyCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\Button.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckBox.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckBoxList.cpp
# End Source File
# Begin Source File

SOURCE=.\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdBmp.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ComCtl32.cpp
# End Source File
# Begin Source File

SOURCE=.\CriticalSection.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Cursor.cpp
# End Source File
# Begin Source File

SOURCE=.\Date.cpp
# End Source File
# Begin Source File

SOURCE=.\DateTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DateTimePicker.cpp
# End Source File
# Begin Source File

SOURCE=.\DC.cpp
# End Source File
# Begin Source File

SOURCE=.\DecimalBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Dll.cpp
# End Source File
# Begin Source File

SOURCE=.\DllMain.cpp
# End Source File
# Begin Source File

SOURCE=.\Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\EditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\File.cpp
# End Source File
# Begin Source File

SOURCE=.\FileException.cpp
# End Source File
# Begin Source File

SOURCE=.\FileFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\Font.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\HintBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Icon.cpp
# End Source File
# Begin Source File

SOURCE=.\IconCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageList.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\Library.cpp
# End Source File
# Begin Source File

SOURCE=.\List.cpp
# End Source File
# Begin Source File

SOURCE=.\ListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ListView.cpp
# End Source File
# Begin Source File

SOURCE=.\LogFont.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\MapIter.cpp
# End Source File
# Begin Source File

SOURCE=.\MemDC.cpp
# End Source File
# Begin Source File

SOURCE=.\MemStream.cpp
# End Source File
# Begin Source File

SOURCE=.\MemStreamException.cpp
# End Source File
# Begin Source File

SOURCE=.\Menu.cpp
# End Source File
# Begin Source File

SOURCE=.\Module.cpp
# End Source File
# Begin Source File

SOURCE=.\MRUList.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgThread.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\NetFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\PathEditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Pen.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Printer.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterDC.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\RadioBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\RegKey.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenDC.cpp
# End Source File
# Begin Source File

SOURCE=.\SDIApp.cpp
# End Source File
# Begin Source File

SOURCE=.\SDICmds.cpp
# End Source File
# Begin Source File

SOURCE=.\SDIDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SDIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StrCvt.cpp
# End Source File
# Begin Source File

SOURCE=.\StrCvtException.cpp
# End Source File
# Begin Source File

SOURCE=.\Stream.cpp
# End Source File
# Begin Source File

SOURCE=.\StreamException.cpp
# End Source File
# Begin Source File

SOURCE=.\String.cpp
# End Source File
# Begin Source File

SOURCE=.\StrTok.cpp
# End Source File
# Begin Source File

SOURCE=.\SysInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TabWndHost.cpp
# End Source File
# Begin Source File

SOURCE=.\ThreadJob.cpp
# End Source File
# Begin Source File

SOURCE=.\ThreadPool.cpp
# End Source File
# Begin Source File

SOURCE=.\Time.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolTip.cpp
# End Source File
# Begin Source File

SOURCE=.\TransparentBmp.cpp
# End Source File
# Begin Source File

SOURCE=.\TrayIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\UpDownBtns.cpp
# End Source File
# Begin Source File

SOURCE=.\URLLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\View.cpp
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=.\Wnd.cpp
# End Source File
# Begin Source File

SOURCE=.\WndMap.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkerThread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Accel.hpp
# End Source File
# Begin Source File

SOURCE=.\App.hpp
# End Source File
# Begin Source File

SOURCE=.\Array.hpp
# End Source File
# Begin Source File

SOURCE=.\Assert.hpp
# End Source File
# Begin Source File

SOURCE=.\AutoThreadLock.hpp
# End Source File
# Begin Source File

SOURCE=.\Bitmap.hpp
# End Source File
# Begin Source File

SOURCE=.\Brush.hpp
# End Source File
# Begin Source File

SOURCE=.\Buffer.hpp
# End Source File
# Begin Source File

SOURCE=.\BusyCursor.hpp
# End Source File
# Begin Source File

SOURCE=.\Button.hpp
# End Source File
# Begin Source File

SOURCE=.\CheckBox.hpp
# End Source File
# Begin Source File

SOURCE=.\CheckBoxList.hpp
# End Source File
# Begin Source File

SOURCE=.\Clipboard.hpp
# End Source File
# Begin Source File

SOURCE=.\CmdBmp.hpp
# End Source File
# Begin Source File

SOURCE=.\CmdBtn.hpp
# End Source File
# Begin Source File

SOURCE=.\CmdCtrl.hpp
# End Source File
# Begin Source File

SOURCE=.\ComboBox.hpp
# End Source File
# Begin Source File

SOURCE=.\ComCtl32.hpp
# End Source File
# Begin Source File

SOURCE=.\CriticalSection.hpp
# End Source File
# Begin Source File

SOURCE=.\CtrlWnd.hpp
# End Source File
# Begin Source File

SOURCE=.\Cursor.hpp
# End Source File
# Begin Source File

SOURCE=.\Date.hpp
# End Source File
# Begin Source File

SOURCE=.\DateTime.hpp
# End Source File
# Begin Source File

SOURCE=.\DateTimePicker.hpp
# End Source File
# Begin Source File

SOURCE=.\DC.hpp
# End Source File
# Begin Source File

SOURCE=.\DecimalBox.hpp
# End Source File
# Begin Source File

SOURCE=.\Dialog.hpp
# End Source File
# Begin Source File

SOURCE=.\DlgFrame.hpp
# End Source File
# Begin Source File

SOURCE=.\Dll.hpp
# End Source File
# Begin Source File

SOURCE=.\Doc.hpp
# End Source File
# Begin Source File

SOURCE=.\EditBox.hpp
# End Source File
# Begin Source File

SOURCE=.\Event.hpp
# End Source File
# Begin Source File

SOURCE=.\Exception.hpp
# End Source File
# Begin Source File

SOURCE=.\File.hpp
# End Source File
# Begin Source File

SOURCE=.\FileException.hpp
# End Source File
# Begin Source File

SOURCE=.\FileFinder.hpp
# End Source File
# Begin Source File

SOURCE=.\Font.hpp
# End Source File
# Begin Source File

SOURCE=.\FrameMenu.hpp
# End Source File
# Begin Source File

SOURCE=.\FrameWnd.hpp
# End Source File
# Begin Source File

SOURCE=.\HandleMap.hpp
# End Source File
# Begin Source File

SOURCE=.\HelpFile.hpp
# End Source File
# Begin Source File

SOURCE=.\HintBar.hpp
# End Source File
# Begin Source File

SOURCE=.\Icon.hpp
# End Source File
# Begin Source File

SOURCE=.\IconCtrl.hpp
# End Source File
# Begin Source File

SOURCE=.\ImageList.hpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.hpp
# End Source File
# Begin Source File

SOURCE=.\IntPtrMap.hpp
# End Source File
# Begin Source File

SOURCE=.\IThreadLock.hpp
# End Source File
# Begin Source File

SOURCE=.\Label.hpp
# End Source File
# Begin Source File

SOURCE=.\Library.hpp
# End Source File
# Begin Source File

SOURCE=.\List.hpp
# End Source File
# Begin Source File

SOURCE=.\ListBox.hpp
# End Source File
# Begin Source File

SOURCE=.\ListView.hpp
# End Source File
# Begin Source File

SOURCE=.\LogFont.hpp
# End Source File
# Begin Source File

SOURCE=.\MainDlg.hpp
# End Source File
# Begin Source File

SOURCE=.\MainThread.hpp
# End Source File
# Begin Source File

SOURCE=.\Map.hpp
# End Source File
# Begin Source File

SOURCE=.\MapIter.hpp
# End Source File
# Begin Source File

SOURCE=.\MemDC.hpp
# End Source File
# Begin Source File

SOURCE=.\MemStream.hpp
# End Source File
# Begin Source File

SOURCE=.\MemStreamException.hpp
# End Source File
# Begin Source File

SOURCE=.\Menu.hpp
# End Source File
# Begin Source File

SOURCE=.\Module.hpp
# End Source File
# Begin Source File

SOURCE=.\MRUList.hpp
# End Source File
# Begin Source File

SOURCE=.\MsgFilter.hpp
# End Source File
# Begin Source File

SOURCE=.\MsgThread.hpp
# End Source File
# Begin Source File

SOURCE=.\MsgWnd.hpp
# End Source File
# Begin Source File

SOURCE=.\NetFinder.hpp
# End Source File
# Begin Source File

SOURCE=.\Path.hpp
# End Source File
# Begin Source File

SOURCE=.\PathEditBox.hpp
# End Source File
# Begin Source File

SOURCE=.\Pen.hpp
# End Source File
# Begin Source File

SOURCE=.\Point.hpp
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.hpp
# End Source File
# Begin Source File

SOURCE=.\PopupWnd.hpp
# End Source File
# Begin Source File

SOURCE=.\Pragmas.hpp
# End Source File
# Begin Source File

SOURCE=.\Printer.hpp
# End Source File
# Begin Source File

SOURCE=.\PrinterDC.hpp
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.hpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPage.hpp
# End Source File
# Begin Source File

SOURCE=.\PropertySheet.hpp
# End Source File
# Begin Source File

SOURCE=.\PtrList.hpp
# End Source File
# Begin Source File

SOURCE=.\RadioBtn.hpp
# End Source File
# Begin Source File

SOURCE=.\Rect.hpp
# End Source File
# Begin Source File

SOURCE=.\RegKey.hpp
# End Source File
# Begin Source File

SOURCE=.\ScreenDC.hpp
# End Source File
# Begin Source File

SOURCE=.\SDIApp.hpp
# End Source File
# Begin Source File

SOURCE=.\SDICmds.hpp
# End Source File
# Begin Source File

SOURCE=.\SDIDoc.hpp
# End Source File
# Begin Source File

SOURCE=.\SDIFrame.hpp
# End Source File
# Begin Source File

SOURCE=.\Size.hpp
# End Source File
# Begin Source File

SOURCE=.\SplitWnd.hpp
# End Source File
# Begin Source File

SOURCE=.\StaticCtrl.hpp
# End Source File
# Begin Source File

SOURCE=.\StatusBar.hpp
# End Source File
# Begin Source File

SOURCE=.\StdWnd.hpp
# End Source File
# Begin Source File

SOURCE=.\StrArray.hpp
# End Source File
# Begin Source File

SOURCE=.\StrCvt.hpp
# End Source File
# Begin Source File

SOURCE=.\StrCvtException.hpp
# End Source File
# Begin Source File

SOURCE=.\Stream.hpp
# End Source File
# Begin Source File

SOURCE=.\StreamException.hpp
# End Source File
# Begin Source File

SOURCE=.\String.hpp
# End Source File
# Begin Source File

SOURCE=.\StrPtrMap.hpp
# End Source File
# Begin Source File

SOURCE=.\StrTok.hpp
# End Source File
# Begin Source File

SOURCE=.\SysInfo.hpp
# End Source File
# Begin Source File

SOURCE=.\TabCtrl.hpp
# End Source File
# Begin Source File

SOURCE=.\TabWndHost.hpp
# End Source File
# Begin Source File

SOURCE=.\TArray.hpp
# End Source File
# Begin Source File

SOURCE=.\Thread.hpp
# End Source File
# Begin Source File

SOURCE=.\ThreadJob.hpp
# End Source File
# Begin Source File

SOURCE=.\ThreadPool.hpp
# End Source File
# Begin Source File

SOURCE=.\Time.hpp
# End Source File
# Begin Source File

SOURCE=.\TMap.hpp
# End Source File
# Begin Source File

SOURCE=.\TMapIter.hpp
# End Source File
# Begin Source File

SOURCE=.\ToolBar.hpp
# End Source File
# Begin Source File

SOURCE=.\ToolTip.hpp
# End Source File
# Begin Source File

SOURCE=.\TransparentBmp.hpp
# End Source File
# Begin Source File

SOURCE=.\TrayIcon.hpp
# End Source File
# Begin Source File

SOURCE=.\TTree.hpp
# End Source File
# Begin Source File

SOURCE=.\UpDownBtns.hpp
# End Source File
# Begin Source File

SOURCE=.\URLLabel.hpp
# End Source File
# Begin Source File

SOURCE=.\View.hpp
# End Source File
# Begin Source File

SOURCE=.\Wcl.hpp
# End Source File
# Begin Source File

SOURCE=.\WclRsc.h
# End Source File
# Begin Source File

SOURCE=.\WclTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\Wnd.hpp
# End Source File
# Begin Source File

SOURCE=.\WndMap.hpp
# End Source File
# Begin Source File

SOURCE=.\WorkerThread.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\TODO.Txt
# End Source File
# End Target
# End Project
