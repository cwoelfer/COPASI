# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/libs/COPASISE/COPASISE.pro,v $ 
#   $Revision: 1.24 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2007/10/29 23:03:05 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# Automatically generated by qmake (1.07a) Fri Oct 27 13:32:17 2006
######################################################################

TEMPLATE = lib

SRC_TARGET = COPASISE

include(../../common.pri)

COPASI_LIBS += commandline
#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
  COPASI_LIBS += commercial
}
#endif // COPASI_LICENSE_COM
COPASI_LIBS += copasiDM
COPASI_LIBS += copasiXML
COPASI_LIBS += elementaryFluxModes
COPASI_LIBS += fitting
COPASI_LIBS += function
COPASI_LIBS += lyap
COPASI_LIBS += model
COPASI_LIBS += odepack++
COPASI_LIBS += optimization
COPASI_LIBS += plot
COPASI_LIBS += randomGenerator
COPASI_LIBS += report
COPASI_LIBS += sbmlimport
COPASI_LIBS += scan
COPASI_LIBS += sensitivities
COPASI_LIBS += steadystate
COPASI_LIBS += trajectory
COPASI_LIBS += tss
COPASI_LIBS += utilities

contains(DEFINES, WITH_LAYOUT) {
  COPASI_LIBS += layout
}

contains(DEFINES, COPASI_TSSA) {
  COPASI_LIBS += tssanalysis
}

contains(DEFINES, COPASI_MIRIAM) {
  COPASI_LIBS += MIRIAM
}

!contains(BUILD_OS, WIN32) {
  COPASI_LIBS += compareExpressions
}

include(../lib.pri)
