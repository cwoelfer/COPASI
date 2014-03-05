// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "test000034.h"

#include <sstream>
#include "utilities.hpp"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CExpression.h"

#include "copasi/report/CCopasiRootContainer.h"

CCopasiDataModel* test000034::pCOPASIDATAMODEL = NULL;

void test000034::setUp()
{
  // Create the root container.
  CCopasiRootContainer::init(0, NULL, false);
  // Create the global data model.
  pCOPASIDATAMODEL = CCopasiRootContainer::addDatamodel();
}

void test000034::tearDown()
{
  CCopasiRootContainer::destroy();
}

void test000034::test_hasOnlySubstanceUnits()
{
  CCopasiDataModel* pDataModel = pCOPASIDATAMODEL;
  CPPUNIT_ASSERT(pDataModel->importSBMLFromString(MODEL_STRING));
  CModel* pModel = pDataModel->getModel();
  CPPUNIT_ASSERT(pModel != NULL);
  CPPUNIT_ASSERT(pModel->getQuantityUnitEnum() == CUnit::mMol);
  CPPUNIT_ASSERT(pModel->getVolumeUnitEnum() == CUnit::ml);
  CPPUNIT_ASSERT(pModel->getTimeUnitEnum() == CUnit::s);
  CPPUNIT_ASSERT(pModel->getCompartments().size() == 1);
  const CCompartment* pCompartment = pModel->getCompartments()[0];
  CPPUNIT_ASSERT(pCompartment != NULL);
  CPPUNIT_ASSERT(pCompartment->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(pModel->getMetabolites().size() == 2);
  CMetab* pA = pModel->getMetabolites()[0];
  CPPUNIT_ASSERT(pA != NULL);
  CPPUNIT_ASSERT(pA->getStatus() == CModelEntity::REACTIONS);
  const CMetab* pB = pModel->getMetabolites()[1];
  CPPUNIT_ASSERT(pB != NULL);
  CPPUNIT_ASSERT(pB->getStatus() == CModelEntity::REACTIONS);
  CPPUNIT_ASSERT(pModel->getModelValues().size() == 2);
  // check the factor
  const CModelValue* pFactor = pModel->getModelValues()[1];
  CPPUNIT_ASSERT(pFactor != NULL);
  CPPUNIT_ASSERT(pFactor->getStatus() == CModelEntity::FIXED);
  CPPUNIT_ASSERT(fabs((pFactor->getInitialValue() - pModel->getQuantity2NumberFactor()) / pModel->getQuantity2NumberFactor()) < 1e-3);
  const CModelValue* pModelValue = pModel->getModelValues()[0];
  CPPUNIT_ASSERT(pModelValue != NULL);
  CPPUNIT_ASSERT(pModelValue->getStatus() == CModelEntity::ODE);
  const CExpression* pExpr = pModelValue->getExpressionPtr();
  // check the expression
  const CEvaluationNode* pNode = pExpr->getRoot();
  CPPUNIT_ASSERT(pNode != NULL);
  const CEvaluationNodeObject* pObjectNode = dynamic_cast<const CEvaluationNodeObject*>(pNode);
  CPPUNIT_ASSERT(pObjectNode != NULL);
  CCopasiObjectName objectCN = pObjectNode->getObjectCN();
  CPPUNIT_ASSERT(!objectCN.empty());
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  const CCopasiObject* pObject = CObjectInterface::DataModel(pCOPASIDATAMODEL->ObjectFromCN(listOfContainers, objectCN));
  CPPUNIT_ASSERT(pObject != NULL);
  CPPUNIT_ASSERT(pObject->isReference() == true);
  CPPUNIT_ASSERT(pObject->getObjectName() == std::string("ParticleNumber"));
  CPPUNIT_ASSERT(pObject->getObjectParent() == pA);
  // check the kinetic laws
  CPPUNIT_ASSERT(pModel->getReactions().size() == 2);
  const CReaction* pReaction1 = pModel->getReactions()[0];
  CPPUNIT_ASSERT(pReaction1 != NULL);
  CPPUNIT_ASSERT(pReaction1->isReversible() == false);
  // check the kinetic law
  const CFunction* pKineticFunction = pReaction1->getFunction();
  CPPUNIT_ASSERT(pKineticFunction != NULL);
  const CMassAction* pMassAction = dynamic_cast<const CMassAction*>(pKineticFunction);
  //FTB: this no longer is recognized as mass action reaction because of the
  //     special case of a species with hOSU
  CPPUNIT_ASSERT(pMassAction == NULL);
  const CChemEq* pChemEq = &pReaction1->getChemEq();
  CPPUNIT_ASSERT(pChemEq != NULL);
  CPPUNIT_ASSERT(pChemEq->getCompartmentNumber() == 1);
  CPPUNIT_ASSERT(pChemEq->getSubstrates().size() == 1);
  const CChemEqElement* pElement = pChemEq->getSubstrates()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pA);
  CPPUNIT_ASSERT(pChemEq->getProducts().size() == 0);
  CPPUNIT_ASSERT(pChemEq->getModifiers().size() == 0);

  const CReaction* pReaction2 = pModel->getReactions()[1];
  CPPUNIT_ASSERT(pReaction2 != NULL);
  CPPUNIT_ASSERT(pReaction2->isReversible() == false);
  // check the kinetic law
  pKineticFunction = pReaction2->getFunction();
  CPPUNIT_ASSERT(pKineticFunction != NULL);
  CPPUNIT_ASSERT(pKineticFunction->getObjectName() == std::string("Henri-Michaelis-Menten (irreversible)"));
  // check the function parameters one should be the reference to the substrate
  pChemEq = &pReaction2->getChemEq();
  CPPUNIT_ASSERT(pChemEq != NULL);
  CPPUNIT_ASSERT(pChemEq->getCompartmentNumber() == 1);
  CPPUNIT_ASSERT(pChemEq->getSubstrates().size() == 1);
  pElement = pChemEq->getSubstrates()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pA);
  CPPUNIT_ASSERT(pChemEq->getProducts().size() == 1);
  pElement = pChemEq->getProducts()[0];
  CPPUNIT_ASSERT(pElement != NULL);
  CPPUNIT_ASSERT(fabs(pElement->getMultiplicity() - 1.0) < 1e-3);
  CPPUNIT_ASSERT(pElement->getMetabolite() == pB);
  CPPUNIT_ASSERT(pChemEq->getModifiers().size() == 0);
  const std::vector<std::vector<std::string> > parameterMappings = pReaction2->getParameterMappings();
  CPPUNIT_ASSERT(parameterMappings.size() == 3);
  CPPUNIT_ASSERT(parameterMappings[0].size() == 1);
  const std::string parameterKey = parameterMappings[0][0];
  CPPUNIT_ASSERT(parameterKey == pA->getKey());
}

