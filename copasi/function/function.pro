######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2005/05/27 16:58:08 $  
######################################################################

LIB = function

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCallParameters.h \
           CEvaluationNode.h \
           CEvaluationNodeConstant.h \
           CEvaluationNodeNumber.h \
           CEvaluationNodeOperator.h \
           CFunction.h \
           CFunctionDB.h \
           CFunctionParameter.h \
           CFunctionParameters.h \
           CKinFunction.h \
           CMassAction.h \
           CNodeK.h \
           CRange.h \
           CUsageRange.h

SOURCES += CCallParameters.cpp \
           CEvaluationNode.cpp \
           CEvaluationNodeConstant.cpp \
           CEvaluationNodeNumber.cpp \
           CEvaluationNodeOperator.cpp \
           CFunction.cpp \
           CFunctionDB.cpp \
           CFunctionParameter.cpp \
           CFunctionParameters.cpp \
           CKinFunction.cpp \
           CKinFunctionFlexLexer.cpp \
           CMassAction.cpp \
           CNodeK.cpp \
           CRange.cpp \
           CUsageRange.cpp

1.target   = CKinFunctionFlexLexer.cpp
1.depends  = CKinFunctionFlexLexer.lpp 
1.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 1

2.target   = CEvaluationFlexLexer.cpp
2.depends  = CEvaluationFlexLexer.lpp 
2.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 2

