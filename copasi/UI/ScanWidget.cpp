/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ScanWidget.cpp,v $
   $Revision: 1.179 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/22 17:23:31 $
   End CVS Header */

//***  In this file I have put "//+++" in all places where something has to be added
//***  if a new scan item is introduced.

#include <qfiledialog.h>
#include <qvariant.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <qcombobox.h>

#include "copasi.h"

#include "ScanWidget.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "model/CModel.h"
#include "listviews.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "ScanItemWidget.h"
#include "ObjectBrowserDialog.h"
#include "ObjectBrowserItem.h"

//#include "SteadyStateWidget.h"
//#include "TrajectoryWidget.h"
//#include "trajectory/CTrajectoryTask.h"
//#include "trajectory/CTrajectoryProblem.h"
//#include "steadystate/CSteadyStateTask.h"
//#include "steadystate/CSteadyStateProblem.h"

#include "report/CKeyFactory.h" 
//#include "CReportDefinitionSelect.h"
#include "qtUtilities.h"
#include "CProgressBar.h"
#include "utilities/CCopasiException.h"
#include "CScanContainerWidget.h"
#include "utilities/CopasiTime.h"

//+++
#include "CScanWidgetScan.h"
#include "CScanWidgetTask.h"

#include "./icons/scanwidgetbuttonicon.xpm"
ScanWidget::ScanWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
    //    pParent(parent)
{
  if (!name)
    setName("ScanWidget");

  setCaption(trUtf8("ScanWidget"));
  ScanWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanWidgetLayout");

  //*****************

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText("<h2>Parameter Scan</h2>");
  ScanWidgetLayout->addWidget(TextLabel1, 0, 0);

  //**********************

  QHBoxLayout* tmpLayout = new QHBoxLayout();

  QSpacerItem* tmpSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  tmpLayout->addItem(tmpSpacer);

  QLabel* tmpLabel = new QLabel(this);
  tmpLabel->setText("New scan item: ");
  tmpLayout->addWidget(tmpLabel);

  comboType = new QComboBox(this);
  comboType->insertItem("Parameter Scan");
  tmpLayout->addWidget(comboType);

  buttonNewItem = new QPushButton(this, "buttonNewItem");
  buttonNewItem->setText("... Create!");
  //ScanWidgetLayout->addWidget(buttonNewItem, 1, 2);
  tmpLayout->addWidget(buttonNewItem);

  ScanWidgetLayout->addMultiCellLayout(tmpLayout, 1, 1, 0, 2);

  //sExecutable = new QCheckBox(this, "sExecutable");
  //sExecutable->setText(trUtf8("Scan Executable"));

  //ScanWidgetLayout->addWidget(sExecutable, 0, 2);

  //**********************
  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  scanButton = new QPushButton(this, "scanButton");
  scanButton->setText(trUtf8("Run"));
  Layout2->addWidget(scanButton);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Revert"));
  Layout2->addWidget(cancelChange);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("Report..."));
  Layout2->addWidget(reportDefinitionButton);

  ScanWidgetLayout->addMultiCellLayout(Layout2, 6, 6, 0, 2);

  //*****************************

  Layout24 = new QHBoxLayout(0, 0, 6, "Layout24");

  scrollview = new CScanContainerWidget(this);
  Layout24->addWidget(scrollview);

  ScanWidgetLayout->addMultiCellLayout(Layout24, 4, 4, 0, 2);

  // tab order
  /*setTabOrder(taskName, sExecutable);
  setTabOrder(sExecutable, steadyState);
  setTabOrder(steadyState, trajectory);
  setTabOrder(trajectory, addButton);
  setTabOrder(downButton, scrollview);
  setTabOrder(scrollview, ObjectListBox);
  setTabOrder(ObjectListBox, scanButton);
  setTabOrder(scanButton, cancelChange);
  setTabOrder(cancelChange, reportDefinitionButton);*/

  connect(scanButton, SIGNAL(clicked()), this, SLOT(runScanTask()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChangeButton()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));
  connect(buttonNewItem, SIGNAL(clicked()), this, SLOT(slotAddItem()));

  //connect(sExecutable, SIGNAL(clicked()), this, SLOT(ScanCheckBoxClicked()));

  /*sExecutable->setEnabled(false);
  scanButton->setEnabled(true);*/

  reportDefinitionButton->setEnabled(false);
}

ScanWidget::~ScanWidget()
{}

void ScanWidget::CancelChangeButton()
{
  loadScan();
}

void ScanWidget::ScanCheckBoxClicked()
{
  /*  CScanTask* scanTask =
      dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
    scanTask->setRequested(sExecutable->isChecked());
    scanButton->setEnabled(sExecutable->isChecked());*/
}

