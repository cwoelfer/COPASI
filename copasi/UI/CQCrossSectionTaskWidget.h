// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/27 16:00:44 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  Created by Paul on 5/21/10.
 */

#ifndef CQCROSSSECTIONTASKWIDGET_H
#define CQCROSSSECTIONTASKWIDGET_H

//#include <QtCore/QVariant>

#include "ui_CQCrossSectionTaskWidget.h"

#include "UI/TaskWidget.h"

class CCrossSectionProblem;
class CQValidatorInt;
class CQValidatorDouble;

class CQCrossSectionTaskWidget : public TaskWidget, public Ui::CQCrossSectionTaskWidget
{
  Q_OBJECT

public:
  CQCrossSectionTaskWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQCrossSectionTaskWidget();

  virtual bool runTask();
  //virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool saveTask();
  virtual bool loadTask();
//  virtual bool taskFinishedEvent();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:

private:
  void init();
  void destroy();

  void updateValues();

  const CCopasiObject * mpSingleVariable;
  CCrossSectionProblem * mpCrossSectionProblem;

  CQValidatorInt * mpValidatorLC;
  CQValidatorDouble * mpValidatorLT;
  CQValidatorDouble * mpValidator;
  CQValidatorDouble * mpValidatorCrossing;

private slots:

  void slotChooseVariable();
  void slotValueRate();
  void slotUpdateLC(bool);
  void slotUpdateLT(bool);
  void slotUpdateSupress(bool);
};

#endif
