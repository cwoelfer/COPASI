// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CallParameterHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "function/CFunctionParameter.h"

/**
 * Replace CallParameter with the name type of the handler and implement the
 * three methods below.
 */
CallParameterHandler::CallParameterHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::CallParameter)
{
  init();
}

// virtual
CallParameterHandler::~CallParameterHandler()
{}

// virtual
CXMLHandler * CallParameterHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * FunctionParameter;

  switch (mCurrentElement.first)
    {
      case CallParameter:
        FunctionParameter =
          mpParser->getAttributeValue("functionParameter", papszAttrs);

        mpData->pFunctionVariable =
          dynamic_cast< CFunctionParameter* >(mpData->mKeyMap.get(FunctionParameter));

        if (!mpData->pFunctionVariable)
          {
            fatalError();
          }

        break;

      case SourceParameter:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool CallParameterHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case CallParameter:
        finished = true;
        break;

      case SourceParameter:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CallParameterHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {CallParameter, HANDLER_COUNT}},
    {"CallParameter", CallParameter, CallParameter, {SourceParameter, HANDLER_COUNT}},
    {"SourceParameter", SourceParameter, SourceParameter, {SourceParameter, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
