// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQNotes.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: shoops
 */

#include <QtWebKit/QWebFrame>
#include <QtXml/QXmlInputSource>
#include <QtXml/QXmlSimpleReader>
#include <QtGui/QDesktopServices>

#include "CQNotes.h"
#include "resourcesUI/CQIconResource.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "model/CModelValue.h"
#include "model/CReaction.h"
#include "model/CEvent.h"
#include "function/CFunction.h"
#include "report/CKeyFactory.h"
#include "report/CReportDefinition.h"
#include "copasi/report/CCopasiRootContainer.h"
#include "commandline/CConfigurationFile.h"

#if COPASI_UNDO
#include <copasi/UI/copasiui3window.h>
#include <copasi/UI/CQCopasiApplication.h>
#include <copasi/undoFramework/ChangeNotesCommand.h>
#endif // COPASI_UNDO

CQValidatorXML::CQValidatorXML(QPlainTextEdit * parent, const char * name):
  CQValidator< QPlainTextEdit >(parent, &QPlainTextEdit::toPlainText, name),
  mIsFreeText(true),
  mNeedsWrap(false)
{}

// virtual
QValidator::State CQValidatorXML::validate(QString & input, int & pos) const
{
  QXmlSimpleReader Validator;
  QXmlInputSource Input;
  CQNotesContentHandler ContentHandler;

  Validator.setContentHandler(&ContentHandler);

  // We like to allow free text and therefore wrap the text to create valid XML.
  Input.setData("<Validate:XML xmlns:Validate=\"http://www.copasi.org/Validate\">" + input + "</Validate:XML>");

  if (Validator.parse(Input))
    {
      mIsFreeText = ContentHandler.isFreeText();
      mNeedsWrap = ContentHandler.needsWrap();
      return CQValidator< QPlainTextEdit >::validate(input, pos);
    }

  mIsFreeText = true;
  mNeedsWrap = false;
  setColor(Invalid);
  return Intermediate;
}

const bool & CQValidatorXML::isFreeText() const
{
  return mIsFreeText;
}

const bool & CQValidatorXML::needsWrap() const
{
  return mNeedsWrap;
}

CQNotesContentHandler::CQNotesContentHandler():
  QXmlDefaultHandler(),
  mIsFreeText(true),
  mNeedsWrap(true),
  mLevel(0)
{}

CQNotesContentHandler:: ~CQNotesContentHandler()
{}

// virtual
bool CQNotesContentHandler::startDocument()
{
  mIsFreeText = true;
  mNeedsWrap = true;
  mLevel = 0;
  return true;
}

// virtual
bool CQNotesContentHandler::startElement(const QString & namespaceURI,
    const QString & localName,
    const QString & qName,
    const QXmlAttributes & atts)
{
  if (namespaceURI != "http://www.copasi.org/Validate" ||
      qName != "Validate:XML")
    mIsFreeText = false;

  if (mLevel == 1 &&
      namespaceURI == "http://www.w3.org/1999/xhtml" &&
      (localName == "html" || localName == "body"))
    mNeedsWrap = false;

  mLevel++;

  return QXmlDefaultHandler::startElement(namespaceURI, localName, qName, atts);
}

// virtual
bool CQNotesContentHandler::endElement(const QString & namespaceURI,
                                       const QString & localName,
                                       const QString & qName)
{
  mLevel--;

  return QXmlDefaultHandler::endElement(namespaceURI, localName, qName);
}

const bool & CQNotesContentHandler::isFreeText() const
{
  return mIsFreeText;
}

bool CQNotesContentHandler::needsWrap() const
{
  return (mNeedsWrap && !mIsFreeText);
}

CQNotes::CQNotes(QWidget* parent, const char* name) :
  CopasiWidget(parent, name),
  mEditMode(false),
  mChanged(false),
  mpValidatorXML(NULL),
  mValidity(QValidator::Acceptable),
  mKeyToCopy("")

{
  setupUi(this);

  mpValidatorXML = new CQValidatorXML(mpEdit);

  mEditMode = false;
  mpEdit->hide();
  mpWebView->show();
  mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::edit));

  mpWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

#if COPASI_UNDO
  mpUndoStack = NULL;
#endif
}

CQNotes::~CQNotes()
{}

void CQNotes::slotBtnCopy()
{
  mKeyToCopy = mKey;
}

// virtual
bool CQNotes::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (action)
    {
      case ListViews::CHANGE:

        if (key == mKey)
          {
            load();
          }

        break;

      case ListViews::DELETE:

        if (key == mKey || objectType == ListViews::MODEL)
          {
            mpObject = NULL;
            mKey = "";
          }

        break;

      default:
        break;
    }

  if (objectType == ListViews::MODEL &&
      action == ListViews::DELETE)
    {
      mEditMode = false;
    }

  return true;
}

// virtual
bool CQNotes::leave()
{
  mpBtnToggleEdit->setFocus();

  mpObject = CCopasiRootContainer::getKeyFactory()->get(mKey);

  if (mpObject != NULL)
    {
      save();
    }
  else
    {
      mKey = "";
      mpDataModel = NULL;
    }

  return true;
}

