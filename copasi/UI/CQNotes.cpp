// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQNotes.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/08/13 20:06:23 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQNotes.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: shoops
 */

#include <QWebFrame>
#include <QProcess>

#include "CQNotes.h"
#include "CQIcons.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "model/CModelValue.h"
#include "model/CReaction.h"
#include "function/CFunction.h"
#include "report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "commandline/CConfigurationFile.h"

CQNotes::CQNotes(QWidget* parent, const char* name) :
    CopasiWidget(parent, name)
{
  setupUi(this);

  mEditMode = false;
  mpEdit->hide();
  mpWebView->show();
  mpBtnToggleEdit->setIcon(CQIcons::getIcon(CQIcons::Edit));

  mpWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

CQNotes::~CQNotes()
{}

// virtual
bool CQNotes::update(ListViews::ObjectType /* objectType */, ListViews::Action action, const std::string & key)
{
  if (key == mKey &&
      action == ListViews::CHANGE)
    {
      load();
    }

  return true;
}

// virtual
bool CQNotes::leave()
{
  mpBtnToggleEdit->setFocus();
  save();

  return true;
}

// virtual
bool CQNotes::enterProtected()
{
  load();

  return true;
}

void CQNotes::slotToggleMode()
{
  mEditMode = !mEditMode;

  if (mEditMode)
    {
      mpWebView->hide();
      mpEdit->show();
      mpBtnToggleEdit->setIcon(CQIcons::getIcon(CQIcons::View));
    }
  else
    {
      save();
      load();

      mpEdit->hide();
      mpWebView->show();
      mpBtnToggleEdit->setIcon(CQIcons::getIcon(CQIcons::Edit));
    }
}

void CQNotes::load()
{
  if (mpObject != NULL)
    {
      const std::string * pNotes = NULL;

      if (dynamic_cast< CModelEntity * >(mpObject))
        pNotes = &static_cast< CModelEntity * >(mpObject)->getNotes();
      else if (dynamic_cast< CReaction * >(mpObject))
        pNotes = &static_cast< CReaction * >(mpObject)->getNotes();
      else if (dynamic_cast< CFunction * >(mpObject))
        pNotes = &static_cast< CFunction * >(mpObject)->getNotes();

      if (pNotes != NULL)
        {
          // The notes are UTF8 encoded however the html does not specify an encoding
          // thus Qt uses locale settings.
          mpWebView->setHtml(FROM_UTF8(*pNotes));
          mpEdit->setPlainText(FROM_UTF8(*pNotes));
        }
    }

  mChanged = false;

  return;
}

void CQNotes::save()
{
  // TODO CRITICAL We need to validate that we have proper XML.
  // We can use QXmlSimpleReader for doing this as we are only interested the fact that
  // we have valid XML.

  if (mpObject != NULL)
    {
      const std::string * pNotes = NULL;

      if (dynamic_cast< CModelEntity * >(mpObject))
        pNotes = &static_cast< CModelEntity * >(mpObject)->getNotes();
      else if (dynamic_cast< CReaction * >(mpObject))
        pNotes = &static_cast< CReaction * >(mpObject)->getNotes();
      else if (dynamic_cast< CFunction * >(mpObject))
        pNotes = &static_cast< CFunction * >(mpObject)->getNotes();

      if (pNotes &&
          mpEdit->toPlainText() != FROM_UTF8(*pNotes))
        {
          if (dynamic_cast< CModelEntity * >(mpObject))
            static_cast< CModelEntity * >(mpObject)->setNotes(TO_UTF8(mpEdit->toPlainText()));
          else if (dynamic_cast< CReaction * >(mpObject))
            static_cast< CReaction * >(mpObject)->setNotes(TO_UTF8(mpEdit->toPlainText()));
          else if (dynamic_cast< CFunction * >(mpObject))
            static_cast< CFunction * >(mpObject)->setNotes(TO_UTF8(mpEdit->toPlainText()));

          mChanged = true;
        }
    }

  if (mChanged)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      protectedNotify(ListViews::MODEL, ListViews::CHANGE, mKey);
    }

  mChanged = false;
  return;
}

void CQNotes::slotOpenUrl(const QUrl & url)
{
  QString Commandline = FROM_UTF8(CCopasiRootContainer::getConfiguration()->getWebBrowser());

  if (Commandline == "")
    {
#ifdef Q_WS_MAC
      Commandline = "open %1";
#else
# ifdef Q_WS_WIN
      Commandline = "cmd /c start %1";
# else
      CQMessageBox::critical(this, "Unable to open link",
                             "COPASI requires you to specify an application for opening URLs for links to work.\n\nPlease go to the preferences and set an appropriate application in the format:\n  command [options] %1");

      return;
# endif  // Q_WS_WIN
#endif // Q_WS_MAC

      CCopasiRootContainer::getConfiguration()->setWebBrowser(TO_UTF8(Commandline));
    }

#ifdef Q_WS_WIN

  if (Commandline == "cmd /c start %1")
    {
      if (QProcess::execute(Commandline.arg(url.toString())) != 0)
        {
          CQMessageBox::critical(this, "Unable to open link",
                                 "COPASI requires you to specify an application for opening links. The currently provided command:\n  " +
                                 Commandline + "\nis not working properly.\n\nPlease go to the preferences and set an appropriate application in the format:\n  application [options] %1");
        }

      return;
    }

#endif // Q_WS_WIN

  if (!QProcess::startDetached(Commandline.arg(url.toString())))
    {
      CQMessageBox::critical(this, "Unable to open link",
                             "COPASI requires you to specify an application for opening links. The currently provided command:\n  " +
                             Commandline + "\nis not working properly.\n\nPlease go to the preferences and set an appropriate application in the format:\n  application [options] %1");
    }

  return;
}
