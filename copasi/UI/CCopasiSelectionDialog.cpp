// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CCopasiSelectionDialog.cpp,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/01 17:13:43 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "qpushbutton.h"
#include "qcheckbox.h"
#include "qhbox.h"
#include "qvbox.h"
#include "qlayout.h"
#include <qcombobox.h>

#include "CCopasiSelectionDialog.h"
#include "CCopasiSelectionWidget.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "qtUtilities.h"
#include "utilities/CAnnotatedMatrix.h"
#include "model/CModel.h"
#include "CQMatrixDialog.h"

CCopasiSelectionDialog::CCopasiSelectionDialog(QWidget * parent , const char * name , bool modal):
    QDialog(parent, name, modal),
    mpOKButton(NULL),
    mpCancelButton(NULL),
    mpModeCheckBox(NULL),
    mpButtonBox(NULL),
    mpMainWidget(NULL),
    mpMainLayout(NULL),
    mpTmpVector(new std::vector< const CCopasiObject * >()),
    mpOutputVector(NULL),
    mExpertMode(false),
    mExpertModeEnabled(true)
{
  setWFlags(this->getWFlags() | Qt::WDestructiveClose);
  mpMainLayout = new QVBoxLayout(this);

  mpSelectionWidget = new CCopasiSelectionWidget(this);
  mpMainLayout->addWidget(mpSelectionWidget);

  mpButtonBox = new QHBoxLayout(mpMainLayout);

  mpOKButton = new QPushButton(this, "OK");
  mpOKButton->setText("OK");
  mpOKButton->setDefault(true);
  mpOKButton->setAutoDefault(true);
  mpButtonBox->addWidget(mpOKButton);

  mpCancelButton = new QPushButton(this, "Cancel");
  mpCancelButton->setText("Cancel");
  mpButtonBox->addWidget(mpCancelButton);

  mpModeCheckBox = new QCheckBox("expert mode", this, "expertMode");
  mpModeCheckBox->setChecked(false);
  mpButtonBox->addWidget(mpModeCheckBox);

  // this->mpButtonBox->addSpacing(20);
  // this->mpButtonBox->addStretch();

  connect(this->mpOKButton, SIGNAL(clicked()), this, SLOT(okButton_clicked()));
  connect(this->mpCancelButton, SIGNAL(clicked()), this, SLOT(cancelButton_clicked()));
  connect(this->mpModeCheckBox, SIGNAL(toggled(bool)), this, SLOT(modeButton_toggled(bool)));

  this->mpSelectionWidget->setOutputVector(NULL);

  this->setTabOrder(this->mpOKButton, this->mpCancelButton);
  this->setTabOrder(this->mpCancelButton, this->mpModeCheckBox);
  this->setTabOrder(this->mpModeCheckBox, this->mpMainWidget);
}

CCopasiSelectionDialog::~CCopasiSelectionDialog()
{
  delete mpTmpVector;
}

void CCopasiSelectionDialog::setModel(const CModel* pModel,
                                      const CCopasiSimpleSelectionTree::SelectionFlag & flag)
{
  this->mpSelectionWidget->populateTree(pModel, flag);
}

void CCopasiSelectionDialog::setOutputVector(std::vector< const CCopasiObject * > * outputVector)
{
  this->mpSelectionWidget->setOutputVector(outputVector);
}

void CCopasiSelectionDialog::okButton_clicked()
{
  // fill outputVector
  this->mpSelectionWidget->commit();
  done(QDialog::Accepted);
}

void CCopasiSelectionDialog::cancelButton_clicked()
{
  done(QDialog::Rejected);
}

void CCopasiSelectionDialog::modeButton_toggled(bool checked)
{
  this->mpSelectionWidget->setExpertMode(checked);
}

void CCopasiSelectionDialog::setSingleSelection(bool singleSelectionMode)
{
  this->mpSelectionWidget->setSingleSelection(singleSelectionMode);
}

void CCopasiSelectionDialog::enableExpertMode(bool enable)
{
  if (enable == this->mExpertModeEnabled) return;
  this->mExpertModeEnabled = enable;
  if (!this->mExpertModeEnabled)
    {
      this->mpModeCheckBox->setChecked(false);
      this->mpModeCheckBox->hide();
    }
  else
    {
      this->mpModeCheckBox->show();
    }
}

