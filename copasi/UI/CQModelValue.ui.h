// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQModelValue.ui.h,v $
//   $Revision: 1.22 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/04/01 11:23:20 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "function/CExpression.h"
#include "report/CKeyFactory.h"

/*!
    After clicking the Commit button, COPASI will internally, automatically save any inputs and load them.
 */
void CQModelValue::slotBtnCommit()
{
  save();
  load();
}

void CQModelValue::slotBtnRevert()
{
  load();
}

void CQModelValue::slotBtnNew()
{
  save();

  std::string name = "quantity";
  int i = 0;

  while (!(mpModelValue = CCopasiDataModel::Global->getModel()->createModelValue(name)))
    {
      i++;
      name = "quantity_";
      name += (const char *) QString::number(i).utf8();
    }

  enter(mpModelValue->getKey());
  protectedNotify(ListViews::MODELVALUE, ListViews::ADD);
}

void CQModelValue::slotBtnDelete()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;
  /*
  std::set< const CCopasiObject * > DeletedObjects;
  unsigned C_INT32 NumberDeleted = 0;
  */

  QString valueList = "Are you sure you want to delete listed MODEL VALUE(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedMetabList = "Following SPECIES reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above MODEL VALUE(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above MODEL VALUE(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  valueList.append(FROM_UTF8(mpModelValue->getObjectName()));
  valueList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(mpModelValue->getDeletedObjects(),
                                      Reactions, Metabolites, Compartments, Values);

  if (Reactions.size() > 0)
    {
      reacFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();
      for (it = Reactions.begin(); it != itEnd; ++it)
        {
          effectedReacList.append(FROM_UTF8((*it)->getObjectName()));
          effectedReacList.append(", ");
        }

      effectedReacList.remove(effectedReacList.length() - 2, 2);
      effectedReacList.append("  ---> ");
      effectedReacList.append(FROM_UTF8(mpModelValue->getObjectName()));
      effectedReacList.append("\n");
    }

  if (Metabolites.size() > 0)
    {
      metabFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();
      for (it = Metabolites.begin(); it != itEnd; ++it)
        {
          effectedMetabList.append(FROM_UTF8((*it)->getObjectName()));
          effectedMetabList.append(", ");
        }

      effectedMetabList.remove(effectedMetabList.length() - 2, 2);
      effectedMetabList.append("  ---> ");
      effectedMetabList.append(FROM_UTF8(mpModelValue->getObjectName()));
      effectedMetabList.append("\n");
    }

  if (Values.size() > 0)
    {
      valueFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();
      for (it = Values.begin(); it != itEnd; ++it)
        {
          effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
          effectedValueList.append(", ");
        }

      effectedValueList.remove(effectedValueList.length() - 2, 2);
      effectedValueList.append("  ---> ");
      effectedValueList.append(FROM_UTF8(mpModelValue->getObjectName()));
      effectedValueList.append("\n");
    }

  if (Compartments.size() > 0)
    {
      compartmentFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();
      for (it = Compartments.begin(); it != itEnd; ++it)
        {
          effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
          effectedCompartmentList.append(", ");
        }

      effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
      effectedCompartmentList.append("  ---> ");
      effectedCompartmentList.append(FROM_UTF8(mpModelValue->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  valueList.remove(valueList.length() - 2, 2);

  QString msg = valueList;

  if (compartmentFound)
    {
      msg.append("\n \n");
      msg.append(effectedCompartmentList);
    }

  if (metabFound)
    {
      msg.append("\n \n");
      msg.append(effectedMetabList);
    }

  if (reacFound)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  if (valueFound)
    {
      msg.append("\n \n");
      msg.append(effectedValueList);
    }

  C_INT32 choice = 0;
  if (metabFound || reacFound || valueFound || valueFound)
    choice = CQMessageBox::question(this,
                                    "CONFIRM DELETE",
                                    msg,
                                    "Continue", "Cancel", 0, 1, 1);

  switch (choice)
    {
    case 0:  // Yes or Enter
      {
        unsigned C_INT32 index =
          static_cast<CCopasiVector< CModelValue > *>(&CCopasiDataModel::Global->getModel()->getModelValues())->getIndex(GlobalKeys.get(mKey));

        CCopasiDataModel::Global->getModel()->removeModelValue(mKey);
        unsigned C_INT32 size =
          CCopasiDataModel::Global->getModel()->getModelValues().size();

        mpModelValue = NULL;

        if (size > 0)
          enter(CCopasiDataModel::Global->getModel()->getModelValues()[std::min(index, size - 1)]->getKey());
        else
          enter("");

#undef DELETE
        protectedNotify(ListViews::MODELVALUE, ListViews::DELETE, mKey);
        break;
      }

    default:  // No or Escape
      break;
    }
}

/*!
    If the simulation type is changed then COPASI will automatically adjust its appearance,
    especially correlating to the Expression Widget and its buttons.
 */
void CQModelValue::slotTypeChanged(int type)
{
  switch ((CModelEntity::Status) mItemToType[type])
    {
    case CModelEntity::FIXED:
      // remove expression layout from GUI screen
      CQModelValueLayout->removeItem(mpHBoxLayoutExpression);
      CQModelValueLayout->remove(mpLblExpression);

      // hide label, widget, and all buttons
      mpLblExpression->hide();
      mpEditExpression->hide();
      mpBtnExpressionObject->hide();
      mpBtnEditExpression->hide();

      // enable the option of use Initial Expression
      mpBoxUseInitialExpression->setEnabled(true);
      slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

      // we don't need to update the expression widget as it is already hidden

      break;

    case CModelEntity::ASSIGNMENT:
      // add expression layout
      CQModelValueLayout->addWidget(mpLblExpression, 2, 0);
      CQModelValueLayout->addMultiCellLayout(mpHBoxLayoutExpression, 2, 2, 1, 2);

      // show label, widget, and correct buttons
      mpLblExpression->show();   // show the label
      mpEditExpression->show();  // show the widget
      showCorrectButtonsExpression(); // depending on emptiness the Expression Widget

      // disable the option of use Initial Expression
      mpBoxUseInitialExpression->setEnabled(false);
      slotInitialTypeChanged(false);

      // update the expression widget
      mpEditExpression->updateExpressionWidget();

      break;

    case CModelEntity::ODE:
      // add expression layout
      CQModelValueLayout->addWidget(mpLblExpression, 2, 0);
      CQModelValueLayout->addMultiCellLayout(mpHBoxLayoutExpression, 2, 2, 1, 2);

      // show label, widget, and correct buttons
      mpLblExpression->show();   // show the label
      //      mpEditExpression->show();
      mpEditExpression->show();  // show the widget
      showCorrectButtonsExpression(); // depending on emptiness the Expression Widget

      // enable the option of use Initial Expression
      mpBoxUseInitialExpression->setEnabled(true);
      slotInitialTypeChanged(mpBoxUseInitialExpression->isChecked());

      // update the expression widget
      mpEditExpression->updateExpressionWidget();

      break;

    default:
      break;
    }
}

/*!
    This function is used in case of not FIXED type
 */
void CQModelValue::showCorrectButtonsExpression()
{
  // Update Button correlated to Expression Widget
  if (((CQExpressionWidget *)mpEditExpression->widget(0))->text().isEmpty())
    {
      std::cout << "expression empty" << std::endl;

      std::cout << "simulation type: " << mpComboBoxType->currentItem() << std::endl;
      // show the button of object selector
      mpBtnExpressionObject->show();
      // hide the button of expression editor
      mpBtnEditExpression->hide();
    }
  else
    {// not empty
      std::cout << "expression not empty -> " << ((CQExpressionWidget *)mpEditExpression->widget(0))->text() << std::endl;
      // hide the button of object selector
      mpBtnExpressionObject->hide();
      // show the button of expression editor
      mpBtnEditExpression->show();
    }
}

void CQModelValue::slotExpressionValid(bool valid)
{
  mExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

void CQModelValue::slotInitialExpressionValid(bool valid)
{
  mInitialExpressionValid = valid;
  mpBtnCommit->setEnabled(mExpressionValid && mInitialExpressionValid);
}

void CQModelValue::init()
{
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mpComboBoxType->insertItem(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);

  mExpressionValid = false;
  //  mpEditExpression->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);
  ((CQExpressionWidget *)mpEditExpression->widget(0))->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);

  mInitialExpressionValid = false;
  //  mpEditInitialExpression->setExpressionType(CCopasiSimpleSelectionTree::INITIAL_EXPRESSION);
  ((CQExpressionWidget *)mpEditInitialExpression->widget(0))->setExpressionType(CCopasiSimpleSelectionTree::TRANSIENT_EXPRESSION);
}

void CQModelValue::destroy()
{}

bool CQModelValue::update(ListViews::ObjectType /* objectType */,
                          ListViews::Action /* action */,
                          const std::string & /* key */)
{
  return true;
}

bool CQModelValue::leave()
{
  if (mpBtnCommit->isEnabled())
    {
      // -- Expression --
      //      slotTypeChanged(mpComboBoxType->currentItem());
      showCorrectButtonsExpression();
      /*      // hide the button of object selector
            mpBtnExpressionObject->hide();
            // show the button of expression editor
            mpBtnEditExpression->show();
      */      // update the expression widget
      mpEditExpression->updateExpressionWidget();

      // -- Initial Expression --
      showCorrectButtonsInitialExpression();
      /*      // hide the button of object selector
            mpBtnInitialExpressionObject->hide();
            // show the button of expression editor
            mpBtnEditInitialExpression->show();
      */      // update the expression widget
      mpEditInitialExpression->updateExpressionWidget();

      save();
    }

  return true;
}

bool CQModelValue::enter(const std::string & key)
{
  mKey = key;
  mpModelValue = dynamic_cast< CModelValue * >(GlobalKeys.get(key));

  if (!mpModelValue)
    {
      mpListView->switchToOtherWidget(115, "");
      return false;
    }

  load();
  return true;
}

/*!
    Load any saved values to the screen
 */
void CQModelValue::load()
{
  std::cout << "CQMV::load" << std::endl;
  if (mpModelValue == NULL) return;

  // Name
  mpEditName->setText(FROM_UTF8(mpModelValue->getObjectName()));

  // Type
  mpComboBoxType->setCurrentText(FROM_UTF8(CModelEntity::StatusName[mpModelValue->getStatus()]));

  // Initial Value
  mpEditInitialValue->setText(QString::number(mpModelValue->getInitialValue()));

  // Current Value
  mpEditCurrentValue->setText(QString::number(mpModelValue->getValue()));

  // Rate
  mpEditRate->setText(QString::number(mpModelValue->getRate()));

  // Expression
  //  mpEditExpression->setExpression(mpModelValue->getExpression());
  ((CQExpressionWidget *)mpEditExpression->widget(0))->setExpression(mpModelValue->getExpression());
  std::cout << "EXP: " << ((CQExpressionWidget *)mpEditExpression->widget(0))->getExpression() << std::endl;
  slotTypeChanged(mpComboBoxType->currentItem());
  /*
    // Update Button correlated to Expression Widget
    if (((CQExpressionWidget *)mpEditFcnExpression->widget(0))->text().isEmpty())
      {
        std::cout << "empty" << std::endl;

        if (((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()]) == CModelEntity::FIXED)
          {
            std::cout << "simulation type: fixed - " << mpComboBoxType->currentItem() << std::endl;
            // activate the button of object selector
            mpBtnExpressionObject->hide();
            // hide the button of expression editor
            mpBtnEditExpression->hide();
          }
        else
          {// other types
            std::cout << "simulation type: " << mpComboBoxType->currentItem() << std::endl;
            // show the button of object selector
            mpBtnExpressionObject->show();
            // hide the button of expression editor
            mpBtnEditExpression->hide();
          }
      }
    else
      {// not empty
        std::cout << "not empty" << std::endl;
        // hide the button of object selector
        mpBtnExpressionObject->hide();
        // show the button of expression editor
        mpBtnEditExpression->show();
      }
  */
  // Update Expression Widget
  mpEditExpression->updateExpressionWidget();

  // Initial Expression
  //  mpEditInitialExpression->setExpression(mpModelValue->getInitialExpression());
  ((CQExpressionWidget *)mpEditInitialExpression->widget(0))->setExpression(mpModelValue->getInitialExpression());
  //  std::cout << "INIT EXP: " << mpModelValue->getInitialExpression() << " vs "
  //            << ((CQExpressionWidget *)mpEditInitialExpression->widget(0))->getExpression() << std::endl;
  std::cout << "INIT EXP: " << ((CQExpressionWidget *)mpEditInitialExpression->widget(0))->getExpression() << std::endl;
  /*
    // Update Button correlated to Initial Expression Widget
    if (((CQExpressionWidget *)mpEditFcnInitialExpression->widget(0))->text().isEmpty())
      {
        std::cout << "initial empty" << std::endl;

        if (mpBoxUseInitialExpression->isChecked())
          {
            std::cout << "mpBoxUseInitialExpression->isChecked(): " << mpBoxUseInitialExpression->isChecked() << std::endl;
            // show the button of object selector
            mpBtnInitialExpressionObject->show();
            // hide the button of expression editor
            mpBtnEditInitialExpression->hide();
          }
        else
          {// not checked
            std::cout << "mpBoxUseInitialExpression->isChecked(): " << mpBoxUseInitialExpression->isChecked() << std::endl;
            // hide the button of object selector
            mpBtnInitialExpressionObject->hide();
            // hide the button of expression editor
            mpBtnEditInitialExpression->hide();
          }
      }
    else // not empty
      {
        std::cout << "not empty" << std::endl;
        // hide the button of object selector
        mpBtnInitialExpressionObject->hide();
        // show the button of expression editor
        mpBtnEditInitialExpression->show();
      }
  */
  // Update Initial Expression Widget
  mpEditInitialExpression->updateExpressionWidget();

  // Use Initial Expression
  if (mpModelValue->getStatus() == CModelEntity::ASSIGNMENT ||
      mpModelValue->getInitialExpression() == "")
    {
      mpBoxUseInitialExpression->setChecked(false);
      //      slotInitialTypeChanged(false);
    }
  else
    {
      mpBoxUseInitialExpression->setChecked(true);
      //      slotInitialTypeChanged(true);
    }

  mChanged = false;
}

/*!
    Save any inputs and set them as initial setting values
 */
void CQModelValue::save()
{
  std::cout << "CQNV::save" << std::endl;

  if (mpModelValue == NULL) return;

  // set text
  if (mpModelValue->getObjectName() != (const char *) mpEditName->text().utf8())
    {
      if (!mpModelValue->setObjectName((const char *) mpEditName->text().utf8()))
        {
          QString msg;
          msg = "Unable to rename quantity '" + FROM_UTF8(mpModelValue->getObjectName()) + "'\n"
                + "to '" + mpEditName->text() + "' since a quantity with that name already exists.\n";

          QMessageBox::information(this,
                                   "Unable to rename Quantity",
                                   msg,
                                   QMessageBox::Ok | QMessageBox::Default | QMessageBox::Escape, QMessageBox::NoButton, QMessageBox::NoButton);

          mpEditName->setText(FROM_UTF8(mpModelValue->getObjectName()));
        }
      else
        {
          protectedNotify(ListViews::MODELVALUE, ListViews::RENAME, mKey);
          mChanged = true;
        }
    }

  // set status
  if (mpModelValue->getStatus() != (CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()])
    {
      mpModelValue->setStatus((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()]);
      mChanged = true;
    }

  // set initial value
  if (QString::number(mpModelValue->getInitialValue()) != mpEditInitialValue->text() &&
      mpModelValue->getStatus() != CModelEntity::ASSIGNMENT)
    {
      mpModelValue->setInitialValue(mpEditInitialValue->text().toDouble());
      mChanged = true;
    }

  // set expression
  /*
    if (mpModelValue->getExpression() != mpEditExpression->getExpression())
      {
        mpModelValue->setExpression(mpEditExpression->getExpression());
        mChanged = true;
      }
  */
  if (mpModelValue->getExpression() != ((CQExpressionWidget *)mpEditExpression->widget(0))->getExpression())
    {
      mpModelValue->setExpression(((CQExpressionWidget *)mpEditExpression->widget(0))->getExpression());
      mChanged = true;
    }

  // set initial expression
  if ((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT)
    {
      /*  if (mpBoxUseInitialExpression->isChecked() &&
            mpModelValue->getInitialExpression() != mpEditInitialExpression->getExpression())
          {
            mpModelValue->setInitialExpression(mpEditInitialExpression->getExpression());
            mChanged = true;
          }
      */
      if (mpBoxUseInitialExpression->isChecked() &&
          mpModelValue->getInitialExpression() != ((CQExpressionWidget *)mpEditInitialExpression->widget(0))->getExpression())
        {
          mpModelValue->setInitialExpression(((CQExpressionWidget *)mpEditInitialExpression->widget(0))->getExpression());
          mChanged = true;
        }
      else if (!mpBoxUseInitialExpression->isChecked() &&
               mpModelValue->getInitialExpression() != "")
        {
          mpModelValue->setInitialExpression("");
          mChanged = true;
        }
    }

  if (mChanged)
    {
      CCopasiDataModel::Global->changed();
      protectedNotify(ListViews::MODELVALUE, ListViews::CHANGE, mKey);
    }

  mChanged = false;
}

void CQModelValue::slotNameLostFocus()
{
  if (mpEditName->text() != FROM_UTF8(mpModelValue->getObjectName()))
    {
      //  mpEditExpression->currentObjectRenamed(mpModelValue, mpEditName->text());
      ((CQExpressionWidget *)mpEditExpression->widget(0))->currentObjectRenamed(mpModelValue, mpEditName->text());
      //  mpEditInitialExpression->currentObjectRenamed(mpModelValue, mpEditName->text());
      ((CQExpressionWidget *)mpEditInitialExpression->widget(0))->currentObjectRenamed(mpModelValue, mpEditName->text());
    }
}

/*!
    If the initial expression is chosen to be used by checking the mpBoxUseInitialExpression check box being represented by
    the boolean parameter useInitialAssignment (true if checked; false otherwise), COPASI will show the Initial Expression
    Widget with its correct push buttons. Otherwise, the widget and its buttons will be hidden.
 */
void CQModelValue::slotInitialTypeChanged(bool useInitialAssignment)
{
  if (useInitialAssignment)  // use Initial Expression (ie. the mpBoxUseInitialExpression is checked)
    {
      // add the layout of initial expression to the CQModelValueLayout
      CQModelValueLayout->addWidget(mpLblInitialExpression, 4, 0);
      CQModelValueLayout->addMultiCellLayout(mpHBoxLayoutInitialExpression, 4, 4, 1, 2);

      // show label, widget, and the correct buttons
      mpLblInitialExpression->show();  // show the label
      //  mpEditInitialExpression->show();
      mpEditInitialExpression->show(); // show the widget
      /*   mpBtnEditInitialExpression->hide();
            mpBtnInitialExpressionObject->show();
      */

      showCorrectButtonsInitialExpression();

      // enable the option of use Initial Value
      mpEditInitialValue->setEnabled(false);

      // update the Initial Expression Widget
      mpEditInitialExpression->updateExpressionWidget();
    }
  else  // mpBoxUseInitialExpression is not checked
    {
      // remove the layout of initial expression from GUI screen
      CQModelValueLayout->removeItem(mpHBoxLayoutInitialExpression);
      CQModelValueLayout->remove(mpLblInitialExpression);

      // hide label, widget, and all buttons
      mpLblInitialExpression->hide();
      // mpEditInitialExpression->hide();
      mpEditInitialExpression->hide();
      mpBtnEditInitialExpression->hide();
      mpBtnInitialExpressionObject->hide();

      // enable the option of use Initial Value
      mpEditInitialValue->setEnabled((CModelEntity::Status) mItemToType[mpComboBoxType->currentItem()] != CModelEntity::ASSIGNMENT);

      // we don't need to update the Initial Expression Widget
    }
}

/*!
 */
void CQModelValue::showCorrectButtonsInitialExpression()
{
  // Update Button correlated to Initial Expression Widget
  if (((CQExpressionWidget *)mpEditInitialExpression->widget(0))->text().isEmpty())  // widget is empty
    {
      std::cout << "initial widget empty" << std::endl;

      // show the button of object selector
      mpBtnInitialExpressionObject->show();
      // hide the button of expression editor
      mpBtnEditInitialExpression->hide();
    }
  else // not empty
    {
      std::cout << "initial widget not empty -> " << ((CQExpressionWidget *)mpEditInitialExpression->widget(0))->text() << std::endl;
      // hide the button of object selector
      mpBtnInitialExpressionObject->hide();
      // show the button of expression editor
      mpBtnEditInitialExpression->show();
    }
}

/*!
    The slot to activate the editor page of type CQExpressionWidget
    for being able to type a new mathematical expression or edit the existing one
 */
void CQModelValue::slotEditExpression()
{
  // activate editor page of the Expression widget stack
  //  mpEditFcnExpression->raiseWidget(mpEditExpression);
  mpEditExpression->raiseWidget(0);
  // show the button of object selector
  mpBtnExpressionObject->show();
  // hide the button of going back to the expression editor
  mpBtnEditExpression->hide();
}

/*!
    The slot to activate the editor page of type CQExpressionWidget
    for being able to type a new mathematical expression or edit the existing one
 */
void CQModelValue::slotEditInitialExpression()
{
  // activate editor page of the Initial Expression widget stack
  mpEditInitialExpression->raiseWidget(0);
  // show the button of object selector
  mpBtnInitialExpressionObject->show();
  // hide the button of going back to the expression editor
  mpBtnEditInitialExpression->hide();
}
