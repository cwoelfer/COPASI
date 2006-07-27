/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMoiety.cpp,v $
   $Revision: 1.42 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/27 18:55:12 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <stdio.h>
#include <float.h>
#include "mathematics.h"

#include "copasi.h"
#include "CMoiety.h"
#include "CCompartment.h"
#include "CMetabNameInterface.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"//By G

#include "utilities/CCopasiMessage.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"

CMoiety::CMoiety(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Moiety"),
    mKey(GlobalKeys.add("Moiety", this)),                   //By G
    mNumber(0),
    mINumber(0),
    mEquation()
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CMoiety::CMoiety(const CMoiety & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Moiety", this)),                   //By G
    mNumber(src.mNumber),
    mINumber(src.mINumber),
    mEquation(src.mEquation)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CMoiety::~CMoiety()
{
  GlobalKeys.remove(mKey);
  DESTRUCTOR_TRACE;
}

void CMoiety::initObjects()
{
  setRefresh(this, &CMoiety::refreshDependentNumber);

  addObjectReference("Value", mINumber, CCopasiObject::ValueDbl);

  CCopasiObject * pObj =
    addObjectReference("DependentValue", mNumber, CCopasiObject::ValueDbl);

  std::set< const CCopasiObject * > Dependencies;
  Dependencies.insert(this);
  pObj->setDirectDependencies(Dependencies);

  mpRateReference =
    static_cast< CCopasiObjectReference< C_FLOAT64 > * >(addObjectReference("DependentRate", mRate, CCopasiObject::ValueDbl));
  mpRateReference->setRefresh(this, &CMoiety::refreshDependentRate);

  return;
}

void CMoiety::add(C_FLOAT64 value, CMetab * pMetabolite)
{
  pMetabolite->addMoiety(this);

  if (!mEquation.size())
    pMetabolite->setDependentOn(this);
  else
    {
      mDependencies.insert(pMetabolite->getObject(CCopasiObjectName("Reference=ParticleNumber")));

      std::set< const CCopasiObject * > Dependencies =
        mpRateReference->getDirectDependencies();
      Dependencies.insert(pMetabolite->getObject(CCopasiObjectName("Reference=ParticleNumberRate")));
      mpRateReference->setDirectDependencies(Dependencies);
    }

  std::pair<C_FLOAT64, CMetab *> element;

  element.first = value;
  element.second = pMetabolite;

  mEquation.push_back(element);
}

void CMoiety::cleanup()
{
  mDependencies.clear();
  mEquation.clear();

  std::set< const CCopasiObject *> NoDependencies;
  mpRateReference->setDirectDependencies(NoDependencies);
}

void CMoiety::refreshDependentNumber()
{
  mNumber = mINumber;

  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin() + 1;
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();
  for (; it != end; ++it)
    mNumber -= it->first * it->second->getValue();

  return;
}

void CMoiety::refreshDependentRate()
{
  mRate = 0;

  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin() + 1;
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();
  for (; it != end; ++it)
    mRate -= it->first * it->second->getRate();

  return;
}

const C_FLOAT64 & CMoiety::dependentNumber()
{
  refreshDependentNumber();
  return mNumber;
}

const C_FLOAT64 & CMoiety::getDependentNumber() const
  {return mNumber;}

const C_FLOAT64 & CMoiety::getDependentRate() const
  {return mRate;}

const std::string & CMoiety::getKey() const {return mKey;} //By G

std::string CMoiety::getDescription(const CModel * model) const
  {
    std::string Description;

    std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator it = mEquation.begin();
    std::vector< std::pair< C_FLOAT64, CMetab * > >::const_iterator end = mEquation.end();
    for (; it != end; ++it)
      {
        if (it != mEquation.begin())
          {
            if (it->first < 0.0)
              Description += " - ";
            else
              Description += " + ";
          }
        if (fabs(it->first) > 1.0 + 100 * DBL_EPSILON ||
            fabs(it->first) < 1.0 - 100 * DBL_EPSILON)
          Description += StringPrint("%g * ", fabs(it->first));

        Description += CMetabNameInterface::getDisplayName(model, *it->second);
      }
    return Description;
  }

void CMoiety::setInitialValue()
{
  mINumber = 0;

  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator it = mEquation.begin();
  std::vector< std::pair< C_FLOAT64, CMetab * > >::iterator end = mEquation.end();
  for (; it != end; ++it)
    mINumber += it->first * it->second->getInitialValue();

  return;
}

/**
 * Return the number value Wei Sun
 */
C_FLOAT64 CMoiety::getNumber() const
  {
    return mINumber;
  }