void ScanWidget::runScanTask()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  if (!scanTask) return;

  //((CScanProblem*)(scanTask->getProblem()))->createDebugScan(dataModel->getModel());

  // save the state of the widget
  saveScan();

  scanTask->initialize(NULL);

  setCursor(Qt::WaitCursor);
  CProgressBar* tmpBar = new CProgressBar(dataModel);
  scanTask->setProgressHandler(tmpBar);

  CCopasiTimeVariable time = CCopasiTimeVariable::getCurrentWallTime();

  try
    {
      scanTask->process();
    }
  catch (CCopasiException Exception)
    {
      std::cout << std::endl << "exception in scan task" << std::endl;
      //TODO: message box
    }

  std::cout << "*************** The scan took "
  << (CCopasiTimeVariable::getCurrentWallTime() - time).isoFormat()
  << " ***************" << std::endl;

  //should be renamed?
  scanTask->restore();

  tmpBar->finish(); pdelete(tmpBar);

  protectedNotify(ListViews::STATE, ListViews::CHANGE,
                  CCopasiDataModel::Global->getModel()->getKey());

  unsetCursor();

  return;

  std::ofstream output;
  if (scanTask->getReport().getTarget() != "")
    {
      if (scanTask->getReport().append())
        output.open(FROM_UTF8(scanTask->getReport().getTarget()),
                    std::ios_base::out | std::ios_base::app);
      else
        output.open(FROM_UTF8(scanTask->getReport().getTarget()),
                    std::ios_base::out);
    }
  if (output.is_open())
    scanTask->initialize(&output);
  else //ask if user insists on proceeding
    {
      if (QMessageBox::information (NULL, "No output specified,",
                                    "No report output target defined, Copasi cannot creat output for you.\n Do you want to continue running scan task with no output?",
                                    QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;
    }

  scanTask->process();

  //  ((ListViews*)pParent)->notify(ListViews::STATE, ListViews::CHANGE, dataModel->getModel()->getKey());
  unsetCursor();
}

bool ScanWidget::loadScan()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  if (!scanTask) return false;

  CScanProblem *scanProblem = dynamic_cast<CScanProblem *>(scanTask->getProblem());
  if (!scanProblem) return false;

  mModel = scanProblem->getModel();

  scrollview->clearWidgetList();

  //std::vector<QWidget*> & widgetList = scrollview->getWidgetList();

  CScanWidgetScan* tmp1;

  // the scan items
  unsigned C_INT32 i, imax = scanProblem->getNumberOfScanItems();
  for (i = 0; i < imax; ++i)
    {
      void* pTmp;
      if (!(pTmp = scanProblem->getScanItem(i)->getValue("Type"))) return false;
      CScanProblem::Type type = *(CScanProblem::Type*)pTmp;

      switch (type)
        {
          //+++
        case CScanProblem::SCAN_LINEAR :
          tmp1 = new CScanWidgetScan(scrollview);
          tmp1->initFromScanItem(scanProblem->getScanItem(i), CCopasiDataModel::Global->getModel());
          scrollview->addWidget(tmp1);
          break;

        case CScanProblem::SCAN_REPEAT :
          break;

        default:
;
        }
    }

  // the widget for the subtask
  CScanWidgetTask* tmpT = new CScanWidgetTask(scrollview);
  tmpT->initFromScanProblem(scanProblem, CCopasiDataModel::Global->getModel());
  scrollview->addWidget(tmpT, false); //false: no control buttons (up/down/del)

  //scrollview->updateFromWidgetList();
  return true;
}

bool ScanWidget::slotAddItem()
{
  CScanWidgetScan* tmp1;

  CScanProblem::Type type = CScanProblem::SCAN_LINEAR;

  //create item to get the default values
  CScanProblem* tmpProblem = new CScanProblem();
  CCopasiParameterGroup* tmpItem = tmpProblem->createScanItem(type, 10);

  switch (type)
    {
      //+++
    case CScanProblem::SCAN_LINEAR :
      tmp1 = new CScanWidgetScan(scrollview);
      tmp1->initFromScanItem(tmpItem, CCopasiDataModel::Global->getModel());
      scrollview->insertWidget(tmp1);
      break;

    case CScanProblem::SCAN_REPEAT :
      break;

    default:
;
    }

  if (tmpProblem) delete tmpProblem;

  return true;
}

bool ScanWidget::saveScan() const
  {
    CScanTask* scanTask =
      dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
    if (!scanTask) return false;

    CScanProblem *scanProblem = dynamic_cast<CScanProblem *>(scanTask->getProblem());
    if (!scanProblem) return false;

    scanProblem->clearScanItems();

    const std::vector<QWidget*> & widgetList = scrollview->getWidgetList();

    unsigned C_INT32 i, imax = widgetList.size();
    for (i = 0; i < imax; ++i)
      {
        //+++

        // item: scan parameter
        const CScanWidgetScan* tmp1 = dynamic_cast<CScanWidgetScan*>(widgetList[i]);
        if (tmp1) {tmp1->saveToScanItem(scanProblem); continue;}

        // the subtask
        const CScanWidgetTask* tmpT = dynamic_cast<CScanWidgetTask*>(widgetList[i]);
        if (tmpT) {tmpT->saveToScanProblem(scanProblem); continue;}

        return false;
      }
    //scrollview->updateFromWidgetList();

    return true;
  }

void ScanWidget::ReportDefinitionClicked()
{
  /*  CReportDefinitionSelect* pSelectDlg = new CReportDefinitionSelect(pParent);
    CScanTask* scanTask = (CScanTask*)(CCopasiContainer*)GlobalKeys.get(scanTaskKey);
    pSelectDlg->setReport(&(scanTask->getReport()));
    pSelectDlg->loadReportDefinitionVector();
    if (pSelectDlg->exec () == QDialog::Rejected)
      {
        return;
      }*/
}

//************* CCopasiWidget interface *******************************

bool ScanWidget::enter(const std::string & key)
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(key));
  if (!scanTask) return false;

  scanTaskKey = key;

  //pSteadyStateWidget->enter(SteadyStateKey);
  //pTrajectoryWidget->enter(TrajectoryKey);

  // ((CScanProblem*)(scanTask->getProblem()))->createDebugScan(dataModel->getModel());

  loadScan();

  return true;
}

bool ScanWidget::leave()
{
  //CScanTask* scanTask =
  //  dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  //if (!scanTask) return false;

  return saveScan();
}

bool ScanWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
      // check if there is a list of Report Defs
      CReportDefinitionVector* pReportDefinitionVector;
      pReportDefinitionVector = CCopasiDataModel::Global->getReportDefinitionList();
      if (pReportDefinitionVector)
        reportDefinitionButton->setEnabled(true);
      break;
    default:
      break;
    }
  return true;
}

//***********************************************************