const char* test000034::MODEL_STRING =
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<sbml xmlns=\"http://www.sbml.org/sbml/level2/version3\" level=\"2\" version=\"3\">\n"
  "    <notes>\n"
  "      <body xmlns=\"http://www.w3.org/1999/xhtml\">\n"
  "        <p>Model with fixed compartment volume, two species with hasOnlySubstanceUnits flag set to true. The units are set to ml and mMol. There is an ode rule for the global parameter that contains a reference to species A multiplied by a constant parameter.</p>\n"
  "        <p>The imported model should contain an ode rule for the global parameter that consists of the reference to the particle number of species A. The species references in the reactions should be imported multiplied by the volume.</p>\n"
  "      </body>\n"
  "    </notes>\n"
  "  <model id=\"Model_1\" name=\"New Model\">\n"
  "    <listOfFunctionDefinitions>\n"
  "      <functionDefinition id=\"function_1\" name=\"Henri-Michaelis-Menten (irreversible)\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <lambda>\n"
  "            <bvar>\n"
  "              <ci> substrate </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> Km </ci>\n"
  "            </bvar>\n"
  "            <bvar>\n"
  "              <ci> V </ci>\n"
  "            </bvar>\n"
  "            <apply>\n"
  "              <divide/>\n"
  "              <apply>\n"
  "                <times/>\n"
  "                <ci> V </ci>\n"
  "                <ci> substrate </ci>\n"
  "              </apply>\n"
  "              <apply>\n"
  "                <plus/>\n"
  "                <ci> Km </ci>\n"
  "                <ci> substrate </ci>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </lambda>\n"
  "        </math>\n"
  "      </functionDefinition>\n"
  "    </listOfFunctionDefinitions>\n"
  "    <listOfUnitDefinitions>\n"
  "      <unitDefinition id=\"volume\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"litre\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "      <unitDefinition id=\"substance\">\n"
  "        <listOfUnits>\n"
  "          <unit kind=\"mole\" scale=\"-3\"/>\n"
  "        </listOfUnits>\n"
  "      </unitDefinition>\n"
  "    </listOfUnitDefinitions>\n"
  "    <listOfCompartments>\n"
  "      <compartment id=\"compartment_1\" name=\"compartment\" size=\"1\"/>\n"
  "    </listOfCompartments>\n"
  "    <listOfSpecies>\n"
  "      <species id=\"species_1\" name=\"A\" compartment=\"compartment_1\" initialAmount=\"1\" hasOnlySubstanceUnits=\"true\"/>\n"
  "      <species id=\"species_2\" name=\"B\" compartment=\"compartment_1\" initialAmount=\"1\" hasOnlySubstanceUnits=\"true\"/>\n"
  "    </listOfSpecies>\n"
  "    <listOfParameters>\n"
  "      <parameter id=\"parameter_1\" name=\"K\" value=\"0\" constant=\"false\"/>\n"
  "      <parameter id=\"parameter_2\" name=\"F\" value=\"6.0221415e20\" constant=\"true\"/>\n"
  "    </listOfParameters>\n"
  "    <listOfRules>\n"
  "      <rateRule variable=\"parameter_1\">\n"
  "        <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "          <apply>\n"
  "            <times/>\n"
  "            <ci> species_1 </ci>\n"
  "            <ci> parameter_2 </ci>\n"
  "          </apply>\n"
  "        </math>\n"
  "      </rateRule>\n"
  "    </listOfRules>\n"
  "    <listOfReactions>\n"
  "      <reaction id=\"reaction_1\" name=\"reaction_0\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> k1 </ci>\n"
  "              <ci> species_1 </ci>\n"
  "            </apply>\n"
  "          </math>\n"
  "          <listOfParameters>\n"
  "            <parameter id=\"k1\" value=\"0.1\"/>\n"
  "          </listOfParameters>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "      <reaction id=\"reaction_2\" name=\"reaction_1\" reversible=\"false\">\n"
  "        <listOfReactants>\n"
  "          <speciesReference species=\"species_1\"/>\n"
  "        </listOfReactants>\n"
  "        <listOfProducts>\n"
  "          <speciesReference species=\"species_2\"/>\n"
  "        </listOfProducts>\n"
  "        <kineticLaw>\n"
  "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
  "            <apply>\n"
  "              <times/>\n"
  "              <ci> compartment_1 </ci>\n"
  "              <apply>\n"
  "                <ci> function_1 </ci>\n"
  "                <apply>\n"
  "                  <divide/>\n"
  "                  <ci> species_1 </ci>\n"
  "                  <ci> compartment_1 </ci>\n"
  "                </apply>  \n"
  "                <ci> Km </ci>\n"
  "                <ci> V </ci>\n"
  "              </apply>\n"
  "            </apply>\n"
  "          </math>\n"
  "          <listOfParameters>\n"
  "            <parameter id=\"Km\" value=\"0.1\"/>\n"
  "            <parameter id=\"V\" value=\"0.1\"/>\n"
  "          </listOfParameters>\n"
  "        </kineticLaw>\n"
  "      </reaction>\n"
  "    </listOfReactions>\n"
  "  </model>\n"
  "</sbml>\n"
  ;