const CCopasiObject *
CCopasiSelectionDialog::getObjectSingle(QWidget * parent,
                                        const CCopasiSimpleSelectionTree::SelectionFlag & flag,
                                        const CCopasiObject * pCurrentObject)
{
  std::vector< const CCopasiObject * > Selection;

  if (pCurrentObject != NULL)
    Selection.push_back(pCurrentObject);

  CCopasiSelectionDialog * pDialog = new CCopasiSelectionDialog(parent);
  pDialog->setModel(CCopasiDataModel::Global->getModel(), flag);
  pDialog->setSingleSelection(true);
  pDialog->setOutputVector(&Selection);

  int Result = pDialog->exec();

  if (Result == QDialog::Accepted && Selection.size() != 0)
    //    return Selection[0];
    {
      const CCopasiObject *pObject = Selection[0];

      chooseCellMatrix(pObject);

      return Selection[0];
    }

  if (Result == QDialog::Rejected && pCurrentObject != NULL)
    return pCurrentObject;

  return NULL;
}

std::vector< const CCopasiObject * > CCopasiSelectionDialog::getObjectVector(QWidget * parent,
    const CCopasiSimpleSelectionTree::SelectionFlag & flag,
    const std::vector< const CCopasiObject * > * pCurrentSelection)
{
  std::vector< const CCopasiObject * > Selection;
  if (pCurrentSelection)
    Selection = *pCurrentSelection;

  CCopasiSelectionDialog * pDialog = new CCopasiSelectionDialog(parent);
  pDialog->setModel(CCopasiDataModel::Global->getModel(), flag);
  pDialog->setSingleSelection(false);
  pDialog->setOutputVector(&Selection);

  if (pDialog->exec() == QDialog::Rejected && pCurrentSelection)
    return *pCurrentSelection; // TO DO: What is different between *pCurrentSelection and Selection ??
  else
    //    return Selection;
    {
      std::vector< const CCopasiObject * >::iterator itSelection = Selection.begin();

      for (; itSelection != Selection.end(); ++itSelection)
        {
          const CCopasiObject *pObject = *itSelection;
          QString str = FROM_UTF8(pObject->getObjectType()) + "=" + FROM_UTF8(pObject->getObjectName());

          if (str == "Reference=Annotated Matrix")
            {
              const CArrayAnnotation * tmp;

              QString strAux = FROM_UTF8(pObject->getObjectParent()->getObjectType()) + "=" + FROM_UTF8(pObject->getObjectParent()->getObjectName());
              //  tmp = dynamic_cast<const CArrayAnnotation *> (pModel->getObject(CCopasiObjectName(strAux)));
              tmp = dynamic_cast<const CArrayAnnotation *> (pObject->getObjectParent()->getObject(CCopasiObjectName((const char*) strAux.utf8())));
              if (!tmp)
                return std::vector< const CCopasiObject * >();
              /*     if (!tmp && pCurrentSelection)
                  return *pCurrentSelection;
              //     if (!tmp)
              //    return NULL;
              */
              int nRows = tmp->getAnnotationsCN(0).size();
              int nCols = tmp->getAnnotationsCN(1).size();

              if (!nRows || !nCols)
                return std::vector< const CCopasiObject * >();
              /*
                if (!nRows || !nCols)
                  return *pCurrentSelection;
              //    return NULL;
              */
              CQMatrixDialog *dialog = new CQMatrixDialog();
              dialog->setArray(tmp);

              int Result = dialog->exec();
              /*
                if (Result == QDialog::Rejected)
                  return *pCurrentSelection;
              //  if (Result == QDialog::Rejected)
              //    return NULL;
              */
              if (Result == QDialog::Rejected)
                return std::vector< const CCopasiObject * >();
              else if (Result == QDialog::Accepted)
                std::cout << dialog->mpCBRow->currentText() << " AND " << dialog->mpCBColumn->currentText() << std::endl;
            }
        }

      return Selection;
    }
}

void CCopasiSelectionDialog::chooseCellMatrix(const CCopasiObject *pObject)
{
  QString str = FROM_UTF8(pObject->getObjectType()) + "=" + FROM_UTF8(pObject->getObjectName());

  if (str == "Reference=Annotated Matrix")
    {
      const CArrayAnnotation * tmp;

      QString strAux = FROM_UTF8(pObject->getObjectParent()->getObjectType()) + "=" + FROM_UTF8(pObject->getObjectParent()->getObjectName());
      //      tmp = dynamic_cast<const CArrayAnnotation *> (pModel->getObject(CCopasiObjectName(strAux)));
      tmp = dynamic_cast<const CArrayAnnotation *> (pObject->getObjectParent()->getObject(CCopasiObjectName((const char*) strAux.utf8())));
      if (!tmp)
        return;

      int nRows = tmp->getAnnotationsCN(0).size();
      int nCols = tmp->getAnnotationsCN(1).size();

      if (!nRows || !nCols)
        return;

      CQMatrixDialog *dialog = new CQMatrixDialog();
      dialog->setArray(tmp);

      int Result = dialog->exec();

      if (Result == QDialog::Rejected)
        return;
      else if (Result == QDialog::Accepted)
        std::cout << dialog->mpCBRow->currentText() << " AND " << dialog->mpCBColumn->currentText() << std::endl;
    }
}
