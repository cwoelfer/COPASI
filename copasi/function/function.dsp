# Microsoft Developer Studio Project File - Name="function" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=function - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "function.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "function.mak" CFG="function - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "function - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "function - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "function - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy
PostBuild_Cmds=copy Release\*.lib ..\Release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "function - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../copasi" /I "../.." /I "$(CBLAS_LIB)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy
PostBuild_Cmds=copy Debug\*.lib ..\Debug
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "function - Win32 Release"
# Name "function - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\CFunctionDB.cpp
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\CKinFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\CMassAction.cpp
# End Source File
# Begin Source File

SOURCE=.\CNodeK.cpp
# End Source File
# Begin Source File

SOURCE=.\CRange.cpp
# End Source File
# Begin Source File

SOURCE=.\CUsageRange.cpp
# End Source File
# Begin Source File

SOURCE=.\lexkk.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCallParameter.h
# End Source File
# Begin Source File

SOURCE=.\CCallParameters.h
# End Source File
# Begin Source File

SOURCE=.\CFunction.h
# End Source File
# Begin Source File

SOURCE=.\CFunctionDB.h
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameter.h
# End Source File
# Begin Source File

SOURCE=.\CFunctionParameters.h
# End Source File
# Begin Source File

SOURCE=.\CKinFunction.h
# End Source File
# Begin Source File

SOURCE=.\CMassAction.h
# End Source File
# Begin Source File

SOURCE=.\CNodeK.h
# End Source File
# Begin Source File

SOURCE=.\CRange.h
# End Source File
# Begin Source File

SOURCE=.\CUsageRange.h
# End Source File
# Begin Source File

SOURCE=.\function.h
# End Source File
# Begin Source File

SOURCE=.\lexkk.h
# End Source File
# End Group
# End Target
# End Project