// virtual
bool CQNotes::enterProtected()
{
  if (mKeyToCopy == "")
    {
      load();
    }
  else
    {
      mpObject = CCopasiRootContainer::getKeyFactory()->get(mKeyToCopy);
      load();
      mpObject = CCopasiRootContainer::getKeyFactory()->get(mKey);
      save();
      mKeyToCopy = "";
    }

  return true;
}

void CQNotes::slotToggleMode()
{
  mEditMode = !mEditMode;

  if (mEditMode)
    {
      mpWebView->hide();
      mpEdit->show();
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::renderMarkup));
    }
  else
    {
      save();
      load();

      mpEdit->hide();
      mpWebView->show();
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::edit));
    }
}

void CQNotes::slotValidateXML()
{
  QString Input = mpEdit->toPlainText();
  int pos = 0;

  mValidity = mpValidatorXML->validate(Input, pos);

  if (mpValidatorXML->isFreeText())
    {
      mEditMode = true;
      mpBtnToggleEdit->hide();
    }
  else
    {
      mpBtnToggleEdit->show();
    }

  if (mEditMode)
    {
      mpWebView->hide();
      mpEdit->show();
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::renderMarkup));
    }
  else
    {
      mpEdit->hide();
      mpWebView->show();
      mpBtnToggleEdit->setIcon(CQIconResource::icon(CQIconResource::edit));
    }
}

void CQNotes::load()
{
  if (mpObject != NULL)
    {
      QString Notes;

      CAnnotation * pAnnotation = CAnnotation::castObject(mpObject);
      CReportDefinition * pReportDefinition = static_cast< CReportDefinition * >(mpObject);

      if (pAnnotation != NULL)
        {
          Notes = FROM_UTF8(pAnnotation->getNotes());
        }
      else if (pReportDefinition != NULL)
        {
          Notes = FROM_UTF8(pReportDefinition->getComment());
        }

      // The notes are UTF8 encoded however the html does not specify an encoding
      // thus Qt uses locale settings.
      mpWebView->setHtml(Notes);
      mpEdit->setPlainText(Notes);
      mpValidatorXML->saved();
      slotValidateXML();

      if (!mpValidatorXML->isFreeText() && mEditMode)
        {
          slotToggleMode();
        }

      mValidity = QValidator::Acceptable;
    }

  mChanged = false;

  return;
}

void CQNotes::save()
{
  if (mpObject != NULL &&
      mValidity == QValidator::Acceptable)
    {

      CAnnotation * pAnnotation = CAnnotation::castObject(mpObject);
      CReportDefinition * pReportDefinition = static_cast< CReportDefinition * >(mpObject);

      std::string notes;

      if (pAnnotation != NULL)
        {
          notes = pAnnotation->getNotes();
        }
      else if (pReportDefinition != NULL)
        {
          notes = pReportDefinition->getComment();
        }

      QString qNotes(FROM_UTF8(notes));

      if (mpEdit->toPlainText() != qNotes)
        {
          std::string PlainText = TO_UTF8(mpEdit->toPlainText());

          if (mpValidatorXML->needsWrap())
            {
              // We wrap the HTML in a body element if it does not contain a top level html or body element.
              PlainText = "<body xmlns=\"http://www.w3.org/1999/xhtml\">" + PlainText + "</body>";
            }

#if COPASI_UNDO

          if (mpUndoStack == NULL)
            {
              CopasiUI3Window *  pWindow = static_cast<CQCopasiApplication*>(qApp)->getMainWindow();

              if (pWindow)
                mpUndoStack = pWindow->getUndoStack();
            }

          mpUndoStack->push(new ChangeNotesCommand(mpObject, notes, PlainText, this));
#else

          if (pAnnotation != NULL)
            {
              pAnnotation->setNotes(PlainText);
            }
          else if (pReportDefinition != NULL)
            {
              pReportDefinition->setComment(PlainText);
            }

          mChanged = true;
#endif
        }
    }

  if (mChanged)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      protectedNotify(ListViews::MODEL, ListViews::CHANGE, mKey);
      mChanged = false;
    }

  return;
}

void CQNotes::slotOpenUrl(const QUrl & url)
{
  QDesktopServices::openUrl(url);
  return;
}

#if COPASI_UNDO
void
CQNotes::changeNotes(const std::string& key, const std::string& notes)
{
  mKey = key;
  load();
  mpListView->switchToOtherWidget(C_INVALID_INDEX, mKey);
  qApp->processEvents();

  CAnnotation * pAnnotation = CAnnotation::castObject(mpObject);
  CReportDefinition * pReportDefinition = static_cast< CReportDefinition * >(mpObject);

  if (pAnnotation != NULL)
    {
      pAnnotation->setNotes(notes);
    }
  else if (pReportDefinition != NULL)
    {
      pReportDefinition->setComment(notes);
    }

  if (mpDataModel != NULL)
    {
      mpDataModel->changed();
    }

  protectedNotify(ListViews::MODEL, ListViews::CHANGE, mKey);
}
#endif // COPASI_UNDO
