# Microsoft Developer Studio Project File - Name="DeskCharger" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DeskCharger - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DeskCharger.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DeskCharger.mak" CFG="DeskCharger - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DeskCharger - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DeskCharger - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DeskCharger - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DeskCharger - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DeskCharger - Win32 Release"
# Name "DeskCharger - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\DeskCharger.cpp
# End Source File
# Begin Source File

SOURCE=.\DeskCharger.rc
# End Source File
# Begin Source File

SOURCE=.\DeskChargerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCDROM.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHotkey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShutDown.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\HECDROM.CPP
# End Source File
# Begin Source File

SOURCE=.\HEHotExec.cpp
# End Source File
# Begin Source File

SOURCE=.\HETime.cpp
# End Source File
# Begin Source File

SOURCE=.\HKAddEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\HotKeyExec.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\NewTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinXPButtonST.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.h
# End Source File
# Begin Source File

SOURCE=.\DeskCharger.h
# End Source File
# Begin Source File

SOURCE=.\DeskChargerDlg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.h
# End Source File
# Begin Source File

SOURCE=.\DlgCDROM.h
# End Source File
# Begin Source File

SOURCE=.\DlgHotkey.h
# End Source File
# Begin Source File

SOURCE=.\DlgShutDown.h
# End Source File
# Begin Source File

SOURCE=.\DlgTimer.h
# End Source File
# Begin Source File

SOURCE=.\HECDROM.H
# End Source File
# Begin Source File

SOURCE=.\HEHotExec.h
# End Source File
# Begin Source File

SOURCE=.\HETime.h
# End Source File
# Begin Source File

SOURCE=.\HKAddEdit.h
# End Source File
# Begin Source File

SOURCE=.\HotKeyExec.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\NewTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinXPButtonST.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AbNormal.ico
# End Source File
# Begin Source File

SOURCE=.\res\AbNormalxp.ico
# End Source File
# Begin Source File

SOURCE=.\CDROM.ico
# End Source File
# Begin Source File

SOURCE=.\res\CDROM.ico
# End Source File
# Begin Source File

SOURCE=.\default.ico
# End Source File
# Begin Source File

SOURCE=.\res\default.ico
# End Source File
# Begin Source File

SOURCE=.\del.ico
# End Source File
# Begin Source File

SOURCE=.\res\del.ico
# End Source File
# Begin Source File

SOURCE=.\res\DeskCharger.ico
# End Source File
# Begin Source File

SOURCE=.\res\DeskCharger.rc2
# End Source File
# Begin Source File

SOURCE=.\Disable.ico
# End Source File
# Begin Source File

SOURCE=.\res\Disable.ico
# End Source File
# Begin Source File

SOURCE=.\edit.ico
# End Source File
# Begin Source File

SOURCE=.\res\edit.ico
# End Source File
# Begin Source File

SOURCE=.\Enable.ico
# End Source File
# Begin Source File

SOURCE=.\res\Enable.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\lsttoolb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lsttoolb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MainFrame.ico
# End Source File
# Begin Source File

SOURCE=.\new.ico
# End Source File
# Begin Source File

SOURCE=.\res\new.ico
# End Source File
# Begin Source File

SOURCE=.\res\Normal.ico
# End Source File
# Begin Source File

SOURCE=.\res\Normalxp.ico
# End Source File
# Begin Source File

SOURCE=".\Open Folder 3.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Open Folder 3.ico"
# End Source File
# Begin Source File

SOURCE=".\Open Folder 4.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Open Folder 4.ico"
# End Source File
# Begin Source File

SOURCE=".\Open Folder.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Open Folder.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Openfile.ico
# End Source File
# Begin Source File

SOURCE=.\read.ico
# End Source File
# Begin Source File

SOURCE=.\res\read.ico
# End Source File
# Begin Source File

SOURCE=.\res\Restart.ico
# End Source File
# Begin Source File

SOURCE=.\res\Save.ico
# End Source File
# Begin Source File

SOURCE=.\Save.ico
# End Source File
# Begin Source File

SOURCE=.\res\setting.ico
# End Source File
# Begin Source File

SOURCE=.\setting.ico
# End Source File
# Begin Source File

SOURCE=.\res\ShutDown.ico
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Timing.ico
# End Source File
# Begin Source File

SOURCE=.\Timing.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\DeskCharger.exe.manifest.xml
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
