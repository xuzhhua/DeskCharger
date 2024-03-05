; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgHotkey
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DeskCharger.h"

ClassCount=10
Class1=CDeskChargerApp
Class2=CDeskChargerDlg

ResourceCount=10
Resource2=IDD_CDROM
Resource3=IDD_TIMER
Resource4=IDD_DESKCHARGER_DIALOG
Resource5=IDD_ABOUT
Resource1=IDR_MAINFRAME
Class3=CDlgAbout
Class4=CDlgCDROM
Class5=CDlgHotkey
Class6=CDlgTimer
Class7=CNewTabCtrl
Resource6=IDR_TOOLBAR
Resource7=IDD_HOTKEY
Resource8=IDD_SHUTDOWN
Class8=CHKAddEdit
Class9=CColorStatic
Resource9=IDD_HOTKEYADDEDIT
Class10=CDlgShutDown
Resource10=IDR_LSTTOOLBAR

[CLS:CDeskChargerApp]
Type=0
HeaderFile=DeskCharger.h
ImplementationFile=DeskCharger.cpp
Filter=N

[CLS:CDeskChargerDlg]
Type=0
HeaderFile=DeskChargerDlg.h
ImplementationFile=DeskChargerDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDeskChargerDlg



[DLG:IDD_DESKCHARGER_DIALOG]
Type=1
Class=CDeskChargerDlg
ControlCount=3
Control1=IDC_CLOSE,button,1342242817
Control2=IDC_MAINTAB,SysTabControl32,1342177280
Control3=IDC_AUTORUN,button,1342242819

[DLG:IDD_CDROM]
Type=1
Class=CDlgCDROM
ControlCount=9
Control1=IDC_CDROMLAB,combobox,1344340291
Control2=IDC_CDROMSETHOTKEY,msctls_hotkey32,1350631424
Control3=IDC_AUTOCLOSE,edit,1350639745
Control4=IDC_AUTOEJECT,button,1342242819
Control5=IDC_SETCDROMHOTKEY,button,1342242816
Control6=IDC_SETDEFAULTCDROM,button,1342242816
Control7=IDC_SETCDROMDEFAULT,button,1342242816
Control8=IDC_LAB,static,1342308352
Control9=IDC_MAINCDROM,static,1342308352

[DLG:IDD_HOTKEY]
Type=1
Class=CDlgHotkey
ControlCount=7
Control1=IDC_HOTKEYLIST,SysListView32,1350664205
Control2=IDC_ADDHOTKEYNEW,button,1342242816
Control3=IDC_READHOTKEYINFO,button,1342242816
Control4=IDC_DELHOTKEYINFO,button,1342242816
Control5=IDC_SAVEHOTKEYINFO,button,1342242816
Control6=IDC_EDITHOTKEYINFO,button,1342242816
Control7=IDC_COMBOKEYSELECT,combobox,1344339971

[DLG:IDD_TIMER]
Type=1
Class=CDlgTimer
ControlCount=7
Control1=IDC_TIMELIST,SysListView32,1350664205
Control2=IDC_STARTTIME,button,1342242816
Control3=IDC_ADDTIMENEW,button,1342242816
Control4=IDC_READTIMEINFO,button,1342242816
Control5=IDC_DELTIMEINFO,button,1342242816
Control6=IDC_SAVETIMEINFO,button,1342242816
Control7=IDC_EDITTIMEINFO,button,1342242816

[DLG:IDD_ABOUT]
Type=1
Class=CDlgAbout
ControlCount=5
Control1=IDC_STATIC,static,1342179331
Control2=IDC_TITLE,static,1342308353
Control3=IDC_VERSION,static,1342308353
Control4=IDC_DECLARE,static,1342308353
Control5=IDC_MAIL,static,1342308353

[CLS:CDlgAbout]
Type=0
HeaderFile=DlgAbout.h
ImplementationFile=DlgAbout.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgAbout
VirtualFilter=dWC

[CLS:CDlgCDROM]
Type=0
HeaderFile=DlgCDROM.h
ImplementationFile=DlgCDROM.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgCDROM
VirtualFilter=dWC

[CLS:CDlgHotkey]
Type=0
HeaderFile=DlgHotkey.h
ImplementationFile=DlgHotkey.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgHotkey
VirtualFilter=dWC

[CLS:CDlgTimer]
Type=0
HeaderFile=DlgTimer.h
ImplementationFile=DlgTimer.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TIMELIST
VirtualFilter=dWC

[CLS:CNewTabCtrl]
Type=0
HeaderFile=NewTabCtrl.h
ImplementationFile=NewTabCtrl.cpp
BaseClass=CTabCtrl
Filter=W
VirtualFilter=UWC
LastObject=CNewTabCtrl

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=IDM_OPTION
Command2=IDM_HELP
Command3=IDM_UNINST
Command4=IDM_EXIT
CommandCount=4

[TB:IDR_LSTTOOLBAR]
Type=1
Class=?
Command1=IDM_LSTADDNEW
Command2=IDM_LSTEDIT
Command3=IDM_LSTDELCUR
CommandCount=3

[DLG:IDD_HOTKEYADDEDIT]
Type=1
Class=CHKAddEdit
ControlCount=13
Control1=IDC_HTICMD,edit,1350631552
Control2=IDC_HTIPARM,edit,1350631552
Control3=IDC_KEYCTRL,button,1342242819
Control4=IDC_KEYALT,button,1342242819
Control5=IDC_KEYSHIFT,button,1342242819
Control6=IDC_HTIINFO,edit,1350631552
Control7=IDC_ADDEDIT,button,1342242817
Control8=IDC_CLOSE,button,1342242816
Control9=IDC_LISTFILES,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[CLS:CHKAddEdit]
Type=0
HeaderFile=HKAddEdit.h
ImplementationFile=HKAddEdit.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_HTICMD
VirtualFilter=dWC

[CLS:CColorStatic]
Type=0
HeaderFile=ColorStatic.h
ImplementationFile=ColorStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CColorStatic

[DLG:IDD_SHUTDOWN]
Type=1
Class=CDlgShutDown
ControlCount=4
Control1=IDC_RESTART,button,1342242816
Control2=IDC_CLOSE,button,1342242816
Control3=IDC_STATIC,static,1342308364
Control4=IDC_STATIC,static,1342308364

[CLS:CDlgShutDown]
Type=0
HeaderFile=DlgShutDown.h
ImplementationFile=DlgShutDown.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RESTART
VirtualFilter=dWC

