// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "ListOfUnsupportedAnnotationsHandler.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"

/**
 * Replace Model with the name type of the handler and implement the
 * three methods below.
 */
ModelHandler::ModelHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Model),
  mKey()
{
  init();
}

// virtual
ModelHandler::~ModelHandler()
{}

// virtual
CXMLHandler * ModelHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  const char * Name;
  const char * timeUnit;
  const char * volumeUnit;
  const char * areaUnit;
  const char * lengthUnit;
  const char * quantityUnit;
  CModel::ModelType ModelType;
  C_FLOAT64 Avogadro;

  switch (mCurrentElement.first)
    {
      case Model:

        if (strcmp(pszName, "Model"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "Model", mpParser->getCurrentLineNumber());

        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);

        timeUnit = mpParser->getAttributeValue("timeUnit", papszAttrs);

        volumeUnit = mpParser->getAttributeValue("volumeUnit", papszAttrs);

        //the next 2 attributes are introduced in Build 31, they have a default for
        //reading older cps files
        areaUnit = mpParser->getAttributeValue("areaUnit", papszAttrs, "m\xc2\xb2");

        lengthUnit = mpParser->getAttributeValue("lengthUnit", papszAttrs, "m");

        quantityUnit = mpParser->getAttributeValue("quantityUnit", papszAttrs);

        ModelType = toEnum(mpParser->getAttributeValue("type", papszAttrs, "deterministic"),
                           CModel::ModelTypeNames, CModel::deterministic);

        {
          const char * tmp = mpParser->getAttributeValue("avogadroConstant", papszAttrs, false);

          if (tmp == NULL)
            Avogadro = CUnit::Avogadro;
          else
            Avogadro = CCopasiXMLInterface::DBL(tmp);
        }

        if (!mpData->pModel) mpData->pModel = new CModel(mpData->pDataModel);

        // We remove the default parameter set:
        mpData->pModel->getModelParameterSets().CCopasiVector< CModelParameterSet >::remove((size_t) 0);

        addFix(mKey, mpData->pModel);
        mpData->pModel->setObjectName(Name);
        mpData->pModel->setTimeUnit(timeUnit);
        mpData->pModel->setVolumeUnit(volumeUnit);
        mpData->pModel->setAreaUnit(areaUnit);
        mpData->pModel->setLengthUnit(lengthUnit);
        mpData->pModel->setQuantityUnit(quantityUnit, CModelParameter::ParticleNumbers);
        mpData->pModel->setModelType(ModelType);
        mpData->pModel->setAvogadro(Avogadro, CModelParameter::ParticleNumbers);

        break;

      case MiriamAnnotation:
      case Comment:
      case ListOfUnsupportedAnnotations:
      case InitialExpression:
      case ListOfCompartments:
      case ListOfMetabolites:
      case ListOfModelValues:
      case ListOfReactions:
      case ListOfEvents:
      case ListOfModelParameterSets:
      case StateTemplate:
      case InitialState:
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
bool ModelHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Model:
        finished = true;
        mpData->pModel->setCompileFlag(true);
        break;

      case MiriamAnnotation:
        mpData->pModel->setMiriamAnnotation(mpData->CharacterData, mpData->pModel->getKey(), mKey);
        mpData->CharacterData = "";
        break;

      case Comment:
        mpData->pModel->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

      {
        ListOfUnsupportedAnnotationsHandler * pHandler = static_cast< ListOfUnsupportedAnnotationsHandler * >(getHandler(ListOfUnsupportedAnnotations));
        mpData->pModel->getUnsupportedAnnotations() = pHandler->getUnsupportedAnnotations();
      }

      break;

      case InitialExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpData->pModel->setInitialExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case ListOfCompartments:
      case ListOfMetabolites:
      case ListOfModelValues:
      case ListOfReactions:
      case ListOfEvents:
      case ListOfModelParameterSets:
      case StateTemplate:
      case InitialState:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModelHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Model, HANDLER_COUNT}},
    {"Model", Model, Model, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, InitialExpression, ListOfCompartments, ListOfMetabolites, ListOfModelValues, ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, InitialExpression, ListOfCompartments, ListOfMetabolites, ListOfModelValues, ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {Comment, ListOfUnsupportedAnnotations, InitialExpression, ListOfCompartments, ListOfMetabolites, ListOfModelValues, ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {InitialExpression, ListOfCompartments, ListOfMetabolites, ListOfModelValues, ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    // Old CopasiML files have the incorrect order and the comment may appear after the initial expression. Therefore, we reset to MiriamAnnotation.
    {"InitialExpression", InitialExpression, CharacterData, {MiriamAnnotation, ListOfCompartments, ListOfMetabolites, ListOfModelValues, ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"ListOfCompartments", ListOfCompartments, ListOfCompartments, {ListOfCompartments, ListOfMetabolites, ListOfModelValues, ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"ListOfMetabolites", ListOfMetabolites, ListOfMetabolites, {ListOfModelValues, ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"ListOfModelValues", ListOfModelValues, ListOfModelValues, {ListOfReactions, ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"ListOfReactions", ListOfReactions, ListOfReactions, {ListOfEvents, ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"ListOfEvents", ListOfEvents, ListOfEvents, {ListOfModelParameterSets, StateTemplate, HANDLER_COUNT}},
    {"ListOfModelParameterSets", ListOfModelParameterSets, ListOfModelParameterSets, {StateTemplate, AFTER, HANDLER_COUNT}},
    {"StateTemplate", StateTemplate, StateTemplate, {InitialState, AFTER, HANDLER_COUNT}},
    {"InitialState", InitialState, InitialState, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
